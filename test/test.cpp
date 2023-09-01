//
// Created by Admin on 2023/8/29.
//
#include "testThreadPool.h"
#include "testDataStream.h"
#include "testReflect.h"
#include "testSpdlog.h"
#include "testSocket.h"
void testDataStream_01()
{
    DataStream ds;
    map<int,int> map1;
    for(int i = 0; i < 10; i++)
    {
        map1[i] = i+100;
    }
    ds.write(map1);

    map<int,int> map2;
    ds>>map2;
    for(auto iter : map2)
    {
        cout << iter.first <<":"<<iter.second<<std::endl;
    }
}
// 示例任务函数
void printNumber(int num) {
    std::cout << "Number: " << num << std::endl;
}

void testThreaPool_01()
{
    // 提交任务到线程池
    for (int i = 0; i < 10; ++i) {
        Singleton<ThreadPool>::instance()->enqueue(printNumber, i);
    }
    // 等待所有任务完成
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout <<sizeof(bool)<<"###"<<sizeof(char)<<"\n";

}
void testReflect_01()
{
    Reflectable* obj1 = ClassFactory::Create("Derived1");
    if (obj1) {
         obj1->DealData();
        delete obj1;
    }

    Reflectable* obj2 = ClassFactory::Create("Derived2");
    if (obj2) {
        obj2->DealData();
        delete obj2;
    }
}
void testSpdlog_01()
{
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");
}


void testSpdlog_02()
{
    auto my_logger = spdlog::basic_logger_mt("file_logger", "logs/basic-log.txt", true);
    my_logger->info("Welcome to spdlog!");
    my_logger->error("Some error message with arg: {}", 1);
}

void handleEvent(int fd, void* ptr, __uint32_t events) {
    std::cout << "Event occurred on file descriptor: " << fd << std::endl;
    // 实际的事件处理逻辑在这里进行
    // ...
}

void testEpoll_01()
{
    EventPoller eventPoller(true);
    int max_connections = 10;
    eventPoller.create(max_connections);

    // 添加事件处理回调函数
    for (int i = 0; i < max_connections; ++i) {
        eventPoller.add(i, nullptr, EPOLLIN, handleEvent);
    }

    // 模拟事件触发
    for (int i = 0; i < max_connections; ++i) {
        std::cout << "Triggering event on file descriptor: " << i << std::endl;
        // 模拟事件发生后的处理延迟
        sleep(1);
        // 假设事件发生后会将事件的相关信息传递给 eventPoller，比如文件描述符和事件类型
        eventPoller.wait(0);
    }

    // 删除事件处理回调函数
    for (int i = 0; i < max_connections; ++i) {
        eventPoller.del(i);
    }
}