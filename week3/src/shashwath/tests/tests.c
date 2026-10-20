
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../deadlock.h"

static void setup(SystemState *s)
{
    memset(s, 0, sizeof(*s));
    s->process_count = 2;
    s->resource_count = 1;
    s->resources[0].total = 3;
    s->available[0] = s->resources[0].available = 1;

    for (int i = 0; i < 2; i++) {
        s->processes[i].pid = i;
        s->allocation[i][0] = s->processes[i].allocation[0] = 1;
    }
    s->maximum[0][0] = s->processes[0].maximum[0] = 2;
    s->maximum[1][0] = s->processes[1].maximum[0] = 1;
    s->need[0][0] = s->processes[0].need[0] = 1;
}

static void make_deadlock(SystemState *s)
{
    memset(s, 0, sizeof(*s));
    s->process_count = s->resource_count = 2;

    for (int i = 0; i < 2; i++) {
        s->processes[i].pid = i;
        s->allocation[i][i] = s->processes[i].allocation[i] = 1;
        s->maximum[i][0] = s->maximum[i][1] = 1;
        s->need[i][0] = s->need[i][1] = 1;
        s->processes[i].maximum[0] = s->processes[i].maximum[1] = 1;
        s->processes[i].need[0] = s->processes[i].need[1] = 1;
        s->request[i][1 - i] = 1;
    }
}

int main(void)
{
    SystemState s;
    int req[MAX_RESOURCES] = {1};

    setup(&s);
    assert(bankers_algorithm(&s) == 1);
    assert(s.safe_sequence_length == 2);
    assert(s.safe_sequence[0] == 0 && s.safe_sequence[1] == 1);

    setup(&s);
    s.available[0] = 0;
    s.need[0][0] = s.need[1][0] = 2;
    s.maximum[0][0] = s.maximum[1][0] = 3;
    assert(bankers_algorithm(&s) == 0);

    make_deadlock(&s);
    assert(detect_deadlock(&s) == 2);

    make_deadlock(&s);
    recover_from_deadlock(&s);
    assert(s.processes[0].completed == 1);
    assert(s.available[0] == 1);
    assert(s.deadlocked_count == 0);

    setup(&s);
    assert(request_resources(&s, 0, req) == 1);
    assert(s.allocation[0][0] == 2 && s.available[0] == 0);

    puts("All deadlock tests passed.");
    return 0;
}
