#ifndef FIFO_H
#define FIFO_H

int fifo_page_replacement(
    const int pages[],
    int n,
    int capacity,
    int *hits,
    int *faults
);

#endif