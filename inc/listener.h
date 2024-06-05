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

class Listener : public std::enable_shared_from_this<Listener>
{
    net::io_context& m_ioc;
    tcp::acceptor m_acceptor;
    std::shared_ptr<std::string const> m_doc_root;
    pqxx::connection& m_conn;

    void fail(beast::error_code ec, const char* what){
        std::cerr << what << " : " << ec.message();
    }

    void do_accept(){
        m_acceptor.async_accept(net::make_strand(m_ioc),
                                beast::bind_front_handler(&Listener::on_accept, shared_from_this()));
    }

    void on_accept(beast::error_code ec, tcp::socket socket){
        if(ec){
            fail(ec, "accept");
        }else{
            std::make_shared<Session>(std::move(socket), m_doc_root, m_conn)->run();
        }

        do_accept();
    }

    public:

    Listener(net::io_context& ioc, tcp::endpoint endpoint, std::shared_ptr<std::string const> doc_root, pqxx::connection& conn)
    : m_ioc(ioc), m_acceptor(net::make_strand(ioc)), m_doc_root(doc_root), m_conn(conn)
    {
        beast::error_code ec;

        m_acceptor.open(endpoint.protocol(), ec);
        m_acceptor.set_option(net::socket_base::reuse_address(true), ec);
        m_acceptor.bind(endpoint, ec);
        m_acceptor.listen(net::socket_base::max_listen_connections, ec);
    }

    void run(){
        do_accept();
    }
};