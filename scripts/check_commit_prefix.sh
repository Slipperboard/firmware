#!/usr/bin/env bash
# Validate commit message prefixes
set -euo pipefail

if [ "$#" -ne 1 ]; then
    echo "usage: $0 <base_sha>" >&2
    exit 1
fi

base=$1
if ! log=$(git log "$base..HEAD" --format=%s --no-merges); then
    echo "error: unable to read git log" >&2
    exit 1
fi

bad=0
while IFS= read -r line; do
    if [[ $line =~ ^(HOTFIX:|FIX:|FEATURE:|ISSUE#[0-9]+:) ]]; then
        echo "\u2714 $line"
    else
        echo "X $line"
        echo "   \u21a9 commit message must start with HOTFIX:, FIX:, FEATURE:, or ISSUE#<number>:"
        bad=1
    fi
done <<< "$log"

exit $bad
