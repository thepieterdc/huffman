file(GLOB util_SRC
		"util/*.h"
		"util/*.c")

add_executable(huffman main.c ${util_SRC})