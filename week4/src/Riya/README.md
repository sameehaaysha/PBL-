# LRU Page Replacement Algorithm

## 1. Introduction

The Least Recently Used (LRU) algorithm is a page replacement algorithm used in operating systems for memory management. When all memory frames are full and a new page needs to be loaded, LRU replaces the page that has not been used for the longest time.

This module implements the LRU algorithm using the C programming language as part of the Page Replacement Algorithms project.

## 2. Files Included

* **`lru.c`** – Contains the implementation of the LRU algorithm.
* **`lru.h`** – Contains the function declarations and result structure.
* **`test_lru.c`** – Tests the LRU implementation.
* **`test.md`** – Documents the test case, expected results, and actual output.

## 3. Working of the Algorithm

1. Accepts the page reference string and the number of memory frames.
2. Checks whether the requested page is already present in memory.
3. If the page is present, counts it as a page hit.
4. If the page is absent, counts it as a page fault.
5. Loads the page into an empty frame if one is available.
6. If all frames are full, replaces the least recently used page.
7. Calculates the total page hits and page faults after processing all page references.

## 4. Compilation and Execution

The LRU module can be tested independently using GCC.

Open the terminal in the `Riya/test` directory.

**Compile the program:**

```bash
gcc -Wall -Wextra -std=c11 -I.. ../lru.c test_lru.c -o test_lru
```

**Run the test:**

```bash
./test_lru
```

The test program checks whether the LRU algorithm produces the expected page hit and page fault counts.

## 5. Technologies Used

* **Programming Language:** C
* **Compiler:** GCC
* **Development Environment:** Visual Studio Code with Ubuntu/WSL

## 6. Conclusion

The LRU module demonstrates how memory frames are managed using the Least Recently Used page replacement strategy. It is designed to be tested independently and integrated with the team's other page replacement algorithms.
