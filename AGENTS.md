# AGENTS.md

This repository hosts the **Slipperboard** firmware, a PlatformIO-based firmware
template for ESP32 boards using the Arduino framework. All contributors should
follow the steps below when working with the project.

## Getting the Source
1. Clone the repository and enter the directory:
   ```bash
   git clone <REPO_URL>
   cd firmware
   ```

## Preparing the Development Environment
Run the provided setup script to install the necessary toolchain and Python
packages:
```bash
make env
```
This installs clang-format, clang-tidy, cppcheck, gcovr, PlatformIO and other
dependencies.

## Building the Firmware
Compile the project using PlatformIO through the Makefile:
```bash
make build
```

## Running Tests
Execute the unit test suite with:
```bash
make test
```

## Precommit Checks
Before creating a commit, every contributor **must** run:
```bash
make precommit
```
This command formats sources, lints the code, builds the firmware, runs tests,
and verifies that unit test coverage remains at 100%. Fix any failures before
opening a pull request or pushing commits.

## Commit Message Format
All commit messages **must** start with one of the following patterns:

* `HOTFIX`, `FIX`, `FEATURE`, or `ISSUE#<number>` followed by `:` or `-`
* A GitHub issue-closing keyword such as `fixes`, `closes`, or `resolves` followed by `#<number>`

Keywords may be written in **uppercase**, **lowercase**, or **Title Case**. A space may optionally appear around the dash.

Example:

```text
fix - correct sensor initialization sequence
Fixes #42 - adjust button debounce logic
```

This ensures a consistent project history and helps automation tools categorize
changes correctly.

Maintainers: Codex
