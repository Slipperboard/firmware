#!/usr/bin/env python3
"""Close GitHub issues referenced by commit messages."""
import json
import os
import re
import subprocess
import sys
from urllib.request import Request, urlopen

CLOSE_RE = re.compile(r"(fixes|closes)#(\d+)", re.IGNORECASE)


def get_commit_messages(base: str, head: str) -> list[str]:
    try:
        out = subprocess.check_output([
            "git",
            "log",
            f"{base}..{head}",
            "--format=%s",
            "--no-merges",
        ], text=True)
    except subprocess.CalledProcessError as exc:
        print(f"error: unable to read git log: {exc}", file=sys.stderr)
        return []
    return [line.strip() for line in out.splitlines()]


def fetch_issue(repo: str, token: str, number: str) -> dict | None:
    url = f"https://api.github.com/repos/{repo}/issues/{number}"
    req = Request(url, headers={"Authorization": f"token {token}", "Accept": "application/vnd.github+json"})
    try:
        with urlopen(req) as resp:
            return json.load(resp)
    except Exception as exc:
        print(f"warning: unable to read issue #{number}: {exc}", file=sys.stderr)
        return None


def close_issue(repo: str, token: str, number: str) -> None:
    url = f"https://api.github.com/repos/{repo}/issues/{number}"
    data = json.dumps({"state": "closed"}).encode()
    req = Request(url, data=data, method="PATCH", headers={
        "Authorization": f"token {token}",
        "Accept": "application/vnd.github+json",
    })
    try:
        with urlopen(req):
            pass
    except Exception as exc:
        print(f"warning: unable to close issue #{number}: {exc}", file=sys.stderr)


def main(base: str, head: str) -> int:
    repo = os.environ.get("GITHUB_REPOSITORY")
    token = os.environ.get("GITHUB_TOKEN")
    if not repo or not token:
        print("error: GITHUB_REPOSITORY and GITHUB_TOKEN must be set", file=sys.stderr)
        return 1

    issues: set[str] = set()
    for msg in get_commit_messages(base, head):
        for m in CLOSE_RE.finditer(msg):
            issues.add(m.group(2))

    for number in issues:
        data = fetch_issue(repo, token, number)
        if not data or data.get("state") == "closed":
            continue
        labels = {lbl["name"].lower() for lbl in data.get("labels", [])}
        if "codex" not in labels:
            continue
        close_issue(repo, token, number)
    return 0


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("usage: close_issues.py <base_sha> <head_sha>", file=sys.stderr)
        sys.exit(1)
    sys.exit(main(sys.argv[1], sys.argv[2]))
