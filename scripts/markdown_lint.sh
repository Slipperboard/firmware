#!/usr/bin/env bash
# Lint markdown files
set -euo pipefail

EMAIL_RE='^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$'

check_file() {
    local path="$1"
    if [ ! -r "$path" ]; then
        echo "$path: unable to read" >&2
        return
    fi
    local text
    text="$(cat "$path")"
    local maintainers_line
    maintainers_line=$(grep -i '^Maintainers:' "$path" | head -n1 || true)
    if [ -z "$maintainers_line" ]; then
        echo "$path: missing maintainers list"
    else
        local rest=${maintainers_line#*:}
        IFS=',' read -ra parts <<< "$rest"
        local names=()
        local emails=()
        for part in "${parts[@]}"; do
            part="$(echo "$part" | sed 's/^ *//;s/ *$//')"
            [ -z "$part" ] && continue
            if [[ "$part" == *'<'*'>' ]]; then
                name="${part%%<*}"
                name="$(echo "$name" | xargs)"
                email="${part#*<}"
                email="${email%>}"
                email="$(echo "$email" | xargs)"
                names+=("$name")
                emails+=("$email")
            else
                names+=("$part")
            fi
        done
        if [ ${#names[@]} -eq 0 ]; then
            echo "$path: maintainer name missing"
        fi
        for email in "${emails[@]}"; do
            if [[ ! $email =~ $EMAIL_RE ]]; then
                echo "$path: invalid email address '$email'"
            fi
        done
    fi

    local idx=0
    while IFS='' read -r line || [ -n "$line" ]; do
        idx=$((idx+1))
        if [[ "$line" =~ [[:space:]]$ ]]; then
            echo "$path:$idx: trailing whitespace"
        fi
        if [[ "$line" == *$'\t'* ]]; then
            echo "$path:$idx: tab character found"
        fi
    done < "$path"

    if [ -n "$text" ] && [ "${text: -1}" != $'\n' ]; then
        echo "$path: missing newline at end of file"
    fi
}

files=("$@")
if [ ${#files[@]} -eq 0 ]; then
    mapfile -t files < <(git ls-files '*.md' | grep -v '\.pio')
fi

errors=0
for f in "${files[@]}"; do
    out=$(check_file "$f") || true
    if [ -n "$out" ]; then
        echo "$out"
        errors=1
    fi
done

exit $errors
