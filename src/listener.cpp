#include "listener.h"
#include "session.h"
#include <iostream>

Listener::Listener(net::io_context& ioc, tcp::endpoint endpoint, std::shared_ptr<std::string const> doc_root, pqxx::connection& conn)
    : m_ioc(ioc), m_acceptor(net::make_strand(ioc)), m_doc_root(doc_root), m_conn(conn)
{
    boost::system::error_code ec;

    m_acceptor.open(endpoint.protocol(), ec);
    if (ec) {
        fail(ec, "open");
        return;
    }

    m_acceptor.set_option(net::socket_base::reuse_address(true), ec);
    if (ec) {
        fail(ec, "set_option");
        return;
    }

    m_acceptor.bind(endpoint, ec);
    if (ec) {
        fail(ec, "bind");
        return;
    }

    m_acceptor.listen(net::socket_base::max_listen_connections, ec);
    if (ec) {
        fail(ec, "listen");
        return;
    }
}

void Listener::run()
{
    do_accept();
}

void Listener::fail(boost::system::error_code ec, const char* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void Listener::do_accept()
{
    m_acceptor.async_accept(net::make_strand(m_ioc),
                            beast::bind_front_handler(&Listener::on_accept, shared_from_this()));
}

void Listener::on_accept(boost::system::error_code ec, tcp::socket socket)
{
    if (ec) {
        fail(ec, "accept");
    } else {
        std::make_shared<Session>(std::move(socket), m_doc_root, m_conn)->run();
    }

    do_accept();
}

