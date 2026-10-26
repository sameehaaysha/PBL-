# LRU Algorithm Testing

## 1. Objective

To test the Least Recently Used (LRU) page replacement algorithm and verify that it correctly calculates page hits and page faults.

## 2. Test Input

* **Page reference string:** `1 2 3 1 4`
* **Number of memory frames:** `3`

## 3. Test Procedure

1. Initialize three memory frames.
2. Process the given page reference string.
3. Check whether each requested page is already present in memory.
4. Count page hits and page faults.
5. Compare the actual results with the expected results.

## 4. Expected Results

| Metric                | Expected Value |
| --------------------- | -------------: |
| Total page references |              5 |
| Page hits             |              1 |
| Page faults           |              4 |
| Hit ratio             |           0.20 |
| Fault ratio           |           0.80 |

## 5. Actual Output

```text
Total page hits: 1
Total page faults: 4
Hit ratio: 0.20
Fault ratio: 0.80
TEST PASSED
```

## 6. Result

**Status: PASS**

The test passed because the actual page hit and page fault counts matched the expected values for the given input.
