#!/usr/bin/env python3
import re
import sys
from pathlib import Path

try:
    import markdown
except ImportError:
    print("markdown module is required. Install with 'pip install markdown'.", file=sys.stderr)
    sys.exit(1)

EMAIL_RE = re.compile(r"^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$")


def check_file(path: Path) -> list[str]:
    errors = []
    try:
        text = path.read_text(encoding="utf-8")
    except Exception as e:
        errors.append(f"{path}: unable to read: {e}")
        return errors

    # ensure markdown parses without raising exceptions
    try:
        markdown.markdown(text)
    except Exception as e:
        errors.append(f"{path}: markdown parse error: {e}")

    maintainers_line = None
    for line in text.splitlines():
        if line.lower().startswith("maintainers:"):
            maintainers_line = line
            break
    if not maintainers_line:
        errors.append(f"{path}: missing maintainers list")
    else:
        emails = re.findall(r"<([^>]+)>", maintainers_line)
        if not emails:
            errors.append(f"{path}: no email addresses found in maintainers line")
        for email in emails:
            if not EMAIL_RE.match(email):
                errors.append(f"{path}: invalid email address '{email}'")

    for idx, line in enumerate(text.splitlines(), start=1):
        if line.rstrip() != line:
            errors.append(f"{path}:{idx}: trailing whitespace")
        if "\t" in line:
            errors.append(f"{path}:{idx}: tab character found")
    if not text.endswith("\n"):
        errors.append(f"{path}: missing newline at end of file")
    return errors


def main(paths: list[str]) -> int:
    all_errors: list[str] = []
    files = [Path(p) for p in paths] if paths else list(Path('.').rglob('*.md'))
    for f in files:
        all_errors.extend(check_file(f))
    if all_errors:
        for err in all_errors:
            print(err)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
