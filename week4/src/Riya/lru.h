#ifndef LRU_H
#define LRU_H

#define MAX_PAGES 100
#define MAX_FRAMES 20

typedef struct {
    int page_hits;
    int page_faults;
    int frame_count;
    int page_count;
    int frames[MAX_PAGES][MAX_FRAMES];
} LRUResult;

int lru_simulate(
    const int pages[],
    int page_count,
    int frame_count,
    LRUResult *result
);

#endif
