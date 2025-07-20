#!/usr/bin/env bash
# Configure git to use the repository's githooks
set -euo pipefail
repo_root="$(git rev-parse --show-toplevel)"
cd "$repo_root"
# Set githooks path
git config core.hooksPath .githooks

printf "Git hooks installed.\n"
