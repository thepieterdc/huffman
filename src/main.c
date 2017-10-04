/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include "util/errors.h"
#include "util/logging.h"

int main(void) {
	info("WOooooo");
	success("Hello, World!");
	warning("WXooo");
	error(ERROR_MALLOC_FAILED);
	return 0;
}