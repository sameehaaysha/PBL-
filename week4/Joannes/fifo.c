#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

int fifo_page_replacement(
    const int pages[],
    int n,
    int capacity,
    int *hits,
    int *faults
) {
    // Validate input
    if (pages == NULL || hits == NULL || faults == NULL ||
        n <= 0 || capacity <= 0) {
        return 0;
    }

    // Create memory frames
    int *frames = malloc(capacity * sizeof(int));

    if (frames == NULL) {
        return 0;
    }

    int count = 0;
    int next = 0;

    *hits = 0;
    *faults = 0;

    // Process each requested page
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check whether the page is already in memory
        for (int j = 0; j < count; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (found) {
            // Page hit
            (*hits)++;
        } else {
            // Page fault
            (*faults)++;

            if (count < capacity) {
                // Use an empty frame
                frames[count] = page;
                count++;
            } else {
                // Replace the oldest page
                frames[next] = page;

                // Move to the next replacement position
                next = (next + 1) % capacity;
            }
        }
    }

    free(frames);

    return 1;
}