#!/bin/zsh

# Exit on error
set -e

# Compile the tests
g++ -std=c++11 -o run_tests tests/syntax_tree_test.cpp src/syntax_tree/syntax_tree.cpp -lgtest -lgtest_main -pthread

# Run the tests
./run_tests

# Remove the compiled tests
rm run_tests
