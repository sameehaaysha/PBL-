# PBL: Simulation and Comparative Analysis of Page Replacement Algorithms

## 1. Project Overview

This project simulates and compares three page replacement algorithms used in operating systems: **FIFO (First-In, First-Out), LRU (Least Recently Used), and Optimal Page Replacement**.

When a requested page is not present in memory, a page fault occurs. If all memory frames are occupied, the operating system must select a page to replace. This project demonstrates how different algorithms make these replacement decisions.

The system calculates page hits, page faults, hit ratios, and fault ratios to help compare the performance of the algorithms.

## 2. Objectives

* Understand page replacement in operating systems.
* Implement FIFO, LRU, and Optimal algorithms using C.
* Simulate page references with a fixed number of memory frames.
* Track page hits, page faults, and memory frame changes.
* Compare the performance of different algorithms.
* Develop and test the project using modular programming.

## 3. Technologies Used

| Technology             | Purpose                                                           |
| ---------------------- | ----------------------------------------------------------------- |
| C Programming Language | Implementing page replacement algorithms and simulation logic     |
| GCC Compiler           | Compiling and executing C programs                                |
| VS Code                | Writing and managing source code                                  |
| Header Files (`.h`)    | Sharing function declarations, structures, and common definitions |
| Git and GitHub         | Version control and team collaboration                            |
| Makefile               | Automating compilation, if configured                             |

## 4. Algorithms Implemented

### FIFO — First-In, First-Out

Replaces the page that entered memory first. It follows a queue-like approach and is simple to implement.

### LRU — Least Recently Used

Replaces the page that has not been used for the longest time. It tracks recent page usage to decide which page to remove.

### Optimal Page Replacement

Replaces the page whose next use is farthest in the future. It helps determine the minimum possible page faults for a given reference string.

## 5. Team Members and Division of Work

| Team Member             | Responsibility                                                                     |
| ----------------------- | ---------------------------------------------------------------------------------- |
| **Sameeha (Team Lead)** | Main program, shared header file (`common.h`), GUI, and integration of all modules |
| **Joannes**             | FIFO page replacement algorithm and testing                                        |
| **Riya Hency Dsa**      | LRU page replacement algorithm, result calculations, and testing                   |
| **Shashwath**           | Optimal page replacement algorithm and testing                                     |

Each member develops and tests their assigned module. The modules are then integrated using shared definitions to create the complete application.

## 6. Key Features

* Simulates FIFO, LRU, and Optimal page replacement.
* Accepts a page reference string and number of memory frames.
* Tracks page hits and page faults.
* Records memory frame contents after each page reference.
* Calculates hit ratio and fault ratio.
* Supports comparison of algorithm performance.
* Provides a common interface for integration, with a GUI if included in the final build.

## 7. Performance Metrics

* **Page Hit:** The requested page is already present in memory.
* **Page Fault:** The requested page is not present in memory.
* **Hit Ratio:** Total page hits divided by total page references.
* **Fault Ratio:** Total page faults divided by total page references.

These metrics help evaluate how efficiently each algorithm manages memory for the same page reference string.

## 8. Testing

Each algorithm is tested independently to verify page replacement decisions, memory frame updates, page hit and fault counts, and calculated ratios.

After individual testing, the modules are integrated and tested together to check the overall functionality of the application.

## 9. Conclusion

This project demonstrates how page replacement algorithms manage limited memory in an operating system. By implementing and comparing FIFO, LRU, and Optimal algorithms, we gain a practical understanding of memory management, algorithm design, C programming, software testing, and teamwork.
