cmake_minimum_required(VERSION 3.0)
project(test)
aux_source_directory(./ SRC)
include_directories(${HEAD_PATH})
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})
add_library(${TEST_LIB} STATIC ${SRC})
# 链接操作
target_link_libraries(${PROJECT_NAME}
        reflect
        serialize
        )