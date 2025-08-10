#!/usr/bin/env bash
set -euo pipefail

if ! command -v brew >/dev/null; then
    echo "Homebrew not found. Installing Homebrew..." >&2
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi

brew update
brew install "$@"
