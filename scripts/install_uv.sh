#!/usr/bin/env bash
set -euo pipefail

curl -Ls https://astral.sh/uv/install.sh | bash
export PATH="$HOME/.local/bin:$PATH"

if [[ -n "${GITHUB_PATH:-}" ]]; then
    echo "$HOME/.local/bin" >> "$GITHUB_PATH"
fi
