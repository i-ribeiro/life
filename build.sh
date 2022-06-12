#!/bin/bash

# build.sh
#
# Isaac Ribeiro
# 12/Jun/2022
#
# A script to easily build Life as an executable.

# life.c => life.o
gcc -o bin/life.o -c src/life.c

# main.c => main.o
gcc -o bin/main.o -c src/main.c

# build executable
gcc -o bin/life bin/main.o bin/life.o
