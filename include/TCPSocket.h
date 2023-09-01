//
// Created by Admin on 2023/9/1.
//

#ifndef COMTOOLS_TCPSOCKET_H
#define COMTOOLS_TCPSOCKET_H

#include <string>
#include <spdlog/spdlog.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

class TCPSocket {
public:
    TCPSocket();
    TCPSocket(const std::string &ip, int port);

    //调用 close() 方法关闭套接字
    virtual ~TCPSocket();
    //绑定套接字到指定 IP 地址和端口号
    bool bind(const std::string &ip, int port);
    //开始监听套接字上的连接请求
    bool listen(int backlog);
    //和指定的 IP 地址和端口号建立连接
    bool connect(const std::string &ip, int port);
    //关闭套接字
    bool close();
    //接受连接请求，返回新的连接套接字
    int accept();
    //接收数据
    int recv(char * buf, int len);
    //发送数据
    int send(const char * buf, int len);
    //设置套接字为非阻塞模式
    bool set_non_blocking();
    //设置发送缓冲区大小
    bool set_send_buffer(int size);
    //设置接收缓冲区大小
    bool set_recv_buffer(int size);
    //设置套接字的 linger 选项，用于控制关闭连接时的行为
    bool set_linger(bool active, int seconds);
    //设置套接字的 keep-alive 选项，用于保持长时间处于空闲状态的连接
    bool set_keep_alive();
    //设置套接字的地址重用选项
    bool set_reuse_addr();
    //设置套接字的端口重用选项
    bool set_reuse_port();

private:
protected:
    std::string  m_ip;
    int          m_port;
    int          m_sockfd;
};


#endif //COMTOOLS_TCPSOCKET_H
