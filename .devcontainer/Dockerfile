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
    curl \
    && rm -rf /var/lib/apt/lists/*

# Install Node.js from NodeSource to ensure npm is available
RUN curl -fsSL https://deb.nodesource.com/setup_lts.x | bash - && \
    apt-get install -y nodejs && \
    rm -rf /var/lib/apt/lists/*

# Install cpplint and PlatformIO
# Ubuntu images enable PEP 668 which prevents system-wide pip installs.
# --break-system-packages allows installing to the base environment.
RUN pip3 install --break-system-packages --no-cache-dir cpplint platformio

# Install Wokwi CLI
RUN npm install -g @wokwi/cli

ENV PATH="/root/.local/bin:${PATH}"
