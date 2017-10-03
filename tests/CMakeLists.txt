file(GLOB tests_SRC
		"*.h"
		"*.c")

add_library(huffman_tests_src STATIC ${tests_SRC})