FROM mcr.microsoft.com/devcontainers/base:ubuntu

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    clang-format \
    clang-tidy \
    cppcheck \
    python3 \
    python3-pip \
    gcovr \
    && rm -rf /var/lib/apt/lists/*

# Install cpplint and PlatformIO
RUN pip3 install --no-cache-dir cpplint platformio

# Install Wokwi CLI
RUN npm install -g @wokwi/cli

ENV PATH="/root/.local/bin:${PATH}"
