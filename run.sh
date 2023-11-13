#!/bin/bash

# Pull the Docker image (if not already pulled)
docker pull crsa441/regex-to-dfa

# Define the source and build directories on the host machine
SOURCE_DIR="$(pwd)"  # Assuming CMakeLists.txt is in the current directory
BUILD_DIR="$(pwd)/build"

# Run the program inside the Docker container using /bin/bash
docker run -it --rm -v "$SOURCE_DIR:/mnt/source" -v "$BUILD_DIR:/mnt/build" crsa441/regex-to-dfa /bin/bash -c "cd /mnt/build && cmake /mnt/source && make && ./bin/RegexToDFAConverter"
