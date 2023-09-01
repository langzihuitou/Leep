//
// Created by Admin on 2023/9/1.
//

#include "TCPSocket.h"

TCPSocket::TCPSocket():m_sockfd(0){}
TCPSocket::TCPSocket(const std::string &ip, int port):m_ip(ip), m_port(port), m_sockfd(0){}

//调用 close() 方法关闭套接字
TCPSocket:: ~TCPSocket()
{
    close();
}
//绑定套接字到指定 IP 地址和端口号
bool TCPSocket::bind(const std::string &ip, int port)
{
    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    if (ip != "")
    {
        sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    }
    else
    {
        sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    sockaddr.sin_port = htons(port);

    if (::bind(m_sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        spdlog::error("socket bind error: errno={} errstr={}", errno,strerror(errno));
        return false;
    }
    return true;
}
//开始监听套接字上的连接请求
bool TCPSocket::listen(int backlog)
{
    if (::listen(m_sockfd, backlog) < 0)
    {
        spdlog::error("socket listen error: errno={} errstr={}", errno,strerror(errno));
        return false;
    }
    return true;
}
//和指定的 IP 地址和端口号建立连接
bool TCPSocket::connect(const std::string &ip, int port)
{
    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);
    if (::connect(m_sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        spdlog::error("socket connect error: errno={} errstr={}", errno,strerror(errno));
        return false;
    }
    return true;
}
//关闭套接字
bool TCPSocket::close()
{
    if (m_sockfd > 0)
    {
        ::close(m_sockfd);
        m_sockfd = 0;
    }
    return true;
}
//接受连接请求，返回新的连接套接字
int TCPSocket::accept()
{
    int sockfd = ::accept(m_sockfd, NULL, NULL);
    if (sockfd < 0)
    {
        spdlog::error("socket call error: errno={} errstr={}", errno,strerror(errno));
        sockfd = -1;
    }
    return sockfd;
}
//接收数据
int TCPSocket::recv(char * buf, int len)
{
    return ::recv(m_sockfd, buf, len, 0);
}
//发送数据
int TCPSocket::send(const char * buf, int len)
{
    return ::send(m_sockfd, buf, len, 0);
}
//设置套接字为非阻塞模式
bool TCPSocket::set_non_blocking()
{
    int flags = fcntl(m_sockfd, F_GETFL, 0);
    if (flags < 0)
    {
        spdlog::error("Socket::set_non_blocking(F_GETFL, O_NONBLOCK): errno={} errstr={}", errno,strerror(errno));
        return false;
    }
    flags |= O_NONBLOCK;
    if (fcntl(m_sockfd, F_SETFL, flags) < 0)
    {
        spdlog::error("Socket::set_non_blocking(F_SETFL, O_NONBLOCK): errno={} errstr={}", errno,strerror(errno));
        return false;
    }
    return true;
}
//设置发送缓冲区大小
bool TCPSocket::set_send_buffer(int size)
{
    int buff_size = size;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_SNDBUF, &buff_size, sizeof(buff_size)) < 0)
    {
        spdlog::error("socket set send buffer error: errno={} errstr={}", errno,strerror(errno));
        return false;
    }
    return true;
}
//设置接收缓冲区大小
bool TCPSocket::set_recv_buffer(int size)
{
    int buff_size = size;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_RCVBUF, &buff_size, sizeof(buff_size)) < 0)
    {
        spdlog::error("socket set recv buffer error: errno={} errstr={}", errno,strerror(errno));
        return false;
    }
    return true;
}
//设置套接字的 linger 选项，用于控制关闭连接时的行为
bool TCPSocket::set_linger(bool active, int seconds)
{
    struct linger l{};
    if (active)
        l.l_onoff = 1;
    else
        l.l_onoff = 0;
    l.l_linger = seconds;

    if (setsockopt(m_sockfd, SOL_SOCKET, SO_LINGER, &l, sizeof(l)) < 0)
    {
        spdlog::error("socket set sock linger error: errno={} errstr={}", errno,strerror(errno));
        return false;
    }
    return true;
}
//设置套接字的 keep-alive 选项，用于保持长时间处于空闲状态的连接
bool TCPSocket::set_keep_alive()
{
    int flag = 1;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof(flag)) < 0)
    {
        spdlog::error("socket set sock keep alive error: errno={} errstr={}", errno,strerror(errno));
        return false;
    }
    return true;
}
//设置套接字的地址重用选项
bool TCPSocket::set_reuse_addr()
{
    int flag = 1;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) < 0)
    {
        spdlog::error("socket set sock reuser addr error: errno={} errstr={}", errno,strerror(errno));
        return false;
    }
    return true;
}
//设置套接字的端口重用选项
bool TCPSocket::set_reuse_port()
{
    int flag = 1;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag)) < 0)
    {
        spdlog::error("socket set sock reuser port error: errno={} errstr={}", errno,strerror(errno));
        return false;
    }
    return true;
}