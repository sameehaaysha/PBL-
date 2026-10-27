#include <string.h>
#include "lru.h"

int lru_simulate(
    const int pages[],
    int page_count,
    int frame_count,
    SimulationResult *result
)
{
    int frames[MAX_FRAMES];
    int last_used[MAX_FRAMES];
    int i, j;

    /* Validate input */
    if (pages == NULL || result == NULL ||
        page_count <= 0 || page_count > MAX_REFERENCES ||
        frame_count <= 0 || frame_count > MAX_FRAMES) {
        return 0;
    }

    /* Initialize result */
    memset(result, 0, sizeof(*result));

    result->algorithm = ALGORITHM_LRU;
    result->frame_count = frame_count;
    result->total_references = page_count;

    /* Initialize all frames as empty */
    for (i = 0; i < frame_count; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    /* Process each requested page */
    for (i = 0; i < page_count; i++) {
        int page = pages[i];
        int found = 0;
        int empty_frame = -1;
        int lru_frame = 0;
        int replaced_page = -1;
        int replaced_frame = -1;

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
            /* Page hit */
            result->total_hits++;
        } else {
            /* Page fault */
            result->total_faults++;

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

                /* Record the replaced page and frame */
                replaced_page = frames[lru_frame];
                replaced_frame = lru_frame;

                /* Replace the least recently used page */
                frames[lru_frame] = page;
                last_used[lru_frame] = i;
            }
        }

        /* Save information about this simulation step */
        result->steps[i].page = page;
        result->steps[i].status = found ? PAGE_HIT : PAGE_FAULT;
        result->steps[i].replaced_page = replaced_page;
        result->steps[i].replaced_frame = replaced_frame;

        /* Save frame contents after this request */
        for (j = 0; j < frame_count; j++) {
            result->steps[i].frames[j] = frames[j];
        }
    }

    /* Calculate hit and fault ratios */
    result->hit_ratio =
        (double)result->total_hits / page_count;

    result->fault_ratio =
        (double)result->total_faults / page_count;

    return 1;
}
