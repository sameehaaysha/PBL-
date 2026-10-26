#include <stdio.h>
#include "../optimal.h"

int main(void)
{
    int refs[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3};
    int n = sizeof(refs) / sizeof(refs[0]);
    SimulationResult r;

    if (optimal_page_replacement(refs, n, 3, &r) != 0)
        return 1;

    printf("Page  F1  F2  F3  Status\n");

    for (int i = 0; i < n; i++) {
        SimulationStep *s = &r.steps[i];
        printf("%-6d", s->page);

        for (int j = 0; j < r.frame_count; j++)
            if (s->frames[j] == -1) printf(" -  ");
            else printf(" %-3d", s->frames[j]);

        printf(" %s\n", s->status == PAGE_HIT ? "Hit" : "Fault");
    }

    printf("\nHits: %d\nFaults: %d\nHit ratio: %.2f%%\nFault ratio: %.2f%%\n",
           r.total_hits, r.total_faults, r.hit_ratio, r.fault_ratio);

    return (r.total_hits == 4 && r.total_faults == 6) ? 0 : 1;
}