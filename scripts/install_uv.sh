#!/usr/bin/env bash
set -euo pipefail

if ! command -v uv >/dev/null 2>&1; then
    curl -Ls https://astral.sh/uv/install.sh | bash
else
    echo "uv already installed"
fi
export PATH="$HOME/.local/bin:$PATH"

if [[ -n "${GITHUB_PATH:-}" ]]; then
    echo "$HOME/.local/bin" >> "$GITHUB_PATH"
fi
