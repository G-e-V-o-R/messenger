#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <boost/beast/websocket.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <pqxx/pqxx>
#include <unordered_map>
#include <mutex>
#include <nlohmann/json.hpp>
#include <webSession.h>
#include <handleRequests.h>
#include <user.h>

class webSession;

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using json = nlohmann::json;
using tcp = net::ip::tcp;


class Session : public std::enable_shared_from_this<Session>
{
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    std::shared_ptr<std::string const> doc_root_;
    http::request<http::string_body> req_;
    pqxx::connection& conn_;
    user currentUser_;

private:

void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void send_response(http::message_generator&& msg)
{
    bool keep_alive = msg.keep_alive();

    beast::async_write(stream_, std::move(msg),
    beast::bind_front_handler(&Session::on_write, shared_from_this(), keep_alive));
}



public:

Session(tcp::socket&& socket, std::shared_ptr<std::string const> const& doc_root, pqxx::connection& conn)
    : stream_(std::move(socket)), doc_root_(doc_root), conn_(conn)
{
    std::cout << "New session starts: " << std::endl;
}

void run()
{
    net::dispatch(stream_.get_executor(),
    beast::bind_front_handler(&Session::do_read, shared_from_this()));
}

void do_read()
{
    req_ = {};

    stream_.expires_after(std::chrono::seconds(30));

    http::async_read(stream_, buffer_, req_,
    beast::bind_front_handler(&Session::on_read, shared_from_this()));
}

void get_user_id_from_session_id()
{
    pqxx::work txn{conn_};

    pqxx::result res = txn.exec("SELECT user_id FROM sessions WHERE session_id = '" + currentUser_.session_id + "'");
    txn.commit();

    if (!res.empty()) {
        currentUser_.user_id =  res[0][0].as<std::string>();
        std::cout << "uder_id : " << currentUser_.user_id << std::endl;
    }else{
        throw std::runtime_error("Session ID not found in database");
    }
}



void on_read(beast::error_code ec, std::size_t bytes_transferred) 
{
    boost::ignore_unused(bytes_transferred);

    if (ec == http::error::end_of_stream)
        return do_close();

    if (ec)
        return fail(ec, "read");

    if (websocket::is_upgrade(req_)) {

        if (req_.base().find("Session-ID") != req_.base().end()) {
            currentUser_.session_id = std::string(req_.base().at("Session-ID"));
            std::cout << currentUser_.session_id << std::endl;
        }else{
            std::cout << "HEader error: " << std::endl;
        }

        try {
            get_user_id_from_session_id();
            auto web_session = std::make_shared<WebSession>(stream_.release_socket(), currentUser_.user_id, conn_);
            web_session->init();
            web_session->run(std::move(req_));

        } catch (const std::exception& e) {
            std::cerr << "Error finding user by session_id: " << e.what() << std::endl;
            return fail(ec, "session_id not found");
        }
        return;
    }

    send_response(HandleRequests::handle_request(*doc_root_, std::move(req_), conn_));
}

void on_write(bool keep_alive, beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);
    if(ec)
        return fail(ec, "write");
    if(!keep_alive)
        return do_close();

    do_read();
}

void do_close()
{
    beast::error_code ec;
    stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
    std::cout << "Session is closed" << std::endl;
}
};