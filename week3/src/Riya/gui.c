#include <gtk/gtk.h>
#include "gui.h"
#include "../sameeha/common.h"
#include "../joannes/process.h"

/* Dashboard labels */
static GtkWidget *process_count_label;
static GtkWidget *resource_count_label;
static GtkWidget *available_label;
static GtkWidget *safety_label;
static GtkWidget *status_label;
static SystemState *system_state = NULL;

/* --------------------------------------------------
   Update system status
   -------------------------------------------------- */

static void update_status(const char *message)
{
    if (status_label != NULL) {
        gtk_label_set_text(GTK_LABEL(status_label), message);
    }
}
/* --------------------------------------------------
   Create Processes GUI
   -------------------------------------------------- */

static void create_processes_gui(void)
{
    GtkWidget *dialog;
    GtkWidget *content;
    GtkWidget *spin;
    GtkWidget *label;

    dialog = gtk_dialog_new_with_buttons(
        "Create Processes",
        NULL,
        GTK_DIALOG_MODAL,
        "Cancel",
        GTK_RESPONSE_CANCEL,
        "Create",
        GTK_RESPONSE_OK,
        NULL
    );

    gtk_window_set_default_size(
        GTK_WINDOW(dialog),
        400,
        180
    );

    content = gtk_dialog_get_content_area(
        GTK_DIALOG(dialog)
    );

    label = gtk_label_new(
        "Enter the number of processes (1 - 20):"
    );

    gtk_box_pack_start(
        GTK_BOX(content),
        label,
        FALSE,
        FALSE,
        15
    );

    spin = gtk_spin_button_new_with_range(
        1,
        MAX_PROCESSES,
        1
    );

    gtk_spin_button_set_value(
        GTK_SPIN_BUTTON(spin),
        3
    );

    gtk_box_pack_start(
        GTK_BOX(content),
        spin,
        FALSE,
        FALSE,
        10
    );

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK)
    {
        int count =
            gtk_spin_button_get_value_as_int(
                GTK_SPIN_BUTTON(spin)
            );

        system_state->process_count = count;

        for (int i = 0; i < count; i++)
        {
            system_state->processes[i].pid = i;

            snprintf(
                system_state->processes[i].name,
                MAX_NAME,
                "P%d",
                i
            );

            system_state->processes[i].completed = 0;
            system_state->processes[i].deadlocked = 0;

            for (int j = 0; j < MAX_RESOURCES; j++)
            {
                system_state->processes[i].allocation[j] = 0;
                system_state->processes[i].maximum[j] = 0;
                system_state->processes[i].need[j] = 0;
            }
        }

        system_state->safe_sequence_length = 0;
        system_state->deadlocked_count = 0;

        char message[100];

        snprintf(
            message,
            sizeof(message),
            "%d processes created successfully.",
            count
        );

        update_status(message);

        if (process_count_label != NULL)
        {
            char value[20];

            snprintf(
                value,
                sizeof(value),
                "%d",
                count
            );

            gtk_label_set_text(
                GTK_LABEL(process_count_label),
                value
            );
        }
    }

    gtk_widget_destroy(dialog);
}
/* --------------------------------------------------
   Create Resources GUI
   -------------------------------------------------- */
static void create_resources_gui(void)
{
    GtkWidget *dialog;
    GtkWidget *content;
    GtkWidget *spin;
    GtkWidget *label;

    GtkWidget *total_entries[MAX_RESOURCES];

    dialog = gtk_dialog_new_with_buttons(
        "Create Resources",
        NULL,
        GTK_DIALOG_MODAL,
        "Cancel",
        GTK_RESPONSE_CANCEL,
        "Create",
        GTK_RESPONSE_OK,
        NULL
    );

    content = gtk_dialog_get_content_area(
        GTK_DIALOG(dialog)
    );

    /* Number of resource types */
    label = gtk_label_new(
        "Enter number of resource types (1 - 10):"
    );

    gtk_box_pack_start(
        GTK_BOX(content),
        label,
        FALSE,
        FALSE,
        10
    );

    spin = gtk_spin_button_new_with_range(
        1,
        MAX_RESOURCES,
        1
    );

    gtk_spin_button_set_value(
        GTK_SPIN_BUTTON(spin),
        3
    );

    gtk_box_pack_start(
        GTK_BOX(content),
        spin,
        FALSE,
        FALSE,
        10
    );

    /*
     * Resource totals
     */
    label = gtk_label_new(
        "Enter total resources for R0, R1, R2..."
    );

    gtk_box_pack_start(
        GTK_BOX(content),
        label,
        FALSE,
        FALSE,
        10
    );

    for (int j = 0; j < MAX_RESOURCES; j++)
    {
        char text[50];

        sprintf(
            text,
            "Total R%d:",
            j
        );

        GtkWidget *row =
            gtk_box_new(
                GTK_ORIENTATION_HORIZONTAL,
                10
            );

        GtkWidget *resource_label =
            gtk_label_new(text);

        total_entries[j] =
            gtk_entry_new();

        gtk_entry_set_text(
            GTK_ENTRY(total_entries[j]),
            "0"
        );

        gtk_entry_set_width_chars(
            GTK_ENTRY(total_entries[j]),
            8
        );

        gtk_box_pack_start(
            GTK_BOX(row),
            resource_label,
            FALSE,
            FALSE,
            5
        );

        gtk_box_pack_start(
            GTK_BOX(row),
            total_entries[j],
            FALSE,
            FALSE,
            5
        );

        gtk_box_pack_start(
            GTK_BOX(content),
            row,
            FALSE,
            FALSE,
            5
        );
    }

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog))
        == GTK_RESPONSE_OK)
    {
        int count =
            gtk_spin_button_get_value_as_int(
                GTK_SPIN_BUTTON(spin)
            );

        system_state->resource_count = count;

        for (int j = 0; j < count; j++)
        {
            int total = atoi(
                gtk_entry_get_text(
                    GTK_ENTRY(total_entries[j])
                )
            );

            if (total < 0)
                total = 0;

            system_state->resources[j].resource_id = j;

            snprintf(
                system_state->resources[j].name,
                MAX_NAME,
                "R%d",
                j
            );

            system_state->resources[j].total = total;

            system_state->resources[j].available = total;

            system_state->available[j] = total;
        }

        if (resource_count_label != NULL)
        {
            char value[20];

            snprintf(
                value,
                sizeof(value),
                "%d",
                count
            );

            gtk_label_set_text(
                GTK_LABEL(resource_count_label),
                value
            );
        }

        update_status(
            "Resources and total capacities created successfully."
        );
    }

    gtk_widget_destroy(dialog);
}
/* --------------------------------------------------
   Enter Allocation Matrix GUI
   -------------------------------------------------- */

static void allocation_matrix_gui(void)
{
    if (system_state->process_count <= 0 ||
        system_state->resource_count <= 0)
    {
        update_status(
            "Create processes and resources first."
        );
        return;
    }

    GtkWidget *dialog;
    GtkWidget *content;
    GtkWidget *grid;

    GtkWidget *entries[MAX_PROCESSES][MAX_RESOURCES];

    dialog = gtk_dialog_new_with_buttons(
        "Enter Allocation Matrix",
        NULL,
        GTK_DIALOG_MODAL,
        "Cancel",
        GTK_RESPONSE_CANCEL,
        "Save",
        GTK_RESPONSE_OK,
        NULL
    );

    content = gtk_dialog_get_content_area(
        GTK_DIALOG(dialog)
    );

    grid = gtk_grid_new();

    gtk_grid_set_row_spacing(
        GTK_GRID(grid), 8
    );

    gtk_grid_set_column_spacing(
        GTK_GRID(grid), 8
    );

    gtk_box_pack_start(
        GTK_BOX(content),
        grid,
        TRUE,
        TRUE,
        15
    );

    /* Resource headings */

    gtk_grid_attach(
        GTK_GRID(grid),
        gtk_label_new("Process"),
        0, 0, 1, 1
    );

    for (int j = 0;
         j < system_state->resource_count;
         j++)
    {
        char name[20];

        snprintf(
            name,
            sizeof(name),
            "R%d",
            j
        );

        gtk_grid_attach(
            GTK_GRID(grid),
            gtk_label_new(name),
            j + 1,
            0,
            1,
            1
        );
    }

    /* Matrix entries */

    for (int i = 0;
         i < system_state->process_count;
         i++)
    {
        char process_name[20];

        snprintf(
            process_name,
            sizeof(process_name),
            "P%d",
            i
        );

        gtk_grid_attach(
            GTK_GRID(grid),
            gtk_label_new(process_name),
            0,
            i + 1,
            1,
            1
        );

        for (int j = 0;
             j < system_state->resource_count;
             j++)
        {
            entries[i][j] =
                gtk_entry_new();

            gtk_entry_set_text(
                GTK_ENTRY(entries[i][j]),
                "0"
            );

            gtk_entry_set_width_chars(
                GTK_ENTRY(entries[i][j]),
                6
            );

            gtk_grid_attach(
                GTK_GRID(grid),
                entries[i][j],
                j + 1,
                i + 1,
                1,
                1
            );
        }
    }

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog))
        == GTK_RESPONSE_OK)
    {
        for (int i = 0;
             i < system_state->process_count;
             i++)
        {
            for (int j = 0;
                 j < system_state->resource_count;
                 j++)
            {
                const char *text =
                    gtk_entry_get_text(
                        GTK_ENTRY(entries[i][j])
                    );

                int value = atoi(text);

                if (value < 0)
                    value = 0;

                system_state->allocation[i][j] =
                    value;

                system_state->processes[i]
                    .allocation[j] = value;
            }
        }

        calculate_available(system_state);
        calculate_need(system_state);

        update_status(
            "Allocation matrix saved successfully."
        );
    }

    gtk_widget_destroy(dialog);
}
void maximum_matrix_gui(void)
{
    GtkWidget *dialog;
    GtkWidget *grid;
    GtkWidget *entries[MAX_PROCESSES][MAX_RESOURCES];

    dialog = gtk_dialog_new_with_buttons(
        "Enter Maximum Matrix",
         NULL,
        GTK_DIALOG_MODAL,
        "Save",
        GTK_RESPONSE_OK,
        "Cancel",
        GTK_RESPONSE_CANCEL,
        NULL
    );

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 8);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 8);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 15);

    gtk_container_add(
        GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),
        grid
    );

    for (int j = 0; j < system_state->resource_count; j++)
    {
        char label[20];
        sprintf(label, "R%d", j);

        GtkWidget *header = gtk_label_new(label);
        gtk_grid_attach(GTK_GRID(grid), header, j + 1, 0, 1, 1);
    }

    for (int i = 0; i < system_state->process_count; i++)
    {
        char label[20];
        sprintf(label, "P%d", i);

        GtkWidget *process_label = gtk_label_new(label);
        gtk_grid_attach(GTK_GRID(grid), process_label, 0, i + 1, 1, 1);

        for (int j = 0; j < system_state->resource_count; j++)
        {
            entries[i][j] = gtk_entry_new();
            gtk_entry_set_text(GTK_ENTRY(entries[i][j]), "0");

            gtk_widget_set_size_request(entries[i][j], 60, -1);

            gtk_grid_attach(
                GTK_GRID(grid),
                entries[i][j],
                j + 1,
                i + 1,
                1,
                1
            );
        }
    }

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK)
    {
        for (int i = 0; i < system_state->process_count; i++)
        {
            for (int j = 0; j < system_state->resource_count; j++)
            {
                const char *text =
                    gtk_entry_get_text(GTK_ENTRY(entries[i][j]));

                int value = atoi(text);

                if (value < system_state->allocation[i][j])
                    value = system_state->allocation[i][j];

                system_state->maximum[i][j] = value;
                system_state->processes[i].maximum[j] = value;
            }
        }

        calculate_need(system_state);

        update_status("Maximum matrix saved successfully.");
    }

    gtk_widget_destroy(dialog);
}
/* ================= BUTTON 5 ================= */

void need_matrix_gui(void)
{
    GtkWidget *dialog;
    GtkWidget *grid;

    dialog = gtk_dialog_new_with_buttons(
        "Need Matrix",
        NULL,
        GTK_DIALOG_MODAL,
        "Close",
        GTK_RESPONSE_CLOSE,
        NULL
    );

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 8);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 15);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 15);

    gtk_container_add(
        GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),
        grid
    );

    for (int j = 0; j < system_state->resource_count; j++)
    {
        char text[20];
        sprintf(text, "R%d", j);
        gtk_grid_attach(
            GTK_GRID(grid),
            gtk_label_new(text),
            j + 1, 0, 1, 1
        );
    }

    for (int i = 0; i < system_state->process_count; i++)
    {
        char text[20];
        sprintf(text, "P%d", i);

        gtk_grid_attach(
            GTK_GRID(grid),
            gtk_label_new(text),
            0, i + 1, 1, 1
        );

        for (int j = 0; j < system_state->resource_count; j++)
        {
            sprintf(text, "%d", system_state->need[i][j]);

            gtk_grid_attach(
                GTK_GRID(grid),
                gtk_label_new(text),
                j + 1, i + 1, 1, 1
            );
        }
    }

    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


/* ================= BUTTON 6 ================= */

void rag_gui(void)
{
    GtkWidget *dialog;
    GtkWidget *label;
    char text[4096];

    strcpy(text, "RESOURCE ALLOCATION GRAPH\n\n");

    for (int i = 0; i < system_state->process_count; i++)
    {
        for (int j = 0; j < system_state->resource_count; j++)
        {
            if (system_state->allocation[i][j] > 0)
            {
                char line[100];

                sprintf(
                    line,
                    "R%d -> P%d   (Allocated: %d)\n",
                    j,
                    i,
                    system_state->allocation[i][j]
                );

                strcat(text, line);
            }
        }
    }

    strcat(text, "\n");

    for (int i = 0; i < system_state->process_count; i++)
    {
        for (int j = 0; j < system_state->resource_count; j++)
        {
            if (system_state->need[i][j] > 0)
            {
                char line[100];

                sprintf(
                    line,
                    "P%d -> R%d   (Need: %d)\n",
                    i,
                    j,
                    system_state->need[i][j]
                );

                strcat(text, line);
            }
        }
    }

    dialog = gtk_dialog_new_with_buttons(
        "Resource Allocation Graph",
        NULL,
        GTK_DIALOG_MODAL,
        "Close",
        GTK_RESPONSE_CLOSE,
        NULL
    );

    label = gtk_label_new(text);
    gtk_label_set_xalign(GTK_LABEL(label), 0.0);

    gtk_container_add(
        GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),
        label
    );

    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


/* ================= BUTTON 7 ================= */

void request_resources_gui(void)
{
    GtkWidget *dialog;
    GtkWidget *content;
    GtkWidget *grid;
    GtkWidget *pid_entry;
    GtkWidget *entries[MAX_RESOURCES];

    int request[MAX_RESOURCES] = {0};

    if (system_state == NULL ||
        system_state->process_count <= 0 ||
        system_state->resource_count <= 0)
    {
        update_status("Create processes and resources first.");
        return;
    }

    dialog = gtk_dialog_new_with_buttons(
        "Request Resources",
        NULL,
        GTK_DIALOG_MODAL,
        "Cancel",
        GTK_RESPONSE_CANCEL,
        "Request",
        GTK_RESPONSE_OK,
        NULL
    );

    content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    grid = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 15);

    gtk_container_add(
        GTK_CONTAINER(content),
        grid
    );

    /* Process ID */
    gtk_grid_attach(
        GTK_GRID(grid),
        gtk_label_new("Process ID:"),
        0, 0, 1, 1
    );

    pid_entry = gtk_entry_new();

    gtk_entry_set_text(
        GTK_ENTRY(pid_entry),
        "1"
    );

    gtk_grid_attach(
        GTK_GRID(grid),
        pid_entry,
        1, 0, 1, 1
    );

    /* Resource requests */
    for (int j = 0;
         j < system_state->resource_count;
         j++)
    {
        char label[30];

        sprintf(label, "Request R%d:", j);

        gtk_grid_attach(
            GTK_GRID(grid),
            gtk_label_new(label),
            0, j + 1, 1, 1
        );

        entries[j] = gtk_entry_new();

        gtk_entry_set_text(
            GTK_ENTRY(entries[j]),
            "0"
        );

        gtk_grid_attach(
            GTK_GRID(grid),
            entries[j],
            1, j + 1, 1, 1
        );
    }

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK)
    {
        int pid = atoi(
            gtk_entry_get_text(GTK_ENTRY(pid_entry))
        );

        if (pid < 0 ||
            pid >= system_state->process_count)
        {
            update_status("Invalid Process ID.");
            gtk_widget_destroy(dialog);
            return;
        }

        for (int j = 0;
             j < system_state->resource_count;
             j++)
        {
            request[j] = atoi(
                gtk_entry_get_text(
                    GTK_ENTRY(entries[j])
                )
            );

            if (request[j] < 0)
                request[j] = 0;
        }

        /* Recalculate current state */
        calculate_available(system_state);
        calculate_need(system_state);

        /*
         * TEST-SAFE REQUEST:
         * P1 -> 1 1 1
         */
        if (pid == 1 &&
            system_state->resource_count >= 3 &&
            request[0] == 1 &&
            request[1] == 1 &&
            request[2] == 1)
        {
            if (request_resources(
                    system_state,
                    pid,
                    request))
            {
                calculate_available(system_state);
                calculate_need(system_state);

                update_status(
                    "Resource request GRANTED safely."
                );
            }
            else
            {
                update_status(
                    "Request could not be granted."
                );
            }
        }
        else
        {
            /*
             * Normal request handling
             */
            if (request_resources(
                    system_state,
                    pid,
                    request))
            {
                calculate_available(system_state);
                calculate_need(system_state);

                update_status(
                    "Resource request GRANTED safely."
                );
            }
            else
            {
                update_status(
                    "Request denied."
                );
            }
        }
    }

    gtk_widget_destroy(dialog);
}

/* ================= BUTTON 8 ================= */

void banker_gui(void)
{
    GtkWidget *dialog;
    char text[2048];

    /* Make sure the current matrices are up to date */
    calculate_available(system_state);
    calculate_need(system_state);
    

    int result = bankers_algorithm(system_state);

    if (result)
    {
        strcpy(text, "SYSTEM STATE: SAFE\n\nSafe Sequence:\n");

        for (int i = 0;
             i < system_state->safe_sequence_length;
             i++)
        {
            char part[50];

            sprintf(
                part,
                "P%d",
                system_state->safe_sequence[i]
            );

            strcat(text, part);

            if (i < system_state->safe_sequence_length - 1)
                strcat(text, " -> ");
        }

        update_status("Banker's Algorithm: SAFE");
    }
    else
    {
        strcpy(
            text,
            "SYSTEM STATE: UNSAFE\n\nNo safe sequence exists."
        );

        update_status("Banker's Algorithm: UNSAFE");
    }

    dialog = gtk_dialog_new_with_buttons(
        "Banker's Algorithm",
        NULL,
        GTK_DIALOG_MODAL,
        "Close",
        GTK_RESPONSE_CLOSE,
        NULL
    );

    GtkWidget *label = gtk_label_new(text);

    gtk_container_add(
        GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),
        label
    );

    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


/* ================= BUTTON 9 ================= */

void detect_deadlock_gui(void)
{
    GtkWidget *dialog;
    char text[2048];

    int count = detect_deadlock(system_state);

    if (count == 0)
    {
        strcpy(text, "NO DEADLOCK DETECTED.");

        update_status("Deadlock detection: No deadlock.");
    }
    else
    {
        sprintf(
            text,
            "DEADLOCK DETECTED\n\nNumber of deadlocked processes: %d\n\n",
            count
        );

        strcat(text, "Deadlocked Processes:\n");

        for (int i = 0; i < count; i++)
        {
            char part[50];

            sprintf(
                part,
                "P%d\n",
                system_state->deadlocked[i]
            );

            strcat(text, part);
        }

        update_status("Deadlock detected.");
    }

    dialog = gtk_dialog_new_with_buttons(
        "Deadlock Detection",
        NULL,
        GTK_DIALOG_MODAL,
        "Close",
        GTK_RESPONSE_CLOSE,
        NULL
    );

    GtkWidget *label = gtk_label_new(text);

    gtk_container_add(
        GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),
        label
    );

    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


/* ================= BUTTON 10 ================= */

void recovery_gui(void)
{
    recover_from_deadlock(system_state);

    update_status(
        "Deadlock recovery completed."
    );

    GtkWidget *dialog = gtk_message_dialog_new(
        NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Deadlock recovery operation completed."
    );

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


/* ================= BUTTON 11 ================= */

void system_status_gui(void)
{
    GtkWidget *dialog;
    GtkWidget *label;

    char text[4096];

    sprintf(
        text,
        "SYSTEM STATUS\n\n"
        "Processes: %d\n"
        "Resources: %d\n\n"
        "Available Resources:\n",
        system_state->process_count,
        system_state->resource_count
    );

    for (int j = 0; j < system_state->resource_count; j++)
    {
        char line[100];

        sprintf(
            line,
            "R%d = %d\n",
            j,
            system_state->available[j]
        );

        strcat(text, line);
    }

    strcat(text, "\nProcess Status:\n");

    for (int i = 0; i < system_state->process_count; i++)
    {
        char line[100];

        sprintf(
            line,
            "P%d: %s\n",
            i,
            system_state->processes[i].deadlocked
                ? "DEADLOCKED"
                : (system_state->processes[i].completed
                    ? "COMPLETED"
                    : "ACTIVE")
        );

        strcat(text, line);
    }

    dialog = gtk_dialog_new_with_buttons(
        "System Status",
        NULL,
        GTK_DIALOG_MODAL,
        "Close",
        GTK_RESPONSE_CLOSE,
        NULL
    );

    label = gtk_label_new(text);

    gtk_label_set_xalign(
        GTK_LABEL(label),
        0.0
    );

    gtk_container_add(
        GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),
        label
    );

    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
/* --------------------------------------------------
   Button callback
   -------------------------------------------------- */

static void on_action_clicked(GtkButton *button, gpointer data)
{
    (void)button;

    int action = GPOINTER_TO_INT(data);

    if (system_state == NULL)
    {
        update_status("System is not initialized.");
        return;
    }

    switch (action)
{
    case 1:
        create_processes_gui();
        break;
    case 2:
        create_resources_gui();
        break;
    case 3:
        allocation_matrix_gui();
        break;
    case 4:
       maximum_matrix_gui();
       break;

   case 5:
    need_matrix_gui();
    break;

case 6:
    rag_gui();
    break;

case 7:
    request_resources_gui();
    break;

case 8:
{
    calculate_available(system_state);
    calculate_need(system_state);

    banker_gui();

    break;
}

case 9:
    detect_deadlock_gui();
    break;

case 10:
    recovery_gui();
    break;

case 11:
    system_status_gui();
    break;

case 12:
    gtk_main_quit();
    break;

default:
    update_status("Button selected. Action not connected yet.");
    break;
}
}

/* --------------------------------------------------
   Exit application
   -------------------------------------------------- */

static void on_exit_clicked(GtkButton *button, gpointer data)
{
    (void)button;
    (void)data;

    gtk_main_quit();
}

/* --------------------------------------------------
   Apply CSS styling
   -------------------------------------------------- */

static void apply_css(void)
{
    const gchar *css =
        /* Main application background */
        "window {"
        "   background-color: #f1f3f5;"
        "}"

        /* Header background */
        ".header {"
        "   background-color: #ffffff;"
        "   padding: 22px;"
        "}"

        /* Main title */
        ".title {"
        "   color: #173b70;"
        "   font-size: 24px;"
        "   font-weight: bold;"
        "}"

        /* Subtitle */
        ".subtitle {"
        "   color: #52647c;"
        "   font-size: 12px;"
        "}"

        /* Dashboard and content cards */
        ".card {"
        "   background-color: #ffffff;"
        "   border-radius: 10px;"
        "   padding: 16px;"
        "}"

        /* Section headings */
        ".section-title {"
        "   color: #173b70;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "}"

        /* Dashboard numbers */
        ".counter {"
        "   color: #173b70;"
        "   font-size: 25px;"
        "   font-weight: bold;"
        "}"

        /* Dashboard labels */
        ".counter-label {"
        "   color: #52647c;"
        "   font-size: 12px;"
        "}"

        /* Normal buttons */
        "button.action-button {"
        "   background-image: none;"
        "   background-color: #e9ecef;"
        "   color: #173b70;"
        "   border: 1px solid #cbd2da;"
        "   border-radius: 7px;"
        "   padding: 9px;"
        "   font-weight: bold;"
        "}"

        /* Normal button text */
        "button.action-button label {"
        "   color: #173b70;"
        "}"

        /* Normal button hover */
        "button.action-button:hover {"
        "   background-image: none;"
        "   background-color: #dce2e8;"
        "}"

        /* Primary buttons */
        "button.primary-button {"
        "   background-image: none;"
        "   background-color: #e9ecef;"
        "   color: #173b70;"
        "   border: 1px solid #cbd2da;"
        "   border-radius: 7px;"
        "   padding: 9px;"
        "   font-weight: bold;"
        "}"

        /* Primary button text */
        "button.primary-button label {"
        "   color: #173b70;"
        "}"

        /* Primary button hover */
        "button.primary-button:hover {"
        "   background-image: none;"
        "   background-color: #dce2e8;"
        "}"

        /* System status panel */
        ".status-card {"
        "   background-color: #e5f4e9;"
        "   border-radius: 8px;"
        "   padding: 12px;"
        "}"

        /* Status heading */
        ".status-title {"
        "   color: #176c38;"
        "   font-weight: bold;"
        "}"

        /* Status message */
        ".status-message {"
        "   color: #315b40;"
        "}"

        /* Footer */
        ".footer {"
        "   color: #52647c;"
        "   font-size: 11px;"
        "}";

    GtkCssProvider *provider = gtk_css_provider_new();

    GError *error = NULL;

    if (!gtk_css_provider_load_from_data(
            provider,
            css,
            -1,
            &error))
    {
        g_printerr(
            "CSS error: %s\n",
            error->message
        );

        g_clear_error(&error);
        g_object_unref(provider);
        return;
    }

    GdkScreen *screen = gdk_screen_get_default();

    if (screen != NULL)
    {
        gtk_style_context_add_provider_for_screen(
            screen,
            GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
        );
    }

    g_object_unref(provider);
}
/* --------------------------------------------------
   Create a styled card
   -------------------------------------------------- */

static GtkWidget *create_card(void)
{
    GtkWidget *card =
        gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    gtk_style_context_add_class(
        gtk_widget_get_style_context(card),
        "card"
    );

    return card;
}

/* --------------------------------------------------
   Create a section heading
   -------------------------------------------------- */

static GtkWidget *create_heading(const char *text)
{
    GtkWidget *label = gtk_label_new(text);

    gtk_label_set_xalign(GTK_LABEL(label), 0.0);

    gtk_style_context_add_class(
        gtk_widget_get_style_context(label),
        "section-title"
    );

    return label;
}

/* --------------------------------------------------
   Create an action button
   -------------------------------------------------- */

static GtkWidget *create_action_button(
    const char *text,
    const char *message __attribute__((unused)),
    int action,
    gboolean primary
)
{
    GtkWidget *button = gtk_button_new_with_label(text);

    gtk_widget_set_hexpand(button, TRUE);
    gtk_widget_set_halign(button, GTK_ALIGN_FILL);

    GtkStyleContext *context =
        gtk_widget_get_style_context(button);

    if (primary) {
        gtk_style_context_add_class(
            context,
            "primary-button"
        );
    } else {
        gtk_style_context_add_class(
            context,
            "action-button"
        );
    }

    g_signal_connect(
    button,
    "clicked",
    G_CALLBACK(on_action_clicked),
    GINT_TO_POINTER(action)
);

    return button;
}

/* --------------------------------------------------
   Create a dashboard counter
   -------------------------------------------------- */

static GtkWidget *create_counter_card(
    const char *heading,
    const char *value,
    GtkWidget **value_label
)
{
    GtkWidget *card = create_card();

    GtkWidget *heading_label = gtk_label_new(heading);

    gtk_label_set_xalign(
        GTK_LABEL(heading_label),
        0.0
    );

    gtk_style_context_add_class(
        gtk_widget_get_style_context(heading_label),
        "counter-label"
    );

    *value_label = gtk_label_new(value);

    gtk_label_set_xalign(
        GTK_LABEL(*value_label),
        0.0
    );

    gtk_style_context_add_class(
        gtk_widget_get_style_context(*value_label),
        "counter"
    );

    gtk_box_pack_start(
        GTK_BOX(card),
        heading_label,
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(card),
        *value_label,
        FALSE,
        FALSE,
        0
    );

    return card;
}

/* --------------------------------------------------
   Create the main GUI
   -------------------------------------------------- */

void create_gui(SystemState *system)
{
    system_state = system;
    apply_css();

    /* Main window */

    GtkWidget *window =
        gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(
        GTK_WINDOW(window),
        "Deadlock Simulation System"
    );

    gtk_window_set_default_size(
        GTK_WINDOW(window),
        1050,
        780
    );

    gtk_window_set_position(
        GTK_WINDOW(window),
        GTK_WIN_POS_CENTER
    );

    g_signal_connect(
        window,
        "destroy",
        G_CALLBACK(gtk_main_quit),
        NULL
    );

    /* Main layout */

    GtkWidget *main_box =
        gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_container_add(
        GTK_CONTAINER(window),
        main_box
    );

    /* Header */

    GtkWidget *header =
        gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);

    gtk_widget_set_margin_start(header, 24);
    gtk_widget_set_margin_end(header, 24);
    gtk_widget_set_margin_top(header, 20);
    gtk_widget_set_margin_bottom(header, 20);

    gtk_style_context_add_class(
        gtk_widget_get_style_context(header),
        "header"
    );

    GtkWidget *title =
        gtk_label_new("DEADLOCK SIMULATION SYSTEM");

    gtk_label_set_xalign(GTK_LABEL(title), 0.0);

    gtk_style_context_add_class(
        gtk_widget_get_style_context(title),
        "title"
    );

    GtkWidget *subtitle = gtk_label_new(
        "Operating Systems Project | "
        "Resource Management and Deadlock Analysis"
    );

    gtk_label_set_xalign(GTK_LABEL(subtitle), 0.0);

    gtk_style_context_add_class(
        gtk_widget_get_style_context(subtitle),
        "subtitle"
    );

    gtk_box_pack_start(
        GTK_BOX(header), title, FALSE, FALSE, 0
    );

    gtk_box_pack_start(
        GTK_BOX(header), subtitle, FALSE, FALSE, 0
    );

    gtk_box_pack_start(
        GTK_BOX(main_box), header, FALSE, FALSE, 0
    );

    /* Scrollable content for smaller screens */

    GtkWidget *scrolled =
        gtk_scrolled_window_new(NULL, NULL);

    gtk_scrolled_window_set_policy(
        GTK_SCROLLED_WINDOW(scrolled),
        GTK_POLICY_NEVER,
        GTK_POLICY_AUTOMATIC
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        scrolled,
        TRUE,
        TRUE,
        0
    );

    GtkWidget *content =
        gtk_box_new(GTK_ORIENTATION_VERTICAL, 16);

    gtk_widget_set_margin_start(content, 24);
    gtk_widget_set_margin_end(content, 24);
    gtk_widget_set_margin_top(content, 18);
    gtk_widget_set_margin_bottom(content, 18);

    gtk_container_add(
        GTK_CONTAINER(scrolled),
        content
    );

    /* Dashboard */

    gtk_box_pack_start(
        GTK_BOX(content),
        create_heading("System Dashboard"),
        FALSE,
        FALSE,
        0
    );

    GtkWidget *counter_row =
        gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);

    GtkWidget *process_card = create_counter_card(
        "TOTAL PROCESSES",
        "0",
        &process_count_label
    );

    GtkWidget *resource_card = create_counter_card(
        "RESOURCE TYPES",
        "0",
        &resource_count_label
    );

    GtkWidget *available_card = create_counter_card(
        "AVAILABLE RESOURCES",
        "0",
        &available_label
    );

    GtkWidget *safety_card = create_counter_card(
        "SYSTEM SAFETY",
        "Unknown",
        &safety_label
    );

    gtk_box_pack_start(
        GTK_BOX(counter_row),
        process_card,
        TRUE,
        TRUE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(counter_row),
        resource_card,
        TRUE,
        TRUE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(counter_row),
        available_card,
        TRUE,
        TRUE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(counter_row),
        safety_card,
        TRUE,
        TRUE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(content),
        counter_row,
        FALSE,
        FALSE,
        0
    );

    /* Two-column action layout */

    GtkWidget *action_row =
        gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 16);

    gtk_box_pack_start(
        GTK_BOX(content),
        action_row,
        FALSE,
        FALSE,
        0
    );

    /* ------------------------------------------
       Resource Management panel
       ------------------------------------------ */

    GtkWidget *resource_panel = create_card();

    gtk_box_pack_start(
        GTK_BOX(resource_panel),
        create_heading("Resource Management"),
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(resource_panel),
        create_action_button(
            "1. Create Processes",
            "Create Processes selected.",
            1,
            TRUE
        ),
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(resource_panel),
        create_action_button(
            "2. Create Resources",
            "Create Resources selected.",
            2,
            FALSE
        ),
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(resource_panel),
        create_action_button(
            "3. Enter Allocation Matrix",
            "Enter Allocation Matrix selected.",
            3,
            FALSE
        ),
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(resource_panel),
        create_action_button(
            "4. Enter Maximum Matrix",
            "Enter Maximum Matrix selected.",
            4,
            FALSE
        ),
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(resource_panel),
        create_action_button(
            "5. Display Need Matrix",
            "Display Need Matrix selected.",
            5,
            FALSE
        ),
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(resource_panel),
        create_action_button(
            "7. Request Resources",
            "Request Resources selected.",
            7,
            FALSE
        ),
        FALSE,
        FALSE,
        0
    );

    /* ------------------------------------------
       Deadlock Analysis panel
       ------------------------------------------ */

    GtkWidget *analysis_panel = create_card();

    gtk_box_pack_start(
        GTK_BOX(analysis_panel),
        create_heading("Deadlock Analysis"),
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(analysis_panel),
        create_action_button(
            "6. Display Resource Allocation Graph",
            "Resource Allocation Graph selected.",
            6,
            FALSE
        ),
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(analysis_panel),
        create_action_button(
            "8. Run Banker's Algorithm",
            "Banker's Algorithm selected.",
            8,
            TRUE
        ),
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(analysis_panel),
        create_action_button(
            "9. Detect Deadlock",
            "Deadlock Detection selected.",
            9,
            FALSE
        ),
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(analysis_panel),
        create_action_button(
            "10. Recover from Deadlock",
            "Deadlock Recovery selected.",
            10,
            FALSE
        ),
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(analysis_panel),
        create_action_button(
            "11. Display System Status",
            "Display System Status selected.",
            11,
            FALSE
        ),
        FALSE,
        FALSE,
        0
    );

    GtkWidget *exit_button = create_action_button(
        "12. Exit",
        "",
        12,
        FALSE
    );

    g_signal_handlers_disconnect_by_func(
        exit_button,
        G_CALLBACK(on_action_clicked),
        (gpointer)""
    );

    g_signal_connect(
        exit_button,
        "clicked",
        G_CALLBACK(on_exit_clicked),
        NULL
    );

    gtk_box_pack_start(
        GTK_BOX(analysis_panel),
        exit_button,
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(action_row),
        resource_panel,
        TRUE,
        TRUE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(action_row),
        analysis_panel,
        TRUE,
        TRUE,
        0
    );

    /* System status */

    GtkWidget *status_card =
        gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);

    gtk_style_context_add_class(
        gtk_widget_get_style_context(status_card),
        "status-card"
    );

    GtkWidget *status_heading =
        gtk_label_new("SYSTEM STATUS");

    gtk_label_set_xalign(
        GTK_LABEL(status_heading),
        0.0
    );

    gtk_style_context_add_class(
        gtk_widget_get_style_context(status_heading),
        "status-title"
    );

    status_label = gtk_label_new(
        "Ready. Select an operation to begin."
    );

    gtk_label_set_xalign(
        GTK_LABEL(status_label),
        0.0
    );

    gtk_label_set_line_wrap(
        GTK_LABEL(status_label),
        TRUE
    );

    gtk_style_context_add_class(
        gtk_widget_get_style_context(status_label),
        "status-message"
    );

    gtk_box_pack_start(
        GTK_BOX(status_card),
        status_heading,
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(status_card),
        status_label,
        FALSE,
        FALSE,
        0
    );

    gtk_box_pack_start(
        GTK_BOX(content),
        status_card,
        FALSE,
        FALSE,
        0
    );

    /* Footer */

    GtkWidget *footer = gtk_label_new(
        "Deadlock Simulation System | Operating Systems Project"
    );

    gtk_style_context_add_class(
        gtk_widget_get_style_context(footer),
        "footer"
    );

    gtk_box_pack_start(
        GTK_BOX(content),
        footer,
        FALSE,
        FALSE,
        0
    );

    /* Show the interface */

    gtk_widget_show_all(window);
}

/* --------------------------------------------------
   Resource Allocation Graph placeholder
   -------------------------------------------------- */

void draw_resource_allocation_graph(void)
{
    update_status(
        "Resource Allocation Graph selected. "
        "Graph rendering is not connected yet."
    );
}
