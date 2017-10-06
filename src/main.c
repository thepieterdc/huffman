/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include <unistd.h>

int main(void) {
	char in;
	while(read(STDIN_FILENO, &in, 1) > 0) {
		printf("%c\n", in);
	}
	return 0;
}