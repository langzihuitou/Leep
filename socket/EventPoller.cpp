//
// Created by Admin on 2023/8/31.
//

#include "../include/socket/EventPoller.h"

EventPoller::EventPoller(bool et) : m_epfd(0), m_max_connections(0), m_events(new std::vector<epoll_event>()), m_et(et)
{
}


EventPoller::~EventPoller()
{
    if(m_epfd > 0)
    {
        close(m_epfd);
        m_epfd = 0;
    }
}

void EventPoller::ctrl(int fd, void * ptr, __uint32_t events, int op)
{
    struct epoll_event ev { };
    ev.data.ptr = ptr;
    if (m_et)
    {
        ev.events = events | EPOLLET;
    }
    else
    {
        ev.events = events;
    }
    epoll_ctl(m_epfd, op, fd, &ev);
}

void EventPoller::create(int max_connections)
{
    /****
    epoll_create() 是一个用于创建 epoll 实例的系统调用函数。它的原型如下：
    int epoll_create(int size);
    该函数接受一个整数参数 size，用于指定 epoll 实例能够为监视的文件描述符维护的最大数目。这个参数在大多数情况下可以被忽略，因为内核会根据需要自动调整大小。
    调用 epoll_create() 函数将会返回一个非负整数的文件描述符，用于表示创建的 epoll 实例。如果调用失败，返回值将为 -1，并且错误号 errno 会被设置以指示具体的错误类型。
    epoll_create1(0) 是一个创建 epoll 实例的系统调用函数。它是通过 epoll_create 函数实现的，通过传递参数 0 等效于传递 EPOLL_CLOEXEC。
    以下是对参数的解释：
    flags：标志参数，用于指定一些选项。其中常用的选项如下：
    0：无特殊选项。
    EPOLL_CLOEXEC：将创建的 epoll 实例设置为 close-on-exec，表示在执行 exec 系列函数时自动关闭。
    epoll_create1 函数返回的是一个整型的 epoll 文件描述符（epoll fd），用于后续的 epoll 操作。如果创建失败，将返回 -1，并设置相应的错误码。*/
    m_max_connections = max_connections;
    m_epfd = epoll_create1(0);
    if (m_epfd < 0)
    {
        return;
    }
    m_events->resize(max_connections + 1);
    m_eventCallbacks.clear();  // 清除之前的回调函数映射
}

void EventPoller::add(int fd, void * ptr, __uint32_t events,const EventCallback& callback)
{
    m_eventCallbacks[fd] = callback;
    ctrl(fd, ptr, events, EPOLL_CTL_ADD);
}

void EventPoller::mod(int fd, void * ptr, __uint32_t events)
{
    ctrl(fd, ptr, events, EPOLL_CTL_MOD);
}

void EventPoller::del(int fd)
{
    ctrl(fd, nullptr, 0, EPOLL_CTL_DEL);
    m_eventCallbacks.erase(fd);
}

int EventPoller::wait(int millsecond)
{
    int numEvents = epoll_wait(m_epfd, m_events->data(), m_max_connections + 1, millsecond);
    for (int i = 0; i < numEvents; ++i) {
        int fd = m_events->at(i).data.fd;
        __uint32_t events = m_events->at(i).events;
        auto callbackIt = m_eventCallbacks.find(fd);
        if (callbackIt != m_eventCallbacks.end()) {
            callbackIt->second(fd, m_events->at(i).data.ptr, events);
        }
    }
    return numEvents;
}