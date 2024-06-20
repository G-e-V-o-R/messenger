#include "session.h"
#include "webSession.h" // Assuming necessary for WebSession
#include "handleRequests.h"   // Assuming necessary for HandleRequests

#include <iostream>

Session::Session(tcp::socket&& socket, std::shared_ptr<std::string const> const& doc_root, pqxx::connection& conn)
    : stream_(std::move(socket)), doc_root_(doc_root), conn_(conn)
{
    std::cout << "New session starts: " << std::endl;
}

void Session::run()
{
    net::dispatch(stream_.get_executor(),
                  beast::bind_front_handler(&Session::do_read, shared_from_this()));
}

void Session::fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void Session::send_response(http::message_generator&& msg)
{
    bool keep_alive = msg.keep_alive();
    beast::async_write(stream_, std::move(msg),
                       beast::bind_front_handler(&Session::on_write, shared_from_this(), keep_alive));
}

void Session::do_read()
{
    req_ = {};
    stream_.expires_after(std::chrono::seconds(30));
    http::async_read(stream_, buffer_, req_,
                     beast::bind_front_handler(&Session::on_read, shared_from_this()));
}

void Session::get_user_id_from_session_id()
{
    pqxx::work txn{conn_};
    pqxx::result res = txn.exec("SELECT user_id FROM sessions WHERE session_id = '" + currentUser_.session_id + "'");
    txn.commit();

    if (!res.empty()) {
        currentUser_.id = res[0][0].as<std::string>();
        std::cout << "user_id : " << currentUser_.id << std::endl;
    } else {
        throw std::runtime_error("Session ID not found in database");
    }
}

void Session::on_read(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (ec == http::error::end_of_stream)
        return do_close();

    if (ec)
        return fail(ec, "read");

    if (websocket::is_upgrade(req_)) {
        if (req_.base().find("Session-ID") != req_.base().end()) {
            currentUser_.session_id = std::string(req_.base().at("Session-ID"));
            std::cout << currentUser_.session_id << std::endl;
        } else {
            std::cout << "Header error: " << std::endl;
        }

        try {
            get_user_id_from_session_id();
            auto web_session = std::make_shared<WebSession>(stream_.release_socket(), currentUser_.id, conn_);
            web_session->init();
            web_session->run(std::move(req_));
        } catch (const std::exception& e) {
            std::cerr << "Error finding user by session_id: " << e.what() << std::endl;
            return fail(ec, "session_id not found");
        }
        return;
    }

    send_response(HandleRequests::handle_request(*doc_root_, std::move(req_), conn_, currentUser_));
}

void Session::on_write(bool keep_alive, beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);
    if (ec)
        return fail(ec, "write");
    if (!keep_alive)
        return do_close();

    do_read();
}

void Session::do_close()
{
    beast::error_code ec;
    stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
    std::cout << "Session is closed" << std::endl;
}

