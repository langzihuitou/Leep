//
// Created by Admin on 2023/8/26.
//

#ifndef COMTOOLS_THREADPOOL_H
#define COMTOOLS_THREADPOOL_H


#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

#include "Singleton.h"
class ThreadPool {
    friend class Singleton<ThreadPool>;
public:
    ThreadPool(size_t numThreads = 4) : stop(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back(
                    [this] {
                        while (true) {
                            std::function<void()> task;
                            {
                                std::unique_lock<std::mutex> lock(queueMutex);
                                condition.wait(lock,
                                               [this] { return stop || !taskQueue.empty(); });
                                if (stop && taskQueue.empty()) {
                                    return;
                                }
                                task = std::move(taskQueue.front());
                                taskQueue.pop();
                            }
                            task();
                        }
                    }
            );
        }
    }

    template<typename Func, typename... Args>
    void enqueue(Func&& func, Args&&... args) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            taskQueue.emplace(
                    std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        }
        condition.notify_one();
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers) {
            worker.join();
        }
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> taskQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};


// 示例任务函数
void printNumber(int num) {
    std::cout << "Number: " << num << std::endl;
}

#endif //COMTOOLS_THREADPOOL_H
