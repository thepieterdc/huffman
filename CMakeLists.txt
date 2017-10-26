cmake_minimum_required(VERSION 3.5.1)
project(huffman C)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall")
set(CMAKE_C_FLAGS_DEBUG "-g -DIS_DEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O4")
set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE algorithms_SRC
		"src/algorithms/*.h"
		"src/algorithms/*.c"
		)

file(GLOB_RECURSE datastructures_SRC
		"src/datastructures/*.h"
		"src/datastructures/*.c"
		)

file(GLOB_RECURSE datatypes_SRC
		"src/datatypes/*.h"
		"src/datatypes/*.c"
		)

file(GLOB_RECURSE io_SRC
		"src/io/*.h"
		"src/io/*.c"
		)

file(GLOB_RECURSE tests_SRC
		"tests/*.h"
		"tests/*.c"
		)

file(GLOB_RECURSE util_SRC
		"src/util/*.h"
		"src/util/*.c"
		)

set(huffman_SRC ${algorithms_SRC} ${datastructures_SRC} ${datatypes_SRC} ${io_SRC} ${util_SRC})
add_executable(huffman src/main.c ${huffman_SRC})
target_link_libraries(huffman m)

add_executable(huffman_tests tests/testrunner.c ${huffman_SRC} ${tests_SRC})
target_compile_definitions(huffman_tests PRIVATE IS_TEST=True)
target_link_libraries(huffman_tests m)
