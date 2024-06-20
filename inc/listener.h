#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <pqxx/pqxx>
#include <memory>
#include <string>

//#include "session.h"

namespace net = boost::asio;
using tcp = net::ip::tcp;

class Listener : public std::enable_shared_from_this<Listener>
{
public:
    Listener(net::io_context& ioc, tcp::endpoint endpoint, std::shared_ptr<std::string const> doc_root, pqxx::connection& conn);

    void run();

private:
    net::io_context& m_ioc;
    tcp::acceptor m_acceptor;
    std::shared_ptr<std::string const> m_doc_root;
    pqxx::connection& m_conn;

    void fail(boost::system::error_code ec, const char* what);
    void do_accept();
    void on_accept(boost::system::error_code ec, tcp::socket socket);
};

