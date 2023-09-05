//
// Created by Admin on 2023/9/5.
//

#ifndef COMTOOLS_TCPCLIENTSOCKET_H
#define COMTOOLS_TCPCLIENTSOCKET_H

#include "TCPSocket.h"
#include <string>

class TCPClientSocket: public TCPSocket{
public:
    TCPClientSocket();
    TCPClientSocket(const std::string &ip, int port);
    virtual ~TCPClientSocket();
};


#endif //COMTOOLS_TCPCLIENTSOCKET_H
