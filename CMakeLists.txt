cmake_minimum_required(VERSION 3.0)
project(ComTools)

set(CMAKE_CXX_STANDARD 14)

add_executable(ComTools main.cpp Thread/ThreadPool.h Serialize/DataStream.h Serialize/DataStream.cpp Serialize/Serializable.h utility/Singleton.h)
