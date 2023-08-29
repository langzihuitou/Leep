//
// Created by Admin on 2023/8/29.
//
#include "testThreadPool.h"
#include "testDataStream.h"
#include "testReflect.h"

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
        obj1->DealData();
        delete obj2;
    }
}