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
#include <session.h>

class session;

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using json = nlohmann::json;
using tcp = net::ip::tcp;

class listener : public std::enable_shared_from_this<listener>
{
    net::io_context& ioc_;
    tcp::acceptor acceptor_;
    std::shared_ptr<std::string const> doc_root_;
    pqxx::connection& conn_;

private:

    void fail(beast::error_code ec, char const* what)
    {
       std::cerr << what << ": " << ec.message() << "\n";
    }

public:

    listener(net::io_context& ioc, tcp::endpoint endpoint, std::shared_ptr<std::string const> const& doc_root, pqxx::connection& conn)
        : ioc_(ioc), acceptor_(net::make_strand(ioc)), doc_root_(doc_root), conn_(conn)
    {
        beast::error_code ec;

        acceptor_.open(endpoint.protocol(), ec);
        if(ec)
        {
            fail(ec, "open");
            return;
        }

        acceptor_.set_option(net::socket_base::reuse_address(true), ec);
        if(ec)
        {
            fail(ec, "set_option");
            return;
        }

        acceptor_.bind(endpoint, ec);
        if(ec)
        {
            fail(ec, "bind");
            return;
        }

        acceptor_.listen(net::socket_base::max_listen_connections, ec);
        if(ec)
        {
            fail(ec, "listen");
            return;
        }
    }

    void run()
    {
        do_accept();
    }

    void do_accept()
    {
        acceptor_.async_accept(net::make_strand(ioc_),
            beast::bind_front_handler(&listener::on_accept, shared_from_this()));
    }

    void on_accept(beast::error_code ec, tcp::socket socket)
    {
        if(ec)
        {
            fail(ec, "accept");
        }
        else
        {
            auto new_session = std::make_shared<Session>(std::move(socket), doc_root_, conn_);
            new_session->run();
        }

        do_accept();
    }
};