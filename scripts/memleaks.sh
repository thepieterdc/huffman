#!/bin/bash

valgrind --leak-check=full --track-origins=yes -v $1