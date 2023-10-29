cmake_minimum_required(VERSION 3.10)

project(RegexToDfa)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Source files
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Compile all .h and .cpp files in src
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.h)

# Add executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_DIR})

# Add warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()