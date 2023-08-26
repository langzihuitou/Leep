#include <iostream>
#include "Thread/ThreadPool.h"
int main() {

    ThreadPool threadPool(4); // 创建一个拥有4个线程的线程池

    // 提交任务到线程池
    for (int i = 0; i < 10; ++i) {
        threadPool.enqueue(printNumber, i);
    }

    // 等待所有任务完成
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}
