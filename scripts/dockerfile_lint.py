#!/usr/bin/env python3
"""Simple Dockerfile linter."""
from __future__ import annotations

import sys
from pathlib import Path


def lint_dockerfile(path: Path) -> list[str]:
    try:
        text = path.read_text(encoding="utf-8")
    except Exception as exc:
        return [f"{path}: unable to read: {exc}"]

    lines = text.splitlines()
    errors: list[str] = []

    # Check that the first non-comment line starts with FROM
    for line in lines:
        stripped = line.strip()
        if stripped and not stripped.startswith("#"):
            if not stripped.upper().startswith("FROM "):
                errors.append(f"{path}: first instruction should be FROM")
            break

    for idx, line in enumerate(lines, start=1):
        if line.rstrip() != line:
            errors.append(f"{path}:{idx}: trailing whitespace")
        if "\t" in line:
            errors.append(f"{path}:{idx}: tab character found")

    if not text.endswith("\n"):
        errors.append(f"{path}: missing newline at end of file")

    return errors


def main(paths: list[str]) -> int:
    files = [Path(p) for p in paths] if paths else [Path("Dockerfile")]
    all_errors: list[str] = []
    for f in files:
        all_errors.extend(lint_dockerfile(f))
    if all_errors:
        for err in all_errors:
            print(err)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
