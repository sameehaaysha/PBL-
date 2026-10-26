#include <stdio.h>
#include <string.h>
#include "lru.h"

int lru_simulate(
    const int pages[],
    int page_count,
    int frame_count,
    LRUResult *result
) {
    int frames[MAX_FRAMES];
    int last_used[MAX_FRAMES];
    int i, j;

    if (pages == NULL || result == NULL ||
        page_count <= 0 || page_count > MAX_PAGES ||
        frame_count <= 0 || frame_count > MAX_FRAMES) {
        return 0;
    }

    memset(result, 0, sizeof(*result));

    /* Initialize all frames as empty */
    for (i = 0; i < frame_count; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    result->page_count = page_count;
    result->frame_count = frame_count;

    /* Process each requested page */
    for (i = 0; i < page_count; i++) {
        int page = pages[i];
        int found = 0;
        int empty_frame = -1;
        int lru_frame = 0;

        /* Check whether the page is already in memory */
        for (j = 0; j < frame_count; j++) {
            if (frames[j] == page) {
                found = 1;
                last_used[j] = i;
                break;
            }

            if (frames[j] == -1 && empty_frame == -1) {
                empty_frame = j;
            }
        }

        if (found) {
            result->page_hits++;
        } else {
            result->page_faults++;

            if (empty_frame != -1) {
                /* Use an empty frame */
                frames[empty_frame] = page;
                last_used[empty_frame] = i;
            } else {
                /* Find the least recently used page */
                for (j = 1; j < frame_count; j++) {
                    if (last_used[j] < last_used[lru_frame]) {
                        lru_frame = j;
                    }
                }

                /* Replace the least recently used page */
                frames[lru_frame] = page;
                last_used[lru_frame] = i;
            }
        }

        /* Save frame contents after this page request */
        for (j = 0; j < frame_count; j++) {
            result->frames[i][j] = frames[j];
        }
    }

    return 1;
}
