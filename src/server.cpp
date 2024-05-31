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
#include <listener.h>
#include <webSession.h>

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using json = nlohmann::json;
using tcp = net::ip::tcp;

class SessionManager;
class WebSession;
class session;
SessionManager session_manager;

void store_message(pqxx::connection& conn, const std::string& sender_id, const std::string& recipient_id, const std::string& message) {
    pqxx::work txn(conn);
    txn.exec_params("INSERT INTO messages (from_user, to_user, text) VALUES ($1, $2, $3)",
                    sender_id, recipient_id, message);
    txn.commit();
}

std::vector<std::string> retrieve_messages(pqxx::connection& conn, const std::string& user_id) {
    pqxx::work txn(conn);
    pqxx::result r = txn.exec_params("SELECT message FROM messages WHERE recipient_id = $1", user_id);
    std::vector<std::string> messages;
    for (auto row : r) {
        messages.push_back(row["message"].c_str());
    }
    return messages;
}


int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cerr <<
            "Usage: http-server-sync <address> <port> <doc_root> <threads>\n" <<
            "Example:\n" <<
            "    http-server-sync 0.0.0.0 8080 . 1\n";
        return EXIT_FAILURE;
    }
    auto const address = net::ip::make_address(argv[1]);
    auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
    auto const doc_root = std::make_shared<std::string>(argv[3]);
    auto const threads = std::max<int>(1, std::atoi(argv[4]));

    net::io_context ioc{threads};

   pqxx::connection conn("dbname=messenger user=postgres password=postgres hostaddr=127.0.0.1 port=5432");

    if (conn.is_open()) {
        std::cout << "Connected to database successfully: " << conn.dbname() << std::endl;

    } else {
        std::cerr << "Failed to connect to database" << std::endl;
        return 1;
    }    std::make_shared<listener>(ioc, tcp::endpoint{address, port}, doc_root, conn)->run();

    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for (auto i = threads - 1; i > 0; --i)
        v.emplace_back(
            [&ioc]
            {
                ioc.run();
            });
    ioc.run();

    return EXIT_SUCCESS;
}
