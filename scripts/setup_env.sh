#!/usr/bin/env bash
# Setup development environment dependencies for Slipperboard
# Installs tools via apt on Linux
set -euo pipefail

case "$(uname)" in
    Linux*)
        if command -v apt-get >/dev/null; then
            sudo apt-get update
            sudo apt-get install -y curl clang-format clang-tidy cppcheck gcovr
        else
            echo "apt-get not found. Unsupported Linux distribution." >&2
            exit 1
        fi
        ;;
    *)
        echo "Unsupported platform" >&2
        exit 1
        ;;
esac

curl -Ls https://astral.sh/uv/install.sh | bash
export PATH="$HOME/.local/bin:$PATH"
uv tool install --force platformio
uv tool install --force cpplint
