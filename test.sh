#!/bin/bash

# Exit on error
set -e

# Directory containing the tests
TEST_DIR="tests"

# Source files directory
SRC_DIR="src"

# Gather all .cpp files in the tests directory and src directory
TEST_FILES=$(find $TEST_DIR -name "*.cpp")
SRC_FILES=$(find $SRC_DIR -name "*.cpp")
INCLUDE_DIR=$(find $SRC_DIR -name "*.h")

# Exclude any .cpp file with a main function (if you know the name)
# For example, if main.cpp has a main function, exclude it:
SRC_FILES=$(echo "$SRC_FILES" | grep -v "main.cpp")

# Compile the tests and source files
g++ -std=c++20 -o run_tests $TEST_FILES $SRC_FILES  -lgtest -lgtest_main -pthread -lfmt

# Run the tests
./run_tests

# Remove the compiled tests
rm run_tests
