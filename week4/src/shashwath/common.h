#ifndef COMMON_H
#define COMMON_H

#define MAX_REFERENCES 1000
#define MAX_FRAMES 100

typedef enum {
    ALGORITHM_FIFO = 1,
    ALGORITHM_LRU = 2,
    ALGORITHM_OPTIMAL = 3,
    ALGORITHM_ALL = 4
} AlgorithmType;

typedef enum {
    PAGE_FAULT = 0,
    PAGE_HIT = 1
} PageStatus;

typedef struct {
    int page;
    int frames[MAX_FRAMES];
    PageStatus status;
    int replaced_page;
    int replaced_frame;
} SimulationStep;

typedef struct {
    int algorithm;
    int frame_count;
    int total_references;
    int total_hits;
    int total_faults;
    double hit_ratio;
    double fault_ratio;
    SimulationStep steps[MAX_REFERENCES];
} SimulationResult;

#endif