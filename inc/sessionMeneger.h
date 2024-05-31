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
#include "webSession.h"

// Forward declaration
class WebSession;

 
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class SessionManager {
public:

void add_session(const std::string& user_id, std::shared_ptr<WebSession> session) 
{
    std::lock_guard<std::mutex> lock(mutex_);
    sessions_[user_id] = session;
}

std::shared_ptr<WebSession> get_session(const std::string& user_id) 
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = sessions_.find(user_id);
    if (it != sessions_.end()) {
        return it->second;
    }
    return nullptr;
}

void remove_session(const std::string& user_id) 
{
    std::lock_guard<std::mutex> lock(mutex_);
    sessions_.erase(user_id);
}


private:

std::unordered_map<std::string, std::shared_ptr<WebSession>> sessions_;
std::mutex mutex_;

};
