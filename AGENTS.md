# AGENTS.md

## Precommit Agent

All contributions must pass the `make precommit` gate. This command formats
sources, builds the firmware, runs tests, performs linting, and verifies that
unit test coverage remains at 100%. The policy applies universally—humans,
Codex, CI jobs and bots must all run this command locally before proposing
changes. Fix any failures before opening a pull request or pushing commits.

Maintainers: Codex
