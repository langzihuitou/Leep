//
// Created by Admin on 2023/9/5.
//

#ifndef COMTOOLS_TCPSERVERSOCKET_H
#define COMTOOLS_TCPSERVERSOCKET_H

#include <string>
#include  "../include/TCPSocket.h"

class TCPServerSocket: public TCPSocket{
    TCPServerSocket();
    TCPServerSocket(const std::string &ip, int port);
    virtual ~TCPServerSocket();
};


#endif //COMTOOLS_TCPSERVERSOCKET_H
