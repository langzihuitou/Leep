//
// Created by Admin on 2023/8/31.
//

#ifndef COMTOOLS_TESTSOCKET_H
#define COMTOOLS_TESTSOCKET_H
#include <iostream>
#include <unistd.h>
#include "../include/socket/EventPoller.h"
void handleEvent(int fd, void* ptr, __uint32_t events);
void testEpoll_01();
#endif //COMTOOLS_TESTSOCKET_H
