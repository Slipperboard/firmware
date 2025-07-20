#!/usr/bin/env bash
# Setup development environment dependencies for Slipperboard
# Installs tools via apt or brew depending on OS
set -euo pipefail

case "$(uname)" in
    Linux*)
        if command -v apt-get >/dev/null; then
            if command -v sudo >/dev/null; then
                SUDO="sudo"
            else
                SUDO=""
            fi
            $SUDO apt-get update
            $SUDO apt-get install -y git python3-venv python3-pip clang-format clang-tidy cppcheck gcovr
        else
            echo "apt-get not found. Unsupported Linux distribution." >&2
            exit 1
        fi
        ;;
    Darwin*)
        if command -v brew >/dev/null; then
            brew update
            brew install clang-format clang-tidy cppcheck gcovr
        else
            echo "Homebrew not found. Please install Homebrew." >&2
            exit 1
        fi
        ;;
    *)
        echo "Unsupported platform" >&2
        exit 1
        ;;
esac

# Create a Python virtual environment for Python tools
if [ ! -d .venv ]; then
    python3 -m venv .venv
fi
source .venv/bin/activate
pip install --upgrade pip
pip install platformio cpplint
