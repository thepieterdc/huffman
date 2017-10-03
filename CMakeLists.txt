cmake_minimum_required(VERSION 3.5.1)
project(huffman C)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall")
set(CMAKE_C_FLAGS_DEBUG "-g -DIS_DEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O4")
set(CMAKE_C_STANDARD 99)

subdirs(src tests)

add_executable(huffman src/main.c ${util_SRC})