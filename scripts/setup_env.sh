#!/usr/bin/env bash
set -e
OS=$(uname -s)

install_linux() {
    if command -v apt-get >/dev/null; then
        sudo apt-get update
        sudo apt-get install -y python3 python3-pip clang-format clang-tidy cppcheck gcovr g++ make
        pip3 install --upgrade platformio cpplint
    else
        echo "Unsupported Linux distribution. Please install dependencies manually." >&2
        exit 1
    fi
}

install_macos() {
    if ! command -v brew >/dev/null; then
        echo "Homebrew not found. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    brew update
    brew install python3 clang-format clang-tidy cppcheck gcovr gcc make
    pip3 install --upgrade platformio cpplint
}

case "$OS" in
    Linux*) install_linux ;;
    Darwin*) install_macos ;;
    *)
        echo "Unsupported OS: $OS" >&2
        exit 1
        ;;
 esac
