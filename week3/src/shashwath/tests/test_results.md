# DEADLOCK ALGORITHMS — TEST RESULTS

## 1. TEST ENVIRONMENT

- Language: C
- Compiler: GCC
- Standard: C11
- Compiler flags: `-Wall -Wextra -Wpedantic -std=c11`
- Test file: `tests/tests.c`
- Implementation file: `deadlock.c`

## 2. COMPILATION

Command used:

```bash
gcc -Wall -Wextra -Wpedantic -std=c11 \
    shashwath/deadlock.c shashwath/tests/tests.c \
    -o shashwath/test_deadlock
```

Result: **PASS**

The program compiled successfully and generated the test executable without displaying compiler warnings or errors.

## 3. TEST CASES

| Test Case | Description | Expected Result | Actual Result |
|---|---|---|---|
| TC01 | Banker’s Algorithm — safe state | System identified as safe | PASS |
| TC02 | Banker’s Algorithm — unsafe state | System identified as unsafe | PASS |
| TC03 | Deadlock detection | Both deadlocked processes identified | PASS |
| TC04 | Deadlock recovery | A deadlocked process terminated and its allocated resources released | PASS |
| TC05 | Resource request | Safe request granted and resource allocation updated | PASS |

## 4. EXECUTION OUTPUT

```text
Terminating process 0 to recover.
All deadlock tests passed.
```

## 5. TEST SUMMARY

- Total test cases: 5
- Passed: 5
- Failed: 0
- Overall status: PASS

## 6. CONCLUSION

The deadlock module compiled and passed all five implemented test cases. The tests verified safe and unsafe state checking using Banker’s Algorithm, deadlock detection, recovery by terminating a deadlocked process, and safe resource-request handling.

Further integration testing with the complete team project is required to verify compatibility with the shared data structures and other modules.
