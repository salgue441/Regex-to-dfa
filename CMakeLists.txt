cmake_minimum_required(VERSION 3.10)

# Set the project name
project(RegexToDFAConverter)

# Specify the required C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory for header files
include_directories(include)

# Add all the source files
file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")

# Create the executable
add_executable(RegexToDFAConverter ${SOURCES})
