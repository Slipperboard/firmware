#!/usr/bin/env python3
"""Validate commit message prefixes."""
import re
import subprocess
import sys

PREFIX_RE = re.compile(
    r"^(HOTFIX:|FIX:|FEATURE:|ISSUE#[0-9]+:|(?i:(?:fixes|closes)#[0-9]+:))"
)
GOOD = "\u2714"  # check mark
BAD = "X"  # invalid mark
RETURN = "\u21a9"  # return arrow for hints


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
        if PREFIX_RE.match(line):
            print(f"{GOOD} {line}")
        else:
            print(f"{BAD} {line}")
            print(
                f"   {RETURN} commit message must start with HOTFIX:, FIX:, FEATURE:, or ISSUE#<number>:"
            )
            bad = True
    return 1 if bad else 0


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: check_commit_prefix.py <base_sha>", file=sys.stderr)
        sys.exit(1)
    sys.exit(main(sys.argv[1]))
