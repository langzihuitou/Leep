//
// Created by Admin on 2023/8/31.
//

#ifndef COMTOOLS_EVENTPOLLER_H
#define COMTOOLS_EVENTPOLLER_H

#include <stddef.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <error.h>
#include <string.h>
#include <functional>
#include <vector>
#include <memory>
#include <unordered_map>

/*********************************************************************************************
epoll ET（Edge Triggered）模式是 Linux 下使用的一种事件驱动模型，用于高效地处理大量的并发连接。
在 ET 模式下，epoll 会仅在文件描述符状态发生边缘变化时通知应用程序，边缘触发适用于非阻塞 I/O。
具体而言，ET 模式下，当文件描述符上有数据准备好时，epoll 只会通知一次，直到应用程序将该数据全部读取完毕或者写入完毕。
与之相对的是 LT（Level Triggered）模式，在 LT 模式下，如果文件描述符上有数据准备好，每次 epoll_wait 返回时都会通知应用程序。
ET 模式相比 LT 模式，能够减少 epoll_wait 的调用次数，提高性能。但是，使用 ET 模式需要应用程序保证对于每个事件都进行读写操作，否则可能会导致事件被漏掉。
总结一下，epoll ET 模式通过边缘触发的方式提供更高效的 I/O 事件通知机制，适用于高并发的非阻塞 I/O 场景
 **************************************************************************************/
class EventPoller
{
public:
    // 用于表示事件的回调函数
    using EventCallback = std::function<void(int, void*, __uint32_t)>;

    EventPoller(bool et = true);
    ~EventPoller();
    /**
     * @brief 生成 epoll句柄.
     * @param max_connections epoll服务需要支持的最大连接数
     */
    void create(int max_connections);

    /**
     * @brief 添加监听句柄.
     * @param fd    句柄
     * @param ptr   辅助的数据, 可以后续在epoll_event中获取到
     * @param event 需要监听的事件EPOLLIN|EPOLLOUT
     *
     */
    void add(int fd, void * ptr, __uint32_t events,const EventCallback& callback);

    /**
     * @brief 修改句柄事件.
     * @param fd    句柄
     * @param ptr   辅助的数据, 可以后续在epoll_event中获取到
     * @param event 需要监听的事件EPOLLIN|EPOLLOUT
     */
    void mod(int fd, void * ptr, __uint32_t events);

    /**
     * @brief 删除句柄事件.
     * @param fd    句柄
     * @param ptr   辅助的数据, 可以后续在epoll_event中获取到
     * @param event 需要监听的事件EPOLLIN|EPOLLOUT
     */
    void del(int fd);

    /**
     * @brief 等待时间.
     * @param millsecond    毫秒
     * @return int          有事件触发的句柄数
     */
    int wait(int millsecond);

protected:
    /**
 * @brief 控制 epoll，将EPOLL设为边缘触发EPOLLET模式
 * @param fd       句柄，在create函数时被赋值
 * @param ptr      辅助的数据, 可以后续在epoll_event中获取到
 * @param events   需要监听的事件
 *                 EPOLLIN  表示对应的文件描述符可以读
 *                 EPOLLOUT 表示对应的文件描述符可以写
 *                 EPOLLPRI 表示对应的文件描述符有紧急的数据可读
 *                 EPOLLERR 表示对应的文件描述符发生错误
 *                 EPOLLHUP 表示对应的文件描述符被挂断
 *                 EPOLLET  表示对应的文件描述符有事件发生
 * @param op       控制 epoll 文件描述符上的事件：注册、修改、删除
 *                 EPOLL_CTL_ADD：注册新的fd到epfd中
 *                 EPOLL_CTL_MOD：修改已经注册的fd的监听事件
 *                 EPOLL_CTL_DEL：从 epfd中删除一个fd；
 *
 */
    void ctrl(int fd, void * ptr, __uint32_t events, int op);

private:
    int m_epfd;  // epoll
    bool m_et; // 是否是ET模式
    int m_max_connections; //最大连接数
    std::unique_ptr<std::vector<epoll_event> > m_events;
    std::unordered_map<int, EventCallback> m_eventCallbacks;
};


#endif //COMTOOLS_EVENTPOLLER_H
