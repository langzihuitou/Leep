#include <iostream>
#include "./test/testDataStream.h"
#include "./test/testThreadPool.h"
#include "./test/testReflect.h"
#include "./test/testSpdlog.h"
#include "./test/testSocket.h"
int main() {
    try{
//        testDataStream_01();
//        testThreaPool_01();
//        testReflect_01();
//        testSpdlog_01();
        testEpoll_01();
    }
    catch (...)
    {
        exit(-1);
    }
    return 0;
}
