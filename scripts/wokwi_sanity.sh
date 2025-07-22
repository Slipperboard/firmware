#!/usr/bin/env bash
# Sanity checks for Wokwi configuration files
set -euo pipefail

WOKWI_TOML="wokwi.toml"

error() {
    echo "$1" >&2
    exit 1
}

[ -f "$WOKWI_TOML" ] || error "$WOKWI_TOML not found"

# Parse [wokwi] section
declare -A cfg
while IFS='=' read -r key value; do
    key="$(echo "$key" | xargs)"
    value="$(echo "$value" | sed 's/#.*//' | xargs | tr -d '"')"
    [ -n "$key" ] && cfg[$key]="$value"
done < <(awk '/^\[wokwi\]/{f=1;next}/^\[/{f=0}f && /=/' "$WOKWI_TOML")

for k in board elf firmware diagram; do
    [ -n "${cfg[$k]:-}" ] || error "Missing '$k' in [wokwi] section"
done

diagram="${cfg[diagram]}"
[ -f "$diagram" ] || error "Diagram file '$diagram' not found"

if command -v jq >/dev/null; then
    jq . "$diagram" >/dev/null || error "Failed to parse $diagram"
else
    python3 -m json.tool "$diagram" >/dev/null || error "Failed to parse $diagram"
fi

for k in elf firmware; do
    path="${cfg[$k]}"
    if [ ! -e "$path" ]; then
        echo "warning: $k '$path' does not exist" >&2
    fi
done

echo "Wokwi configuration OK"
