FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        clang-format \
        clang-tidy \
        cppcheck \
        gcovr \
        git \
        nodejs npm \
        python3 python3-pip \
    && pip3 install --no-cache-dir platformio cpplint \
    && npm install -g @wokwi/cli \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
