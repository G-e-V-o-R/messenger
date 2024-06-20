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
#include "user.h"
#include "handleRequests.h"
#include "nlohmann/json.hpp"

class SessionManager;
extern SessionManager session_manager;

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using json = nlohmann::json;

class WebSession : public std::enable_shared_from_this<WebSession> {
public:
    explicit WebSession(tcp::socket socket, const std::string& user_id, pqxx::connection& conn);
	~WebSession();
    void init();
    void run(http::request<http::string_body> req);
    void send_message(const std::string& message);
	
private:
    void send_my_status(std::set<int>& senders, const std::string&& net_status);
    void store_message(const std::string& sender_id, const std::string& recipient_id, const std::string& message);
    void printSet(const std::set<int>& s);
    void fail(beast::error_code ec, char const* what);
    std::set<int> retrieve_senders(pqxx::connection& conn, const std::string& user_id);
    void on_accept(beast::error_code ec);
    void do_read();
    void on_read(beast::error_code ec, std::size_t bytes_transferred);
    void handle_message(const std::string& message);
    void on_write(beast::error_code ec, std::size_t bytes_transferred);

    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;
    user currentUser_;
    pqxx::connection& conn_;
};
