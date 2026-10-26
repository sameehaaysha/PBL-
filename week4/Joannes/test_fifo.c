#include <stdio.h>
#include "fifo.h"

int main(void) {
    // Page reference string
    int pages[] = {1, 2, 3, 1, 4, 2, 5};

    // Calculate the number of page requests
    int n = sizeof(pages) / sizeof(pages[0]);

    // Number of memory frames
    int capacity = 3;

    int hits = 0;
    int faults = 0;

    // Run the FIFO algorithm
    int result = fifo_page_replacement(
        pages,
        n,
        capacity,
        &hits,
        &faults
    );

    if (!result) {
        printf("FIFO execution failed. Check your inputs.\n");
        return 1;
    }

    // Display results
    printf("Page Replacement Algorithm: FIFO\n");
    printf("Number of Frames: %d\n", capacity);
    printf("Total Page Requests: %d\n", n);
    printf("Page Hits: %d\n", hits);
    printf("Page Faults: %d\n", faults);

    printf("Hit Ratio: %.2f%%\n",
           (hits * 100.0) / n);

    printf("Fault Ratio: %.2f%%\n",
           (faults * 100.0) / n);

    return 0;
}