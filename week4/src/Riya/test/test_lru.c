#include <stdio.h>
#include "lru.h"

int main(void)
{
    int pages[] = {1, 2, 3, 1, 4};
    int page_count = sizeof(pages) / sizeof(pages[0]);
    int frame_count = 3;

    LRUResult result;

    if (!lru_simulate(pages, page_count, frame_count, &result)) {
        printf("Simulation failed: invalid input.\n");
        return 1;
    }

    printf("Total page hits: %d\n", result.page_hits);
    printf("Total page faults: %d\n", result.page_faults);
    printf("Hit ratio: %.2f\n",
           (double)result.page_hits / page_count);
    printf("Fault ratio: %.2f\n",
           (double)result.page_faults / page_count);

    if (result.page_hits == 1 && result.page_faults == 4) {
        printf("TEST PASSED\n");
        return 0;
    }

    printf("TEST FAILED\n");
    return 1;
}