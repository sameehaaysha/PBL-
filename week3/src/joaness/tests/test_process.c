#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../process.h"

int main(void)
{
    SystemState system;

    memset(&system, 0, sizeof(system));

    system.process_count = 3;
    system.resource_count = 2;

    initialize_processes(&system);
    initialize_resources(&system);

    /* Set total resources */
    assert(set_total_resources(&system, 0, 4));
    assert(set_total_resources(&system, 1, 3));

    /* Set allocations */
    assert(set_allocation(&system, 0, 0, 1));
    assert(set_allocation(&system, 0, 1, 0));

    assert(set_allocation(&system, 1, 0, 0));
    assert(set_allocation(&system, 1, 1, 1));

    assert(set_allocation(&system, 2, 0, 1));
    assert(set_allocation(&system, 2, 1, 1));

    /* Set maximum requirements */
    assert(set_maximum(&system, 0, 0, 2));
    assert(set_maximum(&system, 0, 1, 1));

    assert(set_maximum(&system, 1, 0, 1));
    assert(set_maximum(&system, 1, 1, 2));

    assert(set_maximum(&system, 2, 0, 2));
    assert(set_maximum(&system, 2, 1, 2));

    /* Recalculate matrices */
    calculate_need(&system);
    calculate_available(&system);

    /* Check need matrix */
    for (int i = 0; i < 3; i++)
    {
        assert(system.need[i][0] == 1);
        assert(system.need[i][1] == 1);
    }

    /* Check available resources */
    assert(system.available[0] == 2);
    assert(system.available[1] == 1);

    /* Valid request */
    int valid_request[2] = {1, 0};
    assert(validate_request(&system, 0, valid_request));

    /* Request exceeds remaining need */
    int excessive_request[2] = {2, 0};
    assert(!validate_request(&system, 0, excessive_request));

    /* Request exceeds available resources */
    int unavailable_request[2] = {0, 2};
    assert(!validate_request(&system, 0, unavailable_request));

    /* Invalid process ID */
    int another_request[2] = {0, 0};
    assert(!validate_request(&system, 5, another_request));

    /* Display information */
    display_processes(&system);
    display_resources(&system);

    printf("\nAll process and resource tests passed!\n");

    return 0;
}