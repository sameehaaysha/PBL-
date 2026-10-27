FIFO Page Replacement Algorithm

Overview

This project implements the First-In, First-Out (FIFO) page replacement algorithm using C. It replaces the oldest page when all memory frames are full.

My Contribution

Role: Member 1 — FIFO Algorithm

* Implemented FIFO page replacement in fifo.c.
* Created the function declaration in fifo.h.
* Tested the algorithm using test_fifo.c.
* Calculated page hits, page faults, and their ratios.

Test Input

* Pages: 1, 2, 3, 1, 4, 2, 5
* Frames: 3

Output

Page Hits: 2
Page Faults: 5
Hit Ratio: 28.57%
Fault Ratio: 71.43%

Compile and Run

gcc fifo.c test_fifo.c -o test_fifo.exe
./test_fifo.exe

Conclusion

The FIFO algorithm was implemented and tested successfully, producing 2 page hits and 5 page faults.
