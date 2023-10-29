#!/bin/zsh

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Run cmake
cmake ..
make

# Run the program
./RegexToDfa