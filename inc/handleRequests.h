#pragma once

#include <boost/beast/core.hpp>       
#include <boost/beast/http.hpp>       
#include <boost/asio/ip/tcp.hpp>      
#include <pqxx/pqxx>                  
#include <nlohmann/json.hpp>          
#include <string>                     


namespace beast = boost::beast; 
namespace http = beast::http;   
namespace net = boost::asio;      
using tcp = boost::asio::ip::tcp; 
using json = nlohmann::json;

struct user;
class SessionManager;
class WebSession;
extern SessionManager session_manager;

extern std::multimap<int, std::string> retrieve_messages_with_sender(pqxx::connection& conn, const std::string& user_id);

class HandleRequests{
public:
    static std::multimap<int, std::string> retrieve_messages_with_sender(pqxx::connection& conn, const std::string& user_id);

	static std::string gen_session_id(size_t&& length);
	static void fail(beast::error_code ec, char const* what);


    template <class Body, class Allocator>
    static http::message_generator find_user_id_by_email(
        const http::request<Body, http::basic_fields<Allocator>>& req,
        pqxx::connection& conn);

	template <class Body, class Allocator>
    http::response<http::string_body>  static make_response(
        http::status status, const std::string& body,
        const http::request<Body, http::basic_fields<Allocator>>& req,
	        const std::string&& content_type);

    template <class Body, class Allocator>
    http::message_generator static registration(
        const http::request<Body, http::basic_fields<Allocator>>& req,
        pqxx::connection& conn);

	template <class Body, class Allocator>
    http::message_generator  static log_in(
        http::request<Body, http::basic_fields<Allocator>>& req,
        pqxx::connection& conn, user& currentUser);
    
	template <class Body, class Allocator>
    http::message_generator static log_out(
        const http::request<Body, http::basic_fields<Allocator>>& req,
        pqxx::connection& conn,
        SessionManager& sessionManager);
    
	template <class Body, class Allocator>
    http::message_generator
    	static handle_request(
    	beast::string_view doc_root,
    	http::request<Body, http::basic_fields<Allocator>>&& req,
    	pqxx::connection& conn, user& currentUser);

public:
static int findUserIdByEmail(const std::string& email, pqxx::connection& conn);
static std::string findUserNameById(const int& id, pqxx::connection& conn);
};
