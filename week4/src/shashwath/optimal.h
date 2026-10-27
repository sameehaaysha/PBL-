#ifndef OPTIMAL_H
#define OPTIMAL_H
#include "../Sameeha/common.h"

int optimal_page_replacement(const int refs[], int ref_count,
                             int frame_count, SimulationResult *result);

#endif