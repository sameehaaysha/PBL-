#include "process.h"
#include <stdio.h>
#include <string.h>
#include "../Sameeha/common.h"



/* Initialize process and resource information */
void initialize_processes(SystemState *system)
{
    if (system == NULL)
    {
        return;
    }

    for (int i = 0; i < system->process_count; i++)
    {
        system->processes[i].pid = i;
        snprintf(system->processes[i].name,
                 MAX_NAME,
                 "P%d",
                 i);
    }
}

void initialize_resources(SystemState *system)
{
    if (system == NULL)
    {
        return;
    }

    for (int j = 0; j < system->resource_count; j++)
    {
        system->resources[j].resource_id = j;
        snprintf(system->resources[j].name,
                 MAX_NAME,
                 "R%d",
                 j);
    }
}

/* Set total instances of each resource */
int set_total_resources(SystemState *system, int resource, int total)
{
    if (system == NULL ||
        resource < 0 ||
        resource >= system->resource_count ||
        total < 0)
    {
        return 0;
    }

    int allocated = 0;

    for (int i = 0; i < system->process_count; i++)
    {
        allocated += system->allocation[i][resource];
    }

    if (allocated > total)
    {
        return 0;
    }

    system->resources[resource].total = total;
    calculate_available(system);

    return 1;
}

/* Set the number of allocated resource instances */
int set_allocation(SystemState *system,
                   int process,
                   int resource,
                   int value)
{
    if (system == NULL ||
        process < 0 || process >= system->process_count ||
        resource < 0 || resource >= system->resource_count ||
        value < 0)
    {
        return 0;
    }

    int old_value = system->allocation[process][resource];

    system->allocation[process][resource] = value;

    int allocated = 0;

    for (int i = 0; i < system->process_count; i++)
    {
        allocated += system->allocation[i][resource];
    }

    if (allocated > system->resources[resource].total)
    {
        system->allocation[process][resource] = old_value;
        return 0;
    }

    calculate_available(system);
    calculate_need(system);

    return 1;
}

/* Set maximum resources a process may require */
int set_maximum(SystemState *system,
                int process,
                int resource,
                int value)
{
    if (system == NULL ||
        process < 0 || process >= system->process_count ||
        resource < 0 || resource >= system->resource_count ||
        value < 0)
    {
        return 0;
    }

    if (value < system->allocation[process][resource])
    {
        return 0;
    }

    system->maximum[process][resource] = value;
    calculate_need(system);

    return 1;
}

/* Calculate Need = Maximum - Allocation */
void calculate_need(SystemState *system)
{
    if (system == NULL)
    {
        return;
    }

    for (int i = 0; i < system->process_count; i++)
    {
        for (int j = 0; j < system->resource_count; j++)
        {
            system->need[i][j] =
                system->maximum[i][j] -
                system->allocation[i][j];
        }
    }
}

/* Calculate Available = Total - Allocated */
void calculate_available(SystemState *system)
{
    if (system == NULL)
    {
        return;
    }

    for (int j = 0; j < system->resource_count; j++)
    {
        int allocated = 0;

        for (int i = 0; i < system->process_count; i++)
        {
            allocated += system->allocation[i][j];
        }

        system->available[j] =
            system->resources[j].total - allocated;

        system->resources[j].available = system->available[j];
    }
}

/* Check whether a resource request is valid */
int validate_request(const SystemState *system,
                     int process,
                     const int request[])
{
    if (system == NULL ||
        request == NULL ||
        process < 0 ||
        process >= system->process_count)
    {
        return 0;
    }

    for (int j = 0; j < system->resource_count; j++)
    {
        if (request[j] < 0 ||
            request[j] > system->need[process][j] ||
            request[j] > system->available[j])
        {
            return 0;
        }
    }

    return 1;
}

/* Display process and resource information */
void display_processes(const SystemState *system)
{
    if (system == NULL)
    {
        return;
    }

    printf("\nProcess Information\n");
    printf("-------------------\n");

    for (int i = 0; i < system->process_count; i++)
    {
        printf("PID: %d | Name: %s\n",
               system->processes[i].pid,
               system->processes[i].name);
    }
}

void display_resources(const SystemState *system)
{
    if (system == NULL)
    {
        return;
    }

    printf("\nResource Information\n");
    printf("--------------------\n");

    for (int j = 0; j < system->resource_count; j++)
    {
        printf("Resource: %s | Total: %d | Available: %d\n",
               system->resources[j].name,
               system->resources[j].total,
               system->resources[j].available);
    }

    printf("\nAllocation Matrix:\n");

    for (int i = 0; i < system->process_count; i++)
    {
        printf("P%d: ", system->processes[i].pid);

        for (int j = 0; j < system->resource_count; j++)
        {
            printf("%d ", system->allocation[i][j]);
        }

        printf("\n");
    }

    printf("\nMaximum Matrix:\n");

    for (int i = 0; i < system->process_count; i++)
    {
        printf("P%d: ", system->processes[i].pid);

        for (int j = 0; j < system->resource_count; j++)
        {
            printf("%d ", system->maximum[i][j]);
        }

        printf("\n");
    }

    printf("\nNeed Matrix:\n");

    for (int i = 0; i < system->process_count; i++)
    {
        printf("P%d: ", system->processes[i].pid);

        for (int j = 0; j < system->resource_count; j++)
        {
            printf("%d ", system->need[i][j]);
        }

        printf("\n");
    }

    printf("\nAvailable Resources: ");

    for (int j = 0; j < system->resource_count; j++)
    {
        printf("%d ", system->available[j]);
    }

    printf("\n");
}