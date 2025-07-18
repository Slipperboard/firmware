#!/usr/bin/env python3
"""Basic linter for Makefiles."""

from pathlib import Path
import sys
import re


def lint_makefile(path: Path) -> list[str]:
    try:
        lines = path.read_text(encoding="utf-8").splitlines()
    except Exception as exc:
        return [f"{path}: unable to read: {exc}"]

    errors: list[str] = []
    recipe = False
    rule_re = re.compile(r"^[^\s:=]+:\s*")
    for idx, line in enumerate(lines, start=1):
        if rule_re.match(line) and not line.startswith("\t"):
            recipe = True
        elif recipe and line and not line.startswith("\t") and not line.startswith("#"):
            errors.append(f"{path}:{idx}: recipe line not starting with tab")
        if line.strip() == "":
            recipe = False
        if line.rstrip() != line:
            errors.append(f"{path}:{idx}: trailing whitespace")
    return errors


def main(paths: list[str]) -> int:
    files = [Path(p) for p in paths] if paths else [Path("Makefile")]
    all_errors: list[str] = []
    for f in files:
        all_errors.extend(lint_makefile(f))
    if all_errors:
        for err in all_errors:
            print(err)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
