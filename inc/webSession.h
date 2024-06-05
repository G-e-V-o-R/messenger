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
#include "sessionMeneger.h"
#include <user.h>

class SessionManager;
extern SessionManager session_manager;
extern void store_message(pqxx::connection& conn, const std::string& sender_id, const std::string& recipient_id, const std::string& message);


namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class WebSession : public std::enable_shared_from_this<WebSession> {
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;
    user currentUser_;
    pqxx::connection& conn_;
    std::mutex session_manager_mutex;
    std::mutex user_mutex;


private:

    void fail( beast::error_code ec, char const* what)
    {
        std::cerr << what << ": " << ec.message() << "\n";
    }

public:
    explicit WebSession( tcp::socket&& socket, const std::string& user_id, pqxx::connection& conn)
        : ws_(std::move(socket)), conn_(conn)
    {
             currentUser_.user_id = user_id;
    }

    void init() 
    {
        session_manager.add_session(currentUser_.user_id, shared_from_this());
        std::cout << "WebSession added to sessionManager with user_id: " << currentUser_.user_id << std::endl;
    }

    ~WebSession() 
    {
        session_manager.remove_session(currentUser_.user_id);
    }

    void run( http::request<http::string_body> req) 
    {
        std::cout << "WebSession run(): " << std::endl;
        ws_.async_accept( req, beast::bind_front_handler(&WebSession::on_accept, shared_from_this()));
    }

    void on_accept( beast::error_code ec) 
    {
        std::cout << "WebSession on accept(): " << std::endl;
        if (ec) {
            return fail(ec, "accept");
        }
        do_read();
    }

    void do_read() 
    {
                std::cout << "WebSession do_read(): " << std::endl;

        ws_.async_read( buffer_, beast::bind_front_handler(&WebSession::on_read, shared_from_this()));
    }

    void on_read( beast::error_code ec, std::size_t bytes_transferred) 
    {
        if (ec == websocket::error::closed) {
            return;
        }

        if (ec) {
            return fail(ec, "read");
        }

        std::cout << "WebSession on_read(): " << std::endl;

        std::string message = beast::buffers_to_string(buffer_.data());
        std::cout << "Received message: " << message << std::endl;
        // Process message and route to the intended recipient
        handle_message(message);
        buffer_.consume(buffer_.size());
        do_read();
    }

    void handle_message(const std::string& message) {
    std::cout << "WebSession handle_message(): " << std::endl;

    //message format: "recipient_id:message_text"
    auto delimiter_pos = message.find(':');
    if (delimiter_pos != std::string::npos) {
        std::string recipient_id = message.substr(0, delimiter_pos);
        std::string message_text = message.substr(delimiter_pos + 1);

        // Защитите доступ к session_manager с помощью мьютекса
        std::lock_guard<std::mutex> lock(session_manager_mutex);
        std::lock_guard<std::mutex> user_lock(user_mutex);

        auto recipient_session = session_manager.get_session(recipient_id);
        if (recipient_session) {
            std::cout << "uxarkeci namaky usery log Out chi exe: " << std::endl;
            // Проверьте существование сессии перед отправкой сообщения
            recipient_session->send_message(message_text);
        } else {
            std::cout << "Log in chi exel namaky DB uma: " << std::endl;
            // Защитите доступ к currentUser_ с помощью мьютекса
            std::lock_guard<std::mutex> user_lock(user_mutex);
            // Store message in the database if recipient is offline
            store_message(conn_, currentUser_.user_id, recipient_id, message_text);
        }
    }
}

    void send_message( const std::string& message) 
    {
        std::cout << "Send-message: " << std::endl;
        ws_.text(true);
        ws_.async_write( net::buffer(message), beast::bind_front_handler(&WebSession::on_write, shared_from_this()));
    }

    void on_write( beast::error_code ec, std::size_t bytes_transferred) 
    {
        if (ec) {
            return fail(ec, "write");
        }
        buffer_.consume(buffer_.size());

        do_read();
    }
};
