#!/usr/bin/env bash
# Basic linter for Makefiles
set -euo pipefail

lint_file() {
    local file="$1"
    if [ ! -r "$file" ]; then
        echo "$file: unable to read" >&2
        return 1
    fi
    awk -v p="$file" '
    BEGIN{recipe=0}
    {
        line=$0
        if (match(line, /^[^[:space:]:=]+:[[:space:]]*/)) {
            if (substr(line,1,1)!="\t") recipe=1
        } else if (recipe && line!="" && substr(line,1,1)!="\t" && substr(line,1,1)!="#") {
            print p ":" NR ": recipe line not starting with tab"
        }
        if (match(line, /^[[:space:]]*$/)) recipe=0
        if (match(line, /[[:space:]]$/)) {
            print p ":" NR ": trailing whitespace"
        }
    }
    ' "$file"
}

files=("$@")
if [ ${#files[@]} -eq 0 ]; then
    files=(Makefile)
fi

errors=0
for f in "${files[@]}"; do
    out=$(lint_file "$f") || true
    if [ -n "$out" ]; then
        echo "$out"
        errors=1
    fi
done

exit $errors
