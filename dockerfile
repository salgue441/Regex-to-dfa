# Stage 1: Build Stage
FROM ubuntu:latest AS builder
WORKDIR /usr/src/app

# Installing dependencies
RUN apt-get update && \
    apt-get install -y build-essential cmake g++ libfmt-dev libspdlog-dev libboost-regex-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Copy source
COPY . .

# Define the build environment
ENV BUILD_TYPE Release

# Build the project
RUN cmake -B build -DCMAKE_BUILD_TYPE=${BUILD_TYPE} && \
    cmake --build build --config ${BUILD_TYPE}

# Stage 2: Run Stage
FROM ubuntu:latest
WORKDIR /usr/src/app

# Install runtime dependencies
RUN apt-get update && \
    apt-get install -y libfmt-dev libspdlog-dev libboost-regex-dev cmake g++ && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Copy the executable
COPY --from=builder /usr/src/app/build /usr/src/app/build

# Define the environment variables
ENV BUILD_TYPE Release

# Run the executable
CMD ["./build/bin/RegexToDFAConverter"]