#!/usr/bin/env bash
set -euo pipefail

if ! command -v apt-get >/dev/null; then
    echo "apt-get not found" >&2
    exit 1
fi

missing=()
for pkg in "$@"; do
    if ! dpkg -s "$pkg" >/dev/null 2>&1; then
        missing+=("$pkg")
    fi
done

if [ ${#missing[@]} -gt 0 ]; then
    sudo apt-get update
    sudo apt-get install -y --no-install-recommends "${missing[@]}"
fi
