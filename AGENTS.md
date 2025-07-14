# AGENTS.md

...

## Agent: Precommit Agent

- **Type**: Universal validation gate
- **Purpose**: Enforce code quality and consistency before integration
- **Command**: `make precommit`
- **Scope**: **Applies to all contributors and systems**, including:
  - Human developers
  - Codex (LLM assistant)
  - CI jobs (pre-merge verification)
  - Any automated tool or bot producing a pull request
- **Checks Run**:
  - Code formatting (`make format-check`)
  - Compilation (`make build`)
  - Unit tests (`make test`)
  - Static analysis or linting (if configured)
- **Policy**:
  - If `make precommit` fails, the code **must not** be submitted for review
  - All agents are expected to self-verify via this mechanism before initiating a PR or push
  - CI will redundantly enforce it to ensure compliance
- **Interacts With**:
  - Makefile (delegates to individual targets)
  - All other agents (enforcement and feedback)

...

## Contributor Policy

> **All contributors — including AI agents, humans, CI scripts, and bots — must run:**

```bash
make precommit
```
