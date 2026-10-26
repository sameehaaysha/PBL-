#include <string.h>
#include "optimal.h"

static int next_use(const int r[], int n, int page, int pos)
{
    for (int i = pos + 1; i < n; i++)
        if (r[i] == page) return i;
    return -1;
}

static int victim(const int r[], int n, int f[], int count, int pos)
{
    int v = 0, farthest = -1;
    for (int i = 0; i < count; i++) {
        int next = next_use(r, n, f[i], pos);
        if (next == -1) return i;
        if (next > farthest) farthest = next, v = i;
    }
    return v;
}

int optimal_page_replacement(const int refs[], int n,
                             int count, SimulationResult *res)
{
    if (!refs || !res || n <= 0 || n > MAX_REFERENCES ||
        count <= 0 || count > MAX_FRAMES)
        return -1;

    for (int i = 0; i < n; i++)
        if (refs[i] < 0) return -1;

    memset(res, 0, sizeof(*res));
    res->algorithm = ALGORITHM_OPTIMAL;
    res->frame_count = count;
    res->total_references = n;

    int f[MAX_FRAMES];
    for (int i = 0; i < count; i++) f[i] = -1;

    for (int i = 0; i < n; i++) {
        SimulationStep *s = &res->steps[i];
        int j, hit = 0;

        s->page = refs[i];
        s->replaced_page = s->replaced_frame = -1;

        for (j = 0; j < count; j++)
            if (f[j] == refs[i]) { hit = 1; break; }

        if (hit) {
            s->status = PAGE_HIT;
            res->total_hits++;
        } else {
            s->status = PAGE_FAULT;
            res->total_faults++;

            for (j = 0; j < count && f[j] != -1; j++);

            if (j == count) {
                j = victim(refs, n, f, count, i);
                s->replaced_page = f[j];
                s->replaced_frame = j;
            }
            f[j] = refs[i];
        }

        for (j = 0; j < count; j++) s->frames[j] = f[j];
    }

    res->hit_ratio = 100.0 * res->total_hits / n;
    res->fault_ratio = 100.0 * res->total_faults / n;
    return 0;
}