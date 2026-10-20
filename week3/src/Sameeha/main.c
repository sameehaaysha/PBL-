#include "common.h"
#include "../joannes/process.h"
#include "../shashwath/deadlock.h"
#include "../riya/gui.h"

/*
 * WEEK 4 - DEADLOCK SIMULATION SYSTEM
 * Member 1 - Sameeha
 * Role: Team Lead / Main Integration
 *
 * This file controls:
 * - Main menu
 * - User input
 * - System initialization
 * - Module integration
 * - Resource requests
 * - Display and control flow
 *
 * Process/resource operations are handled by Joannes.
 * Deadlock algorithms are handled by Shashwath.
 * GUI will be connected through Riya's module.
 */


/* =========================================================
   SYSTEM INITIALIZATION
   ========================================================= */

void initialize_system(SystemState *system)
{
    int i, j;

    if (system == NULL)
        return;

    system->process_count = 0;
    system->resource_count = 0;
    system->safe_sequence_length = 0;
    system->deadlocked_count = 0;

    for (i = 0; i < MAX_RESOURCES; i++)
    {
        system->available[i] = 0;
        system->resources[i].resource_id = i;
        system->resources[i].total = 0;
        system->resources[i].available = 0;
        system->resources[i].name[0] = '\0';
    }

    for (i = 0; i < MAX_PROCESSES; i++)
    {
        system->safe_sequence[i] = -1;
        system->deadlocked[i] = 0;

        system->processes[i].pid = -1;
        system->processes[i].name[0] = '\0';
        system->processes[i].completed = 0;
        system->processes[i].deadlocked = 0;

        for (j = 0; j < MAX_RESOURCES; j++)
        {
            system->allocation[i][j] = 0;
            system->maximum[i][j] = 0;
            system->need[i][j] = 0;
            system->request[i][j] = 0;

            system->processes[i].allocation[j] = 0;
            system->processes[i].maximum[j] = 0;
            system->processes[i].need[j] = 0;
        }
    }
}


/* =========================================================
   INPUT UTILITY
   ========================================================= */

void clear_input_buffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* discard invalid input */
    }
}


/* =========================================================
   CREATE PROCESSES
   ========================================================= */

void create_processes(SystemState *system)
{
    int n;
    int i;

    printf("\n====================================\n");
    printf("        CREATE PROCESSES\n");
    printf("====================================\n");

    printf("Enter number of processes (1-%d): ", MAX_PROCESSES);

    if (scanf("%d", &n) != 1)
    {
        printf("Invalid input.\n");
        clear_input_buffer();
        return;
    }

    if (n < 1 || n > MAX_PROCESSES)
    {
        printf("Invalid number of processes.\n");
        return;
    }

    system->process_count = n;

    /*
     * Use Joannes' process initialization.
     */
    initialize_processes(system);

    for (i = 0; i < n; i++)
    {
        printf("\nProcess %d name: ", i);

        if (scanf("%49s", system->processes[i].name) != 1)
        {
            printf("Invalid process name.\n");
            clear_input_buffer();

            snprintf(
                system->processes[i].name,
                MAX_NAME,
                "P%d",
                i
            );
        }

        system->processes[i].pid = i;
        system->processes[i].completed = 0;
        system->processes[i].deadlocked = 0;
    }

    printf("\nProcesses created successfully.\n");
}


/* =========================================================
   CREATE RESOURCES
   ========================================================= */

void create_resources(SystemState *system)
{
    int n;
    int i;
    int total;

    printf("\n====================================\n");
    printf("        CREATE RESOURCES\n");
    printf("====================================\n");

    printf("Enter number of resources (1-%d): ", MAX_RESOURCES);

    if (scanf("%d", &n) != 1)
    {
        printf("Invalid input.\n");
        clear_input_buffer();
        return;
    }

    if (n < 1 || n > MAX_RESOURCES)
    {
        printf("Invalid number of resources.\n");
        return;
    }

    system->resource_count = n;

    initialize_resources(system);

    for (i = 0; i < n; i++)
    {
        printf("\nResource %d name: ", i);

        if (scanf("%49s", system->resources[i].name) != 1)
        {
            printf("Invalid resource name.\n");
            clear_input_buffer();

            snprintf(
                system->resources[i].name,
                MAX_NAME,
                "R%d",
                i
            );
        }

        system->resources[i].resource_id = i;

        printf(
            "Total instances of %s: ",
            system->resources[i].name
        );

        if (scanf("%d", &total) != 1)
        {
            printf("Invalid resource value.\n");
            clear_input_buffer();
            total = 0;
        }

        if (total < 0)
            total = 0;

        if (!set_total_resources(system, i, total))
        {
            printf("Unable to set resource total.\n");
            system->resources[i].total = total;
            system->resources[i].available = total;
            system->available[i] = total;
        }
    }

    printf("\nResources created successfully.\n");
}


/* =========================================================
   ENTER ALLOCATION MATRIX
   ========================================================= */

void enter_allocation_matrix(SystemState *system)
{
    int i, j;
    int value;

    if (system->process_count == 0 ||
        system->resource_count == 0)
    {
        printf(
            "\nPlease create processes and resources first.\n"
        );
        return;
    }

    printf("\n====================================\n");
    printf("        ALLOCATION MATRIX\n");
    printf("====================================\n");

    for (i = 0; i < system->process_count; i++)
    {
        printf(
            "\nProcess %d (%s)\n",
            i,
            system->processes[i].name
        );

        for (j = 0; j < system->resource_count; j++)
        {
            printf("Allocation of R%d: ", j);

            if (scanf("%d", &value) != 1)
            {
                printf("Invalid value. Using 0.\n");
                clear_input_buffer();
                value = 0;
            }

            if (value < 0)
                value = 0;

            /*
             * Use Joannes' validation function.
             */
            if (!set_allocation(system, i, j, value))
            {
                printf(
                    "Allocation exceeds available resources. "
                    "Using 0.\n"
                );

                /*
                 * Reset to zero if invalid.
                 */
                set_allocation(system, i, j, 0);
            }
        }
    }

    calculate_available(system);
    calculate_need(system);

    printf("\nAllocation matrix entered successfully.\n");
}


/* =========================================================
   ENTER MAXIMUM MATRIX
   ========================================================= */

void enter_maximum_matrix(SystemState *system)
{
    int i, j;
    int value;

    if (system->process_count == 0 ||
        system->resource_count == 0)
    {
        printf(
            "\nPlease create processes and resources first.\n"
        );
        return;
    }

    printf("\n====================================\n");
    printf("        MAXIMUM MATRIX\n");
    printf("====================================\n");

    for (i = 0; i < system->process_count; i++)
    {
        printf(
            "\nProcess %d (%s)\n",
            i,
            system->processes[i].name
        );

        for (j = 0; j < system->resource_count; j++)
        {
            printf(
                "Maximum requirement of R%d: ",
                j
            );

            if (scanf("%d", &value) != 1)
            {
                printf("Invalid value. Using 0.\n");
                clear_input_buffer();
                value = 0;
            }

            if (value < 0)
                value = 0;

            /*
             * Maximum cannot be less than allocation.
             */
            if (value < system->allocation[i][j])
            {
                printf(
                    "Maximum cannot be less than allocation. "
                    "Using allocation value.\n"
                );

                value = system->allocation[i][j];
            }

            if (!set_maximum(system, i, j, value))
            {
                printf(
                    "Unable to set maximum value.\n"
                );
            }
        }
    }

    calculate_need(system);

    printf("\nMaximum matrix entered successfully.\n");
}


/* =========================================================
   DISPLAY NEED MATRIX
   ========================================================= */

void display_need_matrix(SystemState *system)
{
    int i, j;

    if (system->process_count == 0)
    {
        printf("\nNo processes available.\n");
        return;
    }

    calculate_need(system);

    printf("\n====================================\n");
    printf("           NEED MATRIX\n");
    printf("====================================\n");

    printf("       ");

    for (j = 0; j < system->resource_count; j++)
    {
        printf("R%-5d", j);
    }

    printf("\n");

    for (i = 0; i < system->process_count; i++)
    {
        printf("P%-5d", i);

        for (j = 0; j < system->resource_count; j++)
        {
            printf(
                "%-6d",
                system->need[i][j]
            );
        }

        printf("\n");
    }
}


/* =========================================================
   DISPLAY AVAILABLE RESOURCES
   ========================================================= */

void display_available_resources(SystemState *system)
{
    int j;

    calculate_available(system);

    printf("\nAvailable Resources:\n");

    for (j = 0; j < system->resource_count; j++)
    {
        printf(
            "R%d (%s) = %d\n",
            j,
            system->resources[j].name,
            system->available[j]
        );
    }
}


/* =========================================================
   RESOURCE ALLOCATION GRAPH - TEXT FALLBACK
   ========================================================= */

void display_resource_allocation_graph(SystemState *system)
{
    int i, j;

    printf("\n====================================\n");
    printf("      RESOURCE ALLOCATION GRAPH\n");
    printf("====================================\n");

    printf("\nAllocated Resources:\n");

    for (i = 0; i < system->process_count; i++)
    {
        for (j = 0; j < system->resource_count; j++)
        {
            if (system->allocation[i][j] > 0)
            {
                printf(
                    "R%d -> P%d [allocated: %d]\n",
                    j,
                    i,
                    system->allocation[i][j]
                );
            }
        }
    }

    printf("\nResource Requests:\n");

    for (i = 0; i < system->process_count; i++)
    {
        for (j = 0; j < system->resource_count; j++)
        {
            /*
             * Use outstanding requests if available.
             * Need is shown as fallback information.
             */
            if (system->request[i][j] > 0)
            {
                printf(
                    "P%d -> R%d [requested: %d]\n",
                    i,
                    j,
                    system->request[i][j]
                );
            }
        }
    }

    printf("\n------------------------------------\n");
}


/* =========================================================
   HANDLE RESOURCE REQUEST
   ========================================================= */

void handle_resource_request(SystemState *system)
{
    int process_id;
    int request[MAX_RESOURCES] = {0};
    int j;

    if (system->process_count == 0 ||
        system->resource_count == 0)
    {
        printf(
            "\nCreate processes and resources first.\n"
        );
        return;
    }

    printf("\n====================================\n");
    printf("        RESOURCE REQUEST\n");
    printf("====================================\n");

    printf("Enter process ID: ");

    if (scanf("%d", &process_id) != 1)
    {
        printf("Invalid process ID.\n");
        clear_input_buffer();
        return;
    }

    if (process_id < 0 ||
        process_id >= system->process_count)
    {
        printf("Invalid process ID.\n");
        return;
    }

    if (system->processes[process_id].completed)
    {
        printf("This process has already completed.\n");
        return;
    }

    printf(
        "\nEnter requested amount for each resource:\n"
    );

    for (j = 0; j < system->resource_count; j++)
    {
        printf("R%d: ", j);

        if (scanf("%d", &request[j]) != 1)
        {
            printf("Invalid value. Using 0.\n");
            clear_input_buffer();
            request[j] = 0;
        }

        if (request[j] < 0)
            request[j] = 0;
    }

    /*
     * Shashwath's request_resources()
     * performs the actual validation and
     * Banker's Algorithm safety check.
     */
    if (request_resources(system, process_id, request))
{
    printf("\nREQUEST GRANTED.\n");
}
else
{
    printf("\nREQUEST DENIED: Unsafe or insufficient resources.\n");
}

calculate_available(system);

    /*
     * Keep available values synchronized.
     */
    calculate_available(system);
}


/* =========================================================
   DISPLAY COMPLETE SYSTEM STATUS
   ========================================================= */

void display_system_status(SystemState *system)
{
    int i, j;

    printf("\n");
    printf("============================================\n");
    printf("          SYSTEM STATUS\n");
    printf("============================================\n");

    printf(
        "Processes : %d\n",
        system->process_count
    );

    printf(
        "Resources : %d\n",
        system->resource_count
    );

    display_available_resources(system);

    printf("\nAllocation Matrix:\n");

    for (i = 0; i < system->process_count; i++)
    {
        printf(
            "P%d : ",
            i
        );

        for (j = 0; j < system->resource_count; j++)
        {
            printf(
                "%d ",
                system->allocation[i][j]
            );
        }

        printf("\n");
    }

    printf("\nMaximum Matrix:\n");

    for (i = 0; i < system->process_count; i++)
    {
        printf(
            "P%d : ",
            i
        );

        for (j = 0; j < system->resource_count; j++)
        {
            printf(
                "%d ",
                system->maximum[i][j]
            );
        }

        printf("\n");
    }

    display_need_matrix(system);

    printf("\nProcess Status:\n");

    for (i = 0; i < system->process_count; i++)
    {
        printf(
            "P%d (%s): ",
            i,
            system->processes[i].name
        );

        if (system->processes[i].deadlocked)
        {
            printf("DEADLOCKED");
        }
        else if (system->processes[i].completed)
        {
            printf("COMPLETED");
        }
        else
        {
            printf("ACTIVE");
        }

        printf("\n");
    }

    printf("\n============================================\n");
}


/* =========================================================
   MAIN MENU
   ========================================================= */

void display_menu(void)
{
    printf("\n");
    printf("============================================\n");
    printf("       DEADLOCK SIMULATION SYSTEM\n");
    printf("============================================\n");

    printf("1.  Create Processes\n");
    printf("2.  Create Resources\n");
    printf("3.  Enter Allocation Matrix\n");
    printf("4.  Enter Maximum Matrix\n");
    printf("5.  Display Need Matrix\n");
    printf("6.  Display Resource Allocation Graph\n");
    printf("7.  Request Resources\n");
    printf("8.  Run Banker's Algorithm\n");
    printf("9.  Detect Deadlock\n");
    printf("10. Recover from Deadlock\n");
    printf("11. Display System Status\n");
    printf("12. Exit\n");

    printf("============================================\n");
    printf("Enter your choice: ");
}


/* =========================================================
   MAIN
   ========================================================= */

int main(int argc, char *argv[])
{
    SystemState system;

    initialize_system(&system);
    printf("\nDEBUG TOTAL RESOURCES:\n");
for (int j = 0; j < system.resource_count; j++)
{
    printf("R%d total = %d\n", j, system.resources[j].total);
}

    gtk_init(&argc, &argv);

    create_gui(&system);

    gtk_main();

    return 0;
}
