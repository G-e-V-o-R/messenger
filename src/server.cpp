#include <boost/beast/core.hpp>//
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
#include <map>
#include <listener.h>
#include <webSession.h>

namespace beast = boost::beast;//
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using json = nlohmann::json;
using tcp = net::ip::tcp;

class SessionManager;
class WebSession;
class session;
SessionManager session_manager;


std::multimap<int, std::string> retrieve_messages_with_sender(pqxx::connection& conn, const std::string& user_id){
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


int main(int argc, char* argv[])
{

    if( argc != 5 )
    {
        std::cerr << "run program like this: ip, port, doc_root_path, thread-counts \n"
        << "example 127.0.0.1, 8080, ., 2"; 
        return EXIT_FAILURE;
    }

    net::ip::address address = net::ip::make_address(argv[1]);
    net::ip::port_type port = static_cast<unsigned short>(std::stoi(argv[2]));
    auto const doc_root = std::make_shared<std::string>(argv[3]);
    int threads = std::max(1, std::atoi(argv[4]));

    // DB code
    pqxx::connection conn("dbname=messenger user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
    if(conn.is_open())
    {
        std::cout << "Connected to DB" << std::endl;
		pqxx::work txn(conn);
    	txn.exec("DELETE FROM " + txn.quote_name("messages"));
    	txn.commit();
    }else
    {
        std::cout << "Connection to DB failed";
        return EXIT_FAILURE;
    }

    net::io_context ioc {threads};
    std::make_shared<Listener>(ioc, tcp::endpoint{address, port}, doc_root, conn)->run();

    std::vector<std::thread> thread_vector;
    thread_vector.reserve(threads-1);

    for(int i = 0; i < threads-1; ++i){
        thread_vector.emplace_back([&ioc]{ioc.run();});
    }
    ioc.run();


    return EXIT_SUCCESS;

}
