#include <stdio.h>
#include "lru.h"    

int main(void)
{
    int pages[] = {1, 2, 3, 1, 4};
    int page_count = sizeof(pages) / sizeof(pages[0]);
    int frame_count = 3;

    SimulationResult result;

    if (!lru_simulate(pages, page_count, frame_count, &result)) {
        printf("Simulation failed: invalid input.\n");
        return 1;
    }
    
    printf("Total page hits: %d\n", result.total_hits);
    printf("Total page faults: %d\n", result.total_faults);
    printf("Hit ratio: %.2f\n", result.hit_ratio);
    printf("Fault ratio: %.2f\n", result.fault_ratio);

    if (result.total_hits == 1 &&
        result.total_faults == 4 &&
        result.hit_ratio == 0.20 &&
        result.fault_ratio == 0.80) {
        printf("TEST PASSED\n");
        return 0;
    }

    printf("TEST FAILED\n");
    return 1;
}
