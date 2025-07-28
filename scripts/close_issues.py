#!/usr/bin/env python3
"""Close GitHub issues referenced by commit messages after a PR merge."""

import os
import re
import sys
import warnings

import requests

# Suppress warnings about unverifiable HTTPS requests in this environment
warnings.filterwarnings("ignore", message="Unverified HTTPS request")

API_BASE = "https://api.github.com"
PATTERN = re.compile(r"(?:FIXES|CLOSES)#(\d+)", re.IGNORECASE)


def gh_request(method: str, url: str, token: str, **kwargs):
    headers = kwargs.pop("headers", {})
    headers["Authorization"] = f"token {token}"
    headers["Accept"] = "application/vnd.github+json"
    return requests.request(method, url, headers=headers, verify=False, **kwargs)


def main(pr_number: str) -> int:
    token = os.environ.get("GITHUB_TOKEN")
    repo = os.environ.get("GITHUB_REPOSITORY")
    if not token or not repo:
        print("GITHUB_TOKEN and GITHUB_REPOSITORY must be set", file=sys.stderr)
        return 1

    commits_resp = gh_request(
        "GET",
        f"{API_BASE}/repos/{repo}/pulls/{pr_number}/commits?per_page=100",
        token,
    )
    commits_resp.raise_for_status()
    commits = commits_resp.json()

    issues = set()
    for c in commits:
        msg = c.get("commit", {}).get("message", "")
        issues.update(int(n) for n in PATTERN.findall(msg))

    for number in sorted(issues):
        issue_url = f"{API_BASE}/repos/{repo}/issues/{number}"
        issue_resp = gh_request("GET", issue_url, token)
        issue_resp.raise_for_status()
        issue = issue_resp.json()
        if issue.get("state") == "closed":
            continue
        if "pull_request" in issue:
            continue
        labels = [l.get("name") for l in issue.get("labels", [])]
        if "Codex" not in labels:
            continue
        close_resp = gh_request(
            "PATCH",
            issue_url,
            token,
            json={"state": "closed"},
        )
        close_resp.raise_for_status()
        print(f"Closed issue #{number}")
    return 0


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: close_issues.py <pull_request_number>", file=sys.stderr)
        sys.exit(1)
    sys.exit(main(sys.argv[1]))
