# Guidance for AI Agents

This repository uses PlatformIO and Makefile targets for building and testing.
Follow these practices when preparing commits and pull requests:

1. **Read the README** – It describes the project structure and available Make
   targets.
2. **Run `make precommit` before each commit** – This runs the full build,
   formatting checks, static analysis, unit tests and coverage. Fix any issues
   before committing.
3. **Verify builds** – Use `make build` to ensure the firmware compiles and to
   display its size.
4. **Open Pull Requests with summaries** – Clearly describe what changed and why
   in the PR body.
5. **Leave the working tree clean** – Commit only complete changes and confirm
   `git status` shows no untracked files before ending a PR.

