# Use Ubuntu 22.04 as the base image
FROM ubuntu:22.04

# Set environment variables to prevent interactive prompts during package installation
ARG DEBIAN_FRONTEND=noninteractive

# Update package list and install necessary tools and dependencies
RUN apt-get update && \
    apt-get install -y \
    git \
    curl \
    gnupg \
    make \
    build-essential \
    pkg-config \
    libzmq3-dev \
    protobuf-c-compiler \
    libprotobuf-c-dev \
    libcjson-dev \
    cmake \
    gdb \
    && rm -rf /var/lib/apt/lists/*

# Include shared objects in the library path
ENV LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
