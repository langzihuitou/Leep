#include <iostream>
#include "Thread/ThreadPool.h"
#include "Serialize/DataStream.h"
int main() {

    ThreadPool threadPool(4); // 创建一个拥有4个线程的线程池

    // 提交任务到线程池
    for (int i = 0; i < 10; ++i) {
        threadPool.enqueue(printNumber, i);
       // Singleton<ThreadPool>::instance()->enqueue(printNumber, i);
    }

    // 等待所有任务完成
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout <<sizeof(bool)<<"###"<<sizeof(char)<<"\n";

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
    return 0;
}
