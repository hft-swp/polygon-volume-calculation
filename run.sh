#!/bin/bash

CFLAGS="-O3 -march=native -c -fopenmp -ffast-math -std=c99"
gcc $CFLAGS main.c
gcc $CFLAGS vol.c
gcc main.o vol.o -fopenmp -o vol
objdump -d vol.o > vol.s

./vol
