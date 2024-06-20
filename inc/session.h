#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <pqxx/pqxx>
#include <memory>
#include <string>
#include "user.h" 

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket&& socket, std::shared_ptr<std::string const> const& doc_root, pqxx::connection& conn);

    void run();

private:
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    std::shared_ptr<std::string const> doc_root_;
    http::request<http::string_body> req_;
    pqxx::connection& conn_;
    user currentUser_;

    void fail(beast::error_code ec, char const* what);
    void send_response(http::message_generator&& msg);
    void do_read();
    void get_user_id_from_session_id();
    void on_read(beast::error_code ec, std::size_t bytes_transferred);
    void on_write(bool keep_alive, beast::error_code ec, std::size_t bytes_transferred);
    void do_close();
};

