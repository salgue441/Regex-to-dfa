cmake_minimum_required(VERSION 3.15)

# Project name and version
project(RegexToDFAConverter VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Add the include directory for header files
include_directories(include)

# Add all the source files
set(SOURCES
    src/main.cpp
    src/lex/token/token.cpp  
    src/lexer/lexer.cpp
)
# Create the executable
add_executable(RegexToDFAConverter ${SOURCES})

# Find and link fmt library
find_package(fmt REQUIRED)
target_link_libraries(RegexToDFAConverter PRIVATE fmt::fmt)

# Find and link spdlog library
find_package(spdlog REQUIRED)
target_link_libraries(RegexToDFAConverter PRIVATE spdlog::spdlog)

# Find and link boost library
find_package(Boost COMPONENTS regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Set different compile options for Debug and Release
target_compile_options(RegexToDFAConverter PRIVATE
    $<$<CONFIG:Debug>:-Og -g>
    $<$<CONFIG:Release>:-O3>
)

# Linking boost.regex
target_link_libraries(RegexToDFAConverter PRIVATE 
    fmt::fmt spdlog::spdlog ${Boost_LIBRARIES})
