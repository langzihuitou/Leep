//
// Created by Admin on 2023/9/5.
//

#include "TCPClientSocket.h"
TCPClientSocket::TCPClientSocket() : TCPSocket()
{
    m_sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sockfd < 0)
    {
        spdlog::error("create client socket error: errno={} errstr={}", errno,strerror(errno));
    }
}

TCPClientSocket::TCPClientSocket(const std::string& ip, int port) : TCPSocket(ip, port)
{
    m_sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sockfd < 0)
    {
        spdlog::error("create client socket error: errno={} errstr={}", errno,strerror(errno));
        return;
    }
    TCPSocket::connect(ip, port);
}

TCPClientSocket::~TCPClientSocket()
{
    close();
}