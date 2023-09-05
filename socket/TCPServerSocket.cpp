//
// Created by Admin on 2023/9/5.
//

#include "TCPServerSocket.h"
TCPServerSocket::TCPServerSocket() : TCPSocket()
{
}

TCPServerSocket::TCPServerSocket(const std::string &ip, int port) : TCPSocket(ip, port)
{
    m_sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sockfd < 0)
    {
        spdlog::error("create server socket error: errno={} errstr={}", errno,strerror(errno));
        return;
    }

    set_non_blocking();
    set_recv_buffer(10 * 1024);
    set_send_buffer(10 * 1024);
    set_linger(true, 0);
    set_keep_alive();
    set_reuse_addr();
    bind(ip, port);
    listen(1024);
}

TCPServerSocket::~TCPServerSocket()
{
    close();
}