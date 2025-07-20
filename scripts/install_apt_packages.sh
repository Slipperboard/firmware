#!/usr/bin/env bash
set -euo pipefail

if ! command -v apt-get >/dev/null; then
    echo "apt-get not found" >&2
    exit 1
fi

sudo apt-get update
sudo apt-get install -y "$@"
