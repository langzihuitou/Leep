cmake_minimum_required(VERSION 3.0)
project(ComTools)

set(CMAKE_CXX_STANDARD 14)

# 静态库生成的路径
set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# 头文件目录
set(HEAD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HEAD_PATH_TEST ${CMAKE_CURRENT_SOURCE_DIR}/test)

# 静态库的名字
set(SERIALIZE_LIB serialize)
set(REFLECT_LIB reflect)
set(TEST_LIB test)
#set(SORT_LIB sort)
include_directories(${HEAD_PATH} ${HEAD_PATH_TEST} )
# 添加子目录
add_subdirectory(serialize)
add_subdirectory(reflect)
add_subdirectory(test)
add_subdirectory(socket)
aux_source_directory( ${PROJECT_SOURCE_DIR} SRC)
# 输出一般日志信息
message(STATUS "source path: ${PROJECT_SOURCE_DIR}")

add_executable(${PROJECT_NAME} ${SRC})

# 链接操作
target_link_libraries(${PROJECT_NAME}
        serialize
        test
        reflect
        socket
        )
