cmake_minimum_required(VERSION 3.15)

# Project name and version
project(RegexToDFAConverter VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory for header files
include_directories(include)

# Add all the source files
file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")

# Create the executable
add_executable(RegexToDFAConverter ${SOURCES})

# Find and link fmt library
find_package(fmt REQUIRED)
target_link_libraries(RegexToDFAConverter PRIVATE fmt::fmt)

# Find and link spdlog library
find_package(spdlog REQUIRED)
target_link_libraries(RegexToDFAConverter PRIVATE spdlog::spdlog)

# Set different compile options for Debug and Release
target_compile_options(RegexToDFAConverter PRIVATE
    $<$<CONFIG:Debug>:-Og -g>
    $<$<CONFIG:Release>:-O3>
)
