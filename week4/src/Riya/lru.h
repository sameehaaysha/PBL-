#ifndef LRU_H
#define LRU_H

#include "../Sameeha/common.h"

/* Simulate the LRU page replacement algorithm */
int lru_simulate(
    const int pages[],
    int page_count,
    int frame_count,
    SimulationResult *result
);

#endif
