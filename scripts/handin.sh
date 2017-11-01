#!/bin/bash

# Based on handin by @ramaes
# Source at https://github.ugent.be/ramaes/handin/

OUTFILE="out.zip"
SOURCES_FILE_PREFIX="huffman:"

cd "$(dirname $0)"
cd "../"

# Generate sources-file
echo "$SOURCES_FILE_PREFIX" "$(find ./src/ -name '*.[c|h]' | sed 's_^\./src/__' | tr '\n' ' ')" > sources

# Create zip
rm -f "$OUTFILE"
zip -r "$OUTFILE" src/ tests/ extra/ sources