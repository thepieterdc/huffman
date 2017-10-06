/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
	//Bevat ascii waarden van de letters
	int *frequencies = (int *) malloc(255 * sizeof(int));
	
	int in;
	while ((in = (char) getchar()) > -1) {
		frequencies[in]++;
	}
	
	for(int i = 0; i < 256; ++i) {
		if(frequencies[i] > 0) printf("%d: %d\n", i, frequencies[i]);
	}
	
	return 0;
}