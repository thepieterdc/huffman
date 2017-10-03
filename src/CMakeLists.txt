file(GLOB util_SRC
		"util/*.h"
		"util/*.c")

add_library(huffman_src STATIC main.c ${util_SRC})