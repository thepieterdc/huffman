#!/bin/bash

cmake . && make -j4 huffman && ./huffman -t 1 -c < tests/testfiles/text.txt