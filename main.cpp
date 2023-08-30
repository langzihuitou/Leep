#include <iostream>
#include "./test/testDataStream.h"
#include "./test/testThreadPool.h"
#include "./test/testReflect.h"
#include "./test/testSpdlog.h"
#include "./include/spdlog/spdlog.h"
int main() {
    try{
        testDataStream_01();
        testThreaPool_01();
        testReflect_01();
        testSpdlog_01();
    }
    catch (...)
    {
        exit(-1);
    }
    return 0;
}
