from pathlib import Path
import subprocess
import sys

TEST_DIR = Path("tests")

EXECUTABLE = "../../cmake-build-debug/prb1"

passed = 0
failed = 0

for input_file in sorted(TEST_DIR.glob("input-*.txt")):

    answer_file = TEST_DIR / input_file.name.replace(
        "input",
        "answer"
    )

    result = subprocess.run(
        [EXECUTABLE],
        stdin=open(input_file),
        capture_output=True,
        text=True
    )

    actual = result.stdout.strip()
    expected = answer_file.read_text().strip()

    if actual == expected:
        print(f"PASS: {input_file.name}")
        passed += 1
    else:
        print(f"FAIL: {input_file.name}")
        print("Expected:")
        print(expected)
        print("Actual:")
        print(actual)
        print()
        failed += 1

print()
print(f"Passed: {passed}")
print(f"Failed: {failed}")

sys.exit(failed)