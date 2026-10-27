# Comparison Results of Page Replacement Algorithms

## 1. Introduction

The Page Replacement Simulator compares three page replacement algorithms: FIFO (First-In, First-Out), LRU (Least Recently Used), and Optimal. The purpose is to understand how each algorithm manages memory frames and handles page faults.

## 2. Test Input

The following page reference string is used to test all three algorithms.

* **Page Reference String:** `1 2 3 4 1 2 5 1 2 3 4 5`
* **Number of Frames:** 3
* **Total Page References:** 12

The same input is used for all algorithms to ensure a fair comparison.

## 3. Comparison Table

| Algorithm | Page Hits | Page Faults | Hit Ratio | Fault Ratio |
| --------- | --------: | ----------: | --------: | ----------: |
| FIFO      |           |             |           |             |
| LRU       |           |             |           |             |
| Optimal   |           |             |           |             |

*Note: Fill in the values displayed by your simulator after running each algorithm. The results depend on the reference string and number of frames.*

## 4. Algorithm Analysis

### FIFO (First-In, First-Out)

FIFO replaces the page that has been in memory for the longest time. It is simple to implement but may remove a page that will be needed again soon.

### LRU (Least Recently Used)

LRU replaces the page that has not been used for the longest time. It uses recent page usage to decide which page to remove.

### Optimal Page Replacement

Optimal replaces the page whose next use is farthest in the future, or that will not be used again. It is useful as a benchmark because it produces the minimum possible number of page faults for a given reference string when implemented correctly.

## 5. Observations

* The number of page hits and page faults differs between algorithms.
* A page hit occurs when the requested page is already in memory.
* A page fault occurs when the requested page is not in memory.
* Hit ratio indicates the proportion of references that result in hits.
* Fault ratio indicates the proportion of references that result in faults.
* Optimal provides a benchmark for evaluating FIFO and LRU.

## 6. Conclusion

The comparison feature helps users understand the differences between FIFO, LRU, and Optimal page replacement algorithms. By using the same reference string and number of frames, users can compare their page hits, page faults, and ratios to evaluate their performance.
