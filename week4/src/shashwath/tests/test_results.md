# Optimal Page Replacement — Test Results

## Test Configuration

- Reference string: `7 0 1 2 0 3 0 4 2 3`
- Number of frames: 3
- Algorithm: Optimal Page Replacement

## Execution Output

```text
Page  F1  F2  F3  Status
7     7   -   -   Fault
0     7   0   -   Fault
1     7   0   1   Fault
2     2   0   1   Fault
0     2   0   1   Hit
3     2   0   3   Fault
0     2   0   3   Hit
4     2   4   3   Fault
2     2   4   3   Hit
3     2   4   3   Hit
```

## Summary

| Metric | Result |
|---|---:|
| Total references | 10 |
| Page hits | 4 |
| Page faults | 6 |
| Hit ratio | 40.00% |
| Fault ratio | 60.00% |

## Result

**PASS** — The implementation produces the expected results for the given reference string with three frames.