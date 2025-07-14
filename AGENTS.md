# AGENTS.md

## Precommit Agent

All contributions must pass the `make precommit` gate. This command formats
sources, builds the firmware, runs tests, and performs linting when available.
It applies to everyone—humans, Codex, CI jobs, and bots.

Fix any failures before opening a pull request or pushing changes.
