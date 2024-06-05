#include <boost/beast/core.hpp>        // Required for handling HTTP requests and responses using the Boost Beast library.
#include <boost/beast/http.hpp>        // Necessary for HTTP-related functionalities, such as parsing HTTP requests and generating HTTP responses.
#include <boost/beast/version.hpp> 
#include <boost/asio/ip/tcp.hpp>
    // Provides version information for the Boost Beast library.
#include <pqxx/pqxx>                   // Needed for interacting with PostgreSQL databases using the pqxx library.
#include <nlohmann/json.hpp>           // Required for parsing and serializing JSON data using the nlohmann JSON library.
#include <iostream>                    // Used for printing messages to the standard output stream. Useful for debugging and logging purposes.
#include <string>                      // Used for handling strings, which are essential for various operations, such as string manipulation and concatenation.
#include <chrono>                      // Utilized for timing-related functionality, such as measuring execution time or scheduling tasks.
#include <cstdlib>                     // Needed for accessing environment variables using std::getenv. This can be useful for obtaining configuration or system-related information.
#include <user.h>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/stream.hpp>
#include <boost/beast/websocket/detail/mask.hpp> // Ensure this include is present
#include <boost/beast/websocket/detail/hybi13.hpp> // Include for make_sec_ws_key
#include <boost/beast/core/detail/base64.hpp>
#include <boost/beast/core/detail/base64.ipp>




extern std::multimap<int, std::string> retrieve_messages_with_sender(pqxx::connection& conn, const std::string& user_id);


namespace beast = boost::beast; 
namespace http = beast::http;   
namespace net = boost::asio;      
using tcp = boost::asio::ip::tcp; 
using json = nlohmann::json;

class WebSession;

class HandleRequests{
private:

static
beast::string_view mime_type(beast::string_view path) {
    static const std::unordered_map<std::string, std::string> mime_types = {
        {".json", "application/json"},
        {".txt", "text/plain"},
        {".png", "image/png"},
        {".jpe", "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".jpg", "image/jpeg"},
        {".gif", "image/gif"},
        {".bmp", "image/bmp"},
        {".ico", "image/vnd.microsoft.icon"}
    };

    auto const pos = path.rfind(".");
    if (pos != beast::string_view::npos) {
        auto ext = path.substr(pos);
        auto it = mime_types.find(ext);
        if (it != mime_types.end()) {
            return it->second;
        }
    }

    return "application/text";
}

// Append an HTTP rel-path to a local filesystem path.
// The returned path is normalized for the platform.
static std::string path_cat(beast::string_view base, beast::string_view path)
{
    if (base.empty())
        return std::string(path);

    std::string result(base);
    char constexpr path_separator = '/';
    if (result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
    for (auto& c : result)
        if (c == '/')
            c = path_separator;

    return result;
}
     
static std::string gen_session_id(size_t&& length){
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

static int findUserIdByEmail(const std::string& email, pqxx::connection& conn) {
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



static void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}
public:

    template <class Body, class Allocator>
    static http::message_generator find_user_id_by_email(
        const http::request<Body, http::basic_fields<Allocator>>& req,
        pqxx::connection& conn)
    {
        // Extract email from the request body
        beast::string_view body = req.body();
        json json_body = json::parse(body);
        std::string email = json_body["email"];

        // Find user ID based on email
        int user_id = findUserIdByEmail(email, conn);

        // Prepare response based on the result
        if (user_id != -1) {
            // User found, return user ID in the response
            json response_body = {
                {"user_id", user_id}
            };
            std::string json_string = response_body.dump();
            return make_response(http::status::ok, json_string, req, "application/json");
        } else {
            // User not found, return error response
            std::string error_message = "User not found for email: " + email;
            return make_response(http::status::not_found, error_message, req, "text/plain");
        }
    }

    template <class Body, class Allocator>
    http::response<http::string_body>  static make_response(
        http::status status, const std::string& body,
        const http::request<Body, http::basic_fields<Allocator>>& req,
        const std::string&& content_type)
    {
        http::response<http::string_body> res{status, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, content_type);
        res.keep_alive(req.keep_alive());
        res.body() = body;
        res.prepare_payload();
        return res;
    }
  
  





#include <boost/beast/core/detail/base64.hpp>

template <class Body, class Allocator>
static boost::beast::http::message_generator websocket_upgrade_response(
    const boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>>& req) {
    namespace http = boost::beast::http;

        // Generate the WebSocket response
        http::response<http::empty_body> res{http::status::switching_protocols, req.version()};
        res.set(http::field::upgrade, "websocket");
        res.set(http::field::connection, "Upgrade");

        // Generate the Sec-WebSocket-Accept header
        std::string key = req[http::field::sec_websocket_key];
        boost::beast::websocket::detail::sec_ws_key_type accept_key;
        
        // Copy the key into the accept_key buffer
        std::copy(key.begin(), key.end(), accept_key.begin());

        // Ensure the accept_key is correctly null-terminated
        accept_key[key.size()] = '\0';

        // Generate the accept key
        boost::beast::websocket::detail::make_sec_ws_key(accept_key);

        // Encode the accept key to base64
        std::string accept_key_base64;
        boost::beast::detail::base64::encode(&accept_key_base64, accept_key.data(), accept_key.size());

        res.set(http::field::sec_websocket_accept, accept_key_base64);

        return res;
}












    
    template <class Body, class Allocator>
    http::message_generator static registration(
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
    http::message_generator  static log_in(
        http::request<Body, http::basic_fields<Allocator>>& req,
        pqxx::connection& conn)
    {
        beast::string_view body = req.body();
        json json_body = json::parse(body);
        std::string currentUser_email = json_body["email"];
        std::string currentUser_password = json_body["password"];
        try{
            pqxx::work txn(conn);
            std::string query = "SELECT COUNT(*) FROM users WHERE email = " + txn.quote(currentUser_email) + " AND password_hash = " + txn.quote(currentUser_password)+"";
            pqxx::result result = txn.exec_params(query);
            int count = result[0][0].as<int>();
    
            if (count == 1){
                
                std::string currentUser_sessionId = gen_session_id(32);
                pqxx::result id = txn.exec("SELECT id FROM users WHERE email = " + txn.quote(currentUser_email));
                int currentUser_userId = id[0][0].as<int>(); 
                //save them in database
     
                txn.exec("INSERT INTO sessions (user_id, session_id) VALUES (" +
                txn.quote(currentUser_userId) + ", " + 
                txn.quote(currentUser_sessionId) + ")");
                txn.commit();

                std::multimap<int, std::string> messages = retrieve_messages_with_sender(conn, std::to_string(currentUser_userId));


                json response_body = {
                    {"session_id", currentUser_sessionId},
                    {"messages", json::array()}
                };

                for (const auto& message : messages) {
                    json message_json;
                    message_json["sender_id"] = message.first;
                    message_json["message"] = message.second;
                    response_body["messages"].push_back(message_json);
                }

                // Serialize JSON to string
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
    http::message_generator static log_out(
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
            // Delete the session row from the database based on the session ID
            txn2.exec("DELETE FROM sessions WHERE session_id = " + txn2.quote(currentUser_sessionId));
            txn2.commit();

            // Remove the associated WebSession from the SessionManager
            sessionManager.remove_session(std::to_string(currentUser_user_id));

            // Respond with a success message
            std::string resBody = "Successfully logged out";
            return make_response(http::status::ok, resBody, req, "text/plain");
        } catch (const std::exception& e) {
            std::string resBody = "Database error occurred: " + std::string(e.what());
            return make_response(http::status::internal_server_error, resBody, req, "text/plain");
        }
    }





    template <class Body, class Allocator>
    http::message_generator
    static handle_request(
    beast::string_view doc_root,
    http::request<Body, http::basic_fields<Allocator>>&& req,
    pqxx::connection& conn)
{

    if (req.method() == http::verb::post && req.target() == "/registration")
    {
        return registration(req, conn);
    }

    if (req.method() == http::verb::post && req.target() == "/login")
    {
        return log_in(req, conn);
    }

    if (req.method() == http::verb::post && req.target() == "/logout") 
    {
        return log_out(req, conn, session_manager);
    }

    if (req.method() == http::verb::post && req.target() == "/search") 
    {
        return find_user_id_by_email(req, conn);
    }

    // if (websocket::is_upgrade(req)) 
    // {
    //     beast::error_code ec;

    //     if (req.base().find("Session-ID") != req.base().end()) {
    //         currentUser.session_id = std::string(req.base().at("Session-ID"));
    //     }else{
    //         return make_response(http::status::bad_request, "session_id not found", req, "text/plain");
    //     }

    //     try {
    //         get_user_id_from_session_id(conn, currentUser);
    //         auto web_session = std::make_shared<WebSession>(stream, currentUser.user_id, conn);
    //         web_session->init();
    //         web_session->run(std::move(req));
    //         //return make_response(http::status::accepted, "Connection was upgrated to Websocket", req, "text/plain");

    //     } catch (const std::exception& e) {
    //         std::cerr << "Error finding user by session_id: " << e.what() << std::endl;
    //         return make_response(http::status::bad_request, "session_id not found", req, "text/plain");
    //     }
    // }

    // Make sure we can handle the method
    if( req.method() != http::verb::get &&
        req.method() != http::verb::head)
        return make_response(http::status::bad_request, "Unknown HTTP-method", req, "text/html");

    // Request path must be absolute and not contain "..".
    if( req.target().empty() ||
        req.target()[0] != '/' ||
        req.target().find("..") != beast::string_view::npos)
        return make_response(http::status::bad_request, "Illegal request-target", req, "text/html");



    // Build the path to the requested file
    std::string path = path_cat(doc_root, req.target());
    if(req.target().back() == '/')
        path.append("index.html");

    // Attempt to open the file
    beast::error_code ec;
    http::file_body::value_type body;
    body.open(path.c_str(), beast::file_mode::scan, ec);

    // Handle the case where the file doesn't exist
    if(ec == beast::errc::no_such_file_or_directory)
        return make_response(http::status::not_found, req.target(), req, "text/html");

    // Handle an unknown error
    if(ec)
        return make_response(http::status::internal_server_error, ec.message(), req, "text/html");

    // Cache the size since we need it after the move
    auto const size = body.size();

   // Respond to HEAD request
    if(req.method() == http::verb::head)
    {
        http::response<http::empty_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, mime_type(path));
        res.content_length(size);
        res.keep_alive(req.keep_alive());
        return res;
    }

    //Respond to GET request
    http::response<http::file_body> res{
    std::piecewise_construct,
    std::make_tuple(std::move(body)),
    std::make_tuple(http::status::ok, req.version())};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, mime_type(path));
    res.content_length(size);
    res.keep_alive(req.keep_alive());
    return res;
}
};
