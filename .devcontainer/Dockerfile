FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04

# Install packages required by the project
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        clang \
        clang-tidy \
        clang-format \
        cppcheck \
        gcovr \
        python3 \
        python3-pip \
        git \
    && rm -rf /var/lib/apt/lists/*

# Install PlatformIO via pip
RUN pip3 install --no-cache-dir platformio

WORKDIR /workspace
