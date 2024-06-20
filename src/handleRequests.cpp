#include "handleRequests.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp> 
#include <boost/asio/ip/tcp.hpp>
#include <pqxx/pqxx>          
#include <nlohmann/json.hpp>  
#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib> 
#include <user.h>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/stream.hpp>
#include "sessionMeneger.h"


extern SessionManager session_manager;


namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using json = nlohmann::json;

/*
std::multimap<int, std::string> HandleRequests::retrieve_messages_with_sender(pqxx::connection& conn, const std::string& user_id){
    pqxx::work txn(conn);
    pqxx::result r = txn.exec_params("SELECT from_user, text FROM messages WHERE to_user = $1", user_id);
    std::multimap<int, std::string> messages;
    for (auto row : r) {
		if (row["text"].c_str() != "")
        	messages.insert({row["from_user"].as<int>(), row["text"].c_str()});
    }

    txn.commit();
    
    return messages;
}
*/

std::string HandleRequests::gen_session_id(size_t&& length){
    std::string randomString;
    const char characters[] = "0123456789"
                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                              "abcdefghijklmnopqrstuvwxyz";

    std::default_random_engine engine{std::random_device{}()};
    std::uniform_int_distribution<int> range(0, sizeof(characters)-2);
    for (size_t i = 0; i < length; ++i){
        randomString += characters[range(engine)];
    }
    return randomString;
}


void HandleRequests::fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

int HandleRequests::findUserIdByEmail(const std::string& email, pqxx::connection& conn) {
        try {
            pqxx::work txn(conn);
            pqxx::result result = txn.exec("SELECT id FROM users WHERE email = " + txn.quote(email));
            txn.commit();
            if (!result.empty()) {
                return result[0][0].as<int>();
            } else {
                return -1;
            }
        } catch (const std::exception& e) {
            std::cerr << "Database error: " << e.what() << std::endl;
            return -1;
        }
}

template <class Body, class Allocator>
http::message_generator HandleRequests::find_user_id_by_email(
        const http::request<Body, http::basic_fields<Allocator>>& req,
        pqxx::connection& conn)
    {
        beast::string_view body = req.body();
        json json_body = json::parse(body);
        const std::string email = json_body["email"];

        int user_id = findUserIdByEmail(email, conn);
        if (user_id != -1) {
            json response_body = {
                {"user_id", user_id}
            };
            std::string json_string = response_body.dump();
            std::cout << "find id: " << user_id << std::endl;
            std::cout << "find: " << json_string << std::endl;

            return make_response(http::status::ok, json_string, req, "application/json");
        } else {
            std::string error_message = "User not found for email: " + email;
            return make_response(http::status::not_found, error_message, req, "text/plain");
        }
    }

template <class Body, class Allocator>
http::response<http::string_body>  HandleRequests::make_response(
        http::status status, const std::string& body,
        const http::request<Body, http::basic_fields<Allocator>>& req,
        const std::string&& content_type)
    {
        http::response<http::string_body> res{status, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, content_type);
        res.keep_alive(req.keep_alive());
        std::cout << "make_response(): " << body << std::endl;
        res.body() = body;
        res.prepare_payload();
        return res;
    }

    
template <class Body, class Allocator>
http::message_generator HandleRequests::registration(
        const http::request<Body, http::basic_fields<Allocator>>& req,
        pqxx::connection& conn)
    {    

        beast::string_view body = req.body();
        json json_body = nlohmann::json::parse(body.data(), body.data()+body.size());
        const std::string currentUser_email = json_body["email"];
        const std::string currentUser_password = json_body["password"];
		std::string quary = "INSERT INTO users (email, password_hash) VALUES ('"+currentUser_email+"', '"+currentUser_password+"')";

        try {
            pqxx::work txn(conn);
            txn.exec(quary);
            txn.commit();
            std::cout << "Inserted email and password into the database" << std::endl;
            std::string resBody = "Successfully registered user";
        
            return make_response(http::status::ok, resBody, req, "tetx/plain"); 

        } catch (const std::exception &e) {
            std::string resBody = "Database error occurred: " + std::string(e.what());
            return make_response(http::status::internal_server_error, resBody, req, "text/plain");
        }


	}

template <class Body, class Allocator>
http::message_generator 
	HandleRequests::log_in(
        http::request<Body, http::basic_fields<Allocator>>& req,
        pqxx::connection& conn, user& currentUser)
    {
        beast::string_view body = req.body();
        json json_body = json::parse(body);
        currentUser.name = json_body["email"];
        currentUser.password = json_body["password"];
        try{
            pqxx::work txn(conn);
            std::string query = "SELECT COUNT(*) FROM users WHERE email = " + txn.quote(currentUser.name) + " AND password_hash = " + txn.quote(currentUser.password)+"";
            pqxx::result result = txn.exec_params(query);
            int count = result[0][0].as<int>();
    
            if (count == 1){
                currentUser.net_status = "online";
                currentUser.session_id = gen_session_id(32);
				
                pqxx::result id = txn.exec("SELECT id FROM users WHERE email = " + txn.quote(currentUser.name));
                currentUser.id = id[0][0].as<std::string>(); 
				txn.quote(currentUser.id);

                txn.exec("INSERT INTO sessions (user_id, session_id) VALUES (" +
                txn.quote(currentUser.id) + ", " + 
                txn.quote(currentUser.session_id) + ")");
                txn.commit();

                std::multimap<int, std::string> messages = retrieve_messages_with_sender(conn, currentUser.id);

                json response_body = {
                    {"session_id", currentUser.session_id},
                    {"user_id", currentUser.id},
					{"user_name", currentUser.name},
                    {"messages", json::array()}
                };

                for (const auto& message : messages) {
                    json message_json;
                    message_json["sender_id"] = message.first;
					message_json["sender_name"] = findUserNameById(message.first, conn);
					pqxx::work txn(conn);
					pqxx::result result = txn.exec("SELECT status FROM users WHERE id = " + txn.quote(message.first));
					std::string userStatus = result[0][0].as<std::string>();
					if (userStatus == "online"){
						message_json["net_status"] = "online";
					}else{
						message_json["net_status"] = "offline";
					}
                    message_json["message"] = message.second;
                    response_body["messages"].push_back(message_json);
                }
				txn.commit();

                std::string json_string = response_body.dump();

                return make_response(http::status::ok, json_string, req, "text/plain");
            }else{
                std::string resBody = "Invalid username or password";
                return make_response(http::status::not_found, resBody, req, "text/plain");
            }
        }catch(std::exception& ec){
            std::string resBody = std::string(ec.what());
            return make_response(http::status::internal_server_error, resBody, req, "text/plain");
        }
    }

 
template <class Body, class Allocator>
http::message_generator 
	HandleRequests::log_out(
        const http::request<Body, http::basic_fields<Allocator>>& req,
        pqxx::connection& conn,
        SessionManager& sessionManager)
    {
        auto it = req.base().find("Session-ID");

        if (it == req.base().end()) {
            std::string resBody = "Session-ID header not found";
            return make_response(http::status::bad_request, resBody, req, "text/plain");
        }
        std::string currentUser_sessionId = std::string(it->value());
    
        try {

            pqxx::work txn(conn);
            pqxx::result id = txn.exec("SELECT user_id FROM sessions WHERE session_id = " + txn.quote(currentUser_sessionId));
            int currentUser_user_id = id[0][0].as<int>();
            txn.commit();

            pqxx::work txn2(conn);
            txn2.exec("DELETE FROM sessions WHERE session_id = " + txn2.quote(currentUser_sessionId));
            txn2.commit();
            
			sessionManager.remove_session(std::to_string(currentUser_user_id));
            std::string resBody = "Successfully logged out";
            return make_response(http::status::ok, resBody, req, "text/plain");
        } catch (const std::exception& e) {
            std::string resBody = "Database error occurred: " + std::string(e.what());
            return make_response(http::status::internal_server_error, resBody, req, "text/plain");
        }
    }




template <class Body, class Allocator>
http::message_generator
    HandleRequests::handle_request(
    beast::string_view doc_root,
    http::request<Body, http::basic_fields<Allocator>>&& req,
    pqxx::connection& conn, user& currentUser)
{

    if (req.method() == http::verb::post && req.target() == "/registration")
    {
        return registration(req, conn);
    }

    if (req.method() == http::verb::post && req.target() == "/login")
    {
        return log_in(req, conn, currentUser);
    }

    if (req.method() == http::verb::post && req.target() == "/logout") 
    {
        return log_out(req, conn, session_manager);
    }

}


std::string HandleRequests::findUserNameById(const int& id, pqxx::connection& conn) {
        try {
            pqxx::work txn(conn);
            pqxx::result result = txn.exec("SELECT email FROM users WHERE id = " + txn.quote(id));
            txn.commit();
            if (!result.empty()) {
                return result[0][0].as<std::string>();
            } else {
                return "Deleted user";
            }
        } catch (const std::exception& e) {
            std::cerr << "Database error: " << e.what() << std::endl;
        }
}

