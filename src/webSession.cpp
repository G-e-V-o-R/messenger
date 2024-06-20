#include "webSession.h"

WebSession::WebSession(tcp::socket socket, const std::string& user_id, pqxx::connection& conn)
    : ws_(std::move(socket)), conn_(conn)
{
    currentUser_.id = user_id;
    currentUser_.name = HandleRequests::findUserNameById(std::stoi(currentUser_.id), conn_);
}

void WebSession::init()
{
    session_manager.add_session(currentUser_.id, shared_from_this());
    std::set<int> senders = retrieve_senders(conn_, currentUser_.id);
    printSet(senders);
    send_my_status(senders, "online");
}

WebSession::~WebSession()
{
    session_manager.remove_session(currentUser_.id);
}

void WebSession::run(http::request<http::string_body> req)
{
    ws_.async_accept(req, beast::bind_front_handler(&WebSession::on_accept, shared_from_this()));
}

void WebSession::on_accept(beast::error_code ec)
{
    if (ec) {
        return fail(ec, "accept");
    }
    do_read();
}

void WebSession::do_read()
{
    ws_.async_read(buffer_, beast::bind_front_handler(&WebSession::on_read, shared_from_this()));
}

void WebSession::on_read(beast::error_code ec, std::size_t bytes_transferred)
{
    if (ec == websocket::error::closed) {
        return;
    }

    if (ec == boost::asio::error::eof) {
        std::cout << "Closing WebSocket" << std::endl;
        std::set<int> senders = retrieve_senders(conn_, currentUser_.id);
        send_my_status(senders, "offline");
        std::cout << "Remove: user" << std::endl;
        session_manager.remove_session(currentUser_.id);
        pqxx::work txn(conn_);
        txn.exec_params("DELETE FROM messages WHERE to_user = $1", currentUser_.id);
        txn.commit();
        return;
    } else if (ec) {
        return fail(ec, "read");
    }

    std::string message = beast::buffers_to_string(buffer_.data());
    std::cout << "Received message: " << message << std::endl;
    handle_message(message);
    buffer_.consume(buffer_.size());
    do_read();
}

void WebSession::handle_message(const std::string& message)
{
	std::cout << "holaaaaaaaaaaaaaaaaaaaaaa" << std::endl; 
    json json_message = json::parse(message);
    std::string type = json_message["type"];

    if (type == "search") {
        std::string email = json_message["email"];
        int recipient_id = HandleRequests::findUserIdByEmail(email, conn_);
        std::string quary = "INSERT INTO messages (from_user, to_user, text) VALUES ('" +currentUser_.id + "', '" + std::to_string(recipient_id) + "', '')";

		pqxx::work txn(conn_);
        txn.exec(quary);
        txn.commit();
		quary = "INSERT INTO messages (from_user, to_user, text) VALUES ('" + std::to_string(recipient_id) + "', '" +currentUser_.id + "', '')";

		pqxx::work txn1(conn_);
        txn1.exec(quary);
        txn1.commit();
        
		auto recipient_session = session_manager.get_session(std::to_string(recipient_id));
        std::string net_status;
        if (recipient_session) {
            net_status = "online";
        } else {
            net_status = "offline";
        }

        json response = {
            {"type", "search_result"},
            {"user_id", recipient_id},
            {"target_name", email},
            {"net_status", net_status}
        };

        send_message(response.dump());
    } else {
        std::string recipient_id = json_message["recipient_id"];
        std::string sender_id = json_message["sender_id"];
        std::string sender_name = json_message["sender_name"];
        std::string message_text = json_message["message"];

        if (recipient_id != "-1") {
            auto recipient_session = session_manager.get_session(recipient_id);
            if (recipient_session) {
                std::cout << "Send ONLINE message: " << std::endl;
                std::string formated_message = sender_id + ":" + message_text;
                recipient_session->send_message(message);
                store_message(sender_id, currentUser_.id, message_text);
            } else {
                std::cout << "Message is in DATABASE: " << std::endl;
                store_message(currentUser_.id, recipient_id, message_text);
            }
        }
    }
}

void WebSession::send_message(const std::string& message)
{
    ws_.text(true);
    ws_.async_write(net::buffer(message), beast::bind_front_handler(&WebSession::on_write, shared_from_this()));
}

void WebSession::on_write(beast::error_code ec, std::size_t bytes_transferred)
{
    if (ec) {
        return fail(ec, "write");
    }
    buffer_.consume(buffer_.size());
}

void WebSession::send_my_status(std::set<int>& senders, const std::string&& net_status)
{
    std::cout << "\033[32m" << "send_my_status() : " << net_status << "\033[0m" << std::endl;
    printSet(senders);

    for (int elem : senders) {
        auto recipient_session = session_manager.get_session(std::to_string(elem));
        if (recipient_session) {
            json update_status = {
                {"type", "status_update"},
                {"target_id", currentUser_.id},
                {"net_status", net_status}
            };
            recipient_session->send_message(update_status.dump());
            std::cout << "\033[32m" << "send status " << net_status << " to user: "<< elem << "\033[0m" << std::endl;
        }
    }
}

void WebSession::store_message(const std::string& sender_id, const std::string& recipient_id, const std::string& message)
{
    pqxx::work txn(conn_);
    txn.exec_params("INSERT INTO messages (from_user, to_user, text) VALUES ($1, $2, $3)",
                    sender_id, recipient_id, message);
    txn.commit();
}

void WebSession::printSet(const std::set<int>& s)
{
    std::cout << "\033[33m";
    std::cout << "Printing set elements:" << std::endl;

    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << std::endl;
    }

    std::cout << "\033[0m";
}

void WebSession::fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

std::set<int> WebSession::retrieve_senders(pqxx::connection& conn, const std::string& user_id)
{
    std::cout << "\033[32m" << "retreve_senders(): " << "\033[0m" << std::endl;

    pqxx::work txn(conn);
    pqxx::result r = txn.exec_params("SELECT from_user FROM messages WHERE to_user = $1", user_id);
    std::set<int> senders;
    for (auto row : r) {
        senders.insert(row["from_user"].as<int>());
    }

    txn.commit();
    return senders;
}
