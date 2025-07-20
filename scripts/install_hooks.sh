#!/usr/bin/env bash
# Configure git to use the repository's githooks
set -euo pipefail
repo_root="$(git rev-parse --show-toplevel)"
cd "$repo_root"

current="$(git config --get core.hooksPath || echo '')"
if [[ "$current" != ".githooks" ]]; then
    git config core.hooksPath .githooks
fi

printf "Git hooks installed at %s/.githooks\n" "$repo_root"
