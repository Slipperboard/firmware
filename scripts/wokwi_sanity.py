#!/usr/bin/env python3
"""Sanity checks for Wokwi configuration files."""

import json
import os
import sys
import tomllib

WOKWI_TOML = "wokwi.toml"


def error(msg: str) -> int:
    print(msg, file=sys.stderr)
    return 1


def main() -> int:
    if not os.path.exists(WOKWI_TOML):
        return error(f"{WOKWI_TOML} not found")

    try:
        with open(WOKWI_TOML, "rb") as f:
            config = tomllib.load(f)
    except Exception as exc:
        return error(f"Failed to parse {WOKWI_TOML}: {exc}")

    wokwi_cfg = config.get("wokwi")
    if not isinstance(wokwi_cfg, dict):
        return error("Missing [wokwi] section in wokwi.toml")

    required_keys = ["board", "elf", "firmware", "diagram"]
    for key in required_keys:
        if key not in wokwi_cfg:
            return error(f"Missing '{key}' in [wokwi] section")

    diagram_path = wokwi_cfg["diagram"]
    if not os.path.exists(diagram_path):
        return error(f"Diagram file '{diagram_path}' not found")

    try:
        with open(diagram_path, "r", encoding="utf-8") as f:
            json.load(f)
    except Exception as exc:
        return error(f"Failed to parse {diagram_path}: {exc}")

    for key in ("elf", "firmware"):
        path = wokwi_cfg[key]
        if not os.path.exists(path):
            print(f"warning: {key} '{path}' does not exist", file=sys.stderr)

    print("Wokwi configuration OK")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
