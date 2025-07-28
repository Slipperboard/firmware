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
All commit messages **must** start with one of the following prefixes:

* `HOTFIX:`
* `FIX:`
* `FEATURE:`
* `ISSUE#<number>:`
* `FIXES#<number>:`
* `CLOSES#<number>:`

These `FIXES#` and `CLOSES#` prefixes may be written in any mix of uppercase or
lowercase letters.

Example:

```text
FIX: correct sensor initialization sequence
```

This ensures a consistent project history and helps automation tools categorize
changes correctly.

## Post-Merge Issue Closure

After a pull request is merged, the CI pipeline automatically closes issues that
meet **all** of the following conditions:

1. The issue has the `Codex` label.
2. Any commit message in the merged range contains `fixes#<issue>` or
   `closes#<issue>` (case-insensitive).
3. The issue is still open.

This automation only runs after merges and never closes issues based solely on
open pull requests.

Maintainers: Codex
