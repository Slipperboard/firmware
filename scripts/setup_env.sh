#!/usr/bin/env bash
# Setup development environment dependencies for Slipperboard
set -euo pipefail

script_dir="$(cd "$(dirname "$0")" && pwd)"

case "$(uname)" in
    Linux*)
        "$script_dir/install_apt_packages.sh" curl clang-format clang-tidy cppcheck gcovr
        ;;
    *)
        echo "Unsupported platform" >&2
        exit 1
        ;;
esac

"$script_dir/install_uv.sh"
"$script_dir/install_platformio.sh"
"$script_dir/install_cpplint.sh"
