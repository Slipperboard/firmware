#!/usr/bin/env python3
"""Validate commit message prefixes."""
import re
import subprocess
import sys

PREFIX_RE = re.compile(r"^(HOTFIX:|FIX:|FEATURE:|ISSUE#[0-9]+:)")


def main(base: str) -> int:
    try:
        log = subprocess.check_output([
            "git",
            "log",
            f"{base}..HEAD",
            "--format=%s",
            "--no-merges",
        ], text=True)
    except subprocess.CalledProcessError as exc:
        print(f"error: unable to read git log: {exc}", file=sys.stderr)
        return 1

    bad = False
    for line in log.splitlines():
        line = line.strip()
        print(line)
        if not PREFIX_RE.match(line):
            print(f"Invalid commit message prefix: {line}", file=sys.stderr)
            bad = True
    return 1 if bad else 0


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: check_commit_prefix.py <base_sha>", file=sys.stderr)
        sys.exit(1)
    sys.exit(main(sys.argv[1]))
