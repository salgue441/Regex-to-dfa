FROM ubuntu:latest
WORKDIR /usr/src/app

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libfmt-dev \
    libspdlog-dev \
    libboost-all-dev \
    libboost-regex-dev 

# Copy source code
COPY . .

# Define the environment variable
ENV BUILD_TYPE Release

# Build the project
RUN cmake -B build -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
RUN cmake --build build --config ${BUILD_TYPE}

# Run the executable
CMD ["./build/bin/RegexToDFAConverter"]