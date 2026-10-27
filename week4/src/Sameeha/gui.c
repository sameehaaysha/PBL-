#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>

#include "gui.h"
#include "common.h"

/*
 * Function implemented in main.c.
 * Returns 1 on success and 0 on failure.
 */
int run_simulation_to_text(
    const int pages[],
    int page_count,
    int frame_count,
    AlgorithmType selected_algorithm,
    char *output,
    size_t output_size
);

/* GUI widgets */
static GtkWidget *references_entry;
static GtkWidget *frames_entry;
static GtkWidget *algorithm_combo;
static GtkWidget *results_view;
static GtkWidget *status_label;

/* --------------------------------------------------
   Display a message in the GUI results area
   -------------------------------------------------- */

static void show_message(const char *message)
{
    GtkTextBuffer *buffer;

    buffer = gtk_text_view_get_buffer(
        GTK_TEXT_VIEW(results_view)
    );

    gtk_text_buffer_set_text(
        buffer,
        message != NULL ? message : "",
        -1
    );
}

/* --------------------------------------------------
   Parse page references
   Accepts spaces and commas as separators.
   Returns 1 on success and 0 on failure.
   -------------------------------------------------- */

static int parse_references(
    const char *input,
    int pages[],
    int *count
)
{
    const char *p;
    char *endptr;
    long value;

    if (input == NULL || pages == NULL || count == NULL)
        return 0;

    *count = 0;
    p = input;

    while (*p != '\0')
    {
        /* Skip separators */
        while (*p == ' ' ||
               *p == '\t' ||
               *p == '\n' ||
               *p == '\r' ||
               *p == ',')
        {
            p++;
        }

        if (*p == '\0')
            break;

        /* Page references must be non-negative integers */
        if (*p < '0' || *p > '9')
            return 0;

        errno = 0;
        value = strtol(p, &endptr, 10);

        if (errno == ERANGE ||
            endptr == p ||
            value < 0 ||
            value > INT_MAX)
        {
            return 0;
        }

        if (*count >= MAX_REFERENCES)
            return 0;

        pages[*count] = (int)value;
        (*count)++;

        p = endptr;

        /* Reject invalid separators or characters */
        if (*p != '\0' &&
            *p != ' ' &&
            *p != '\t' &&
            *p != '\n' &&
            *p != '\r' &&
            *p != ',')
        {
            return 0;
        }
    }

    return (*count > 0);
}

/* --------------------------------------------------
   Parse and validate the number of frames
   -------------------------------------------------- */

static int parse_frame_count(
    const char *input,
    int *frame_count
)
{
    char *endptr;
    long value;

    if (input == NULL ||
        frame_count == NULL ||
        *input == '\0')
    {
        return 0;
    }

    errno = 0;
    value = strtol(input, &endptr, 10);

    if (errno == ERANGE ||
        endptr == input ||
        *endptr != '\0' ||
        value < 1 ||
        value > MAX_FRAMES)
    {
        return 0;
    }

    *frame_count = (int)value;

    return 1;
}

/* --------------------------------------------------
   Run Simulation button
   -------------------------------------------------- */

static void on_run_clicked(
    GtkButton *button,
    gpointer data
)
{
    int pages[MAX_REFERENCES];
    int page_count = 0;
    int frame_count = 0;

    const char *references;
    const char *frame_text;

    gchar *algorithm = NULL;

    /*
     * Large buffer for page-by-page results.
     * If the output is too large, main.c reports
     * an output-buffer error.
     */
    char output[1000000];

    AlgorithmType selected_algorithm;

    (void)button;
    (void)data;

    /* Read page references */
    references = gtk_entry_get_text(
        GTK_ENTRY(references_entry)
    );

    /* Read frame count */
    frame_text = gtk_entry_get_text(
        GTK_ENTRY(frames_entry)
    );

    /* Validate page references */
    if (!parse_references(
            references,
            pages,
            &page_count))
    {
        gtk_label_set_text(
            GTK_LABEL(status_label),
            "Invalid page references."
        );

        show_message(
            "INVALID PAGE REFERENCES\n\n"
            "Enter non-negative page numbers separated "
            "by spaces or commas.\n\n"
            "Example:\n"
            "7 0 1 2 0 3 0 4 2 3"
        );

        return;
    }

    /* Validate frame count */
    if (!parse_frame_count(
            frame_text,
            &frame_count))
    {
        char error_message[256];

        snprintf(
            error_message,
            sizeof(error_message),
            "Frame count must be between 1 and %d.",
            MAX_FRAMES
        );

        gtk_label_set_text(
            GTK_LABEL(status_label),
            error_message
        );

        show_message(
            "INVALID FRAME COUNT\n\n"
            "Enter a positive whole number of frames."
        );

        return;
    }

    /* Get selected algorithm */
    algorithm = gtk_combo_box_text_get_active_text(
        GTK_COMBO_BOX_TEXT(algorithm_combo)
    );

    if (algorithm == NULL)
    {
        gtk_label_set_text(
            GTK_LABEL(status_label),
            "Please select an algorithm."
        );

        show_message(
            "Please select an algorithm and try again."
        );

        return;
    }

    /* Convert selection to the algorithm enum */
    if (strcmp(algorithm, "FIFO") == 0)
    {
        selected_algorithm = ALGORITHM_FIFO;
    }
    else if (strcmp(algorithm, "LRU") == 0)
    {
        selected_algorithm = ALGORITHM_LRU;
    }
    else if (strcmp(algorithm, "Optimal") == 0)
    {
        selected_algorithm = ALGORITHM_OPTIMAL;
    }
    else if (strcmp(algorithm, "Compare All") == 0)
    {
        selected_algorithm = ALGORITHM_ALL;
    }
    else
    {
        g_free(algorithm);

        gtk_label_set_text(
            GTK_LABEL(status_label),
            "Invalid algorithm selection."
        );

        show_message(
            "The selected algorithm is not supported."
        );

        return;
    }

    /* Update status before running */
    gtk_label_set_text(
        GTK_LABEL(status_label),
        "Running simulation..."
    );

    /*
     * Call main.c to run the selected algorithm
     * and format the results into the output buffer.
     */
    output[0] = '\0';

    int success = run_simulation_to_text(
        pages,
        page_count,
        frame_count,
        selected_algorithm,
        output,
        sizeof(output)
    );

    if (!success)
    {
        gtk_label_set_text(
            GTK_LABEL(status_label),
            "Simulation failed."
        );

        show_message(
            output[0] != '\0'
                ? output
                : "Simulation failed. Please check your input."
        );

        g_free(algorithm);
        return;
    }

    /* Display actual simulation results in GTK */
    gtk_label_set_text(
        GTK_LABEL(status_label),
        "Simulation completed successfully."
    );

    show_message(output);

    g_free(algorithm);
}

/* --------------------------------------------------
   Clear Inputs button
   -------------------------------------------------- */

static void on_clear_clicked(
    GtkButton *button,
    gpointer data
)
{
    (void)button;
    (void)data;

    gtk_entry_set_text(
        GTK_ENTRY(references_entry),
        ""
    );

    gtk_entry_set_text(
        GTK_ENTRY(frames_entry),
        ""
    );

    gtk_combo_box_set_active(
        GTK_COMBO_BOX(algorithm_combo),
        0
    );

    gtk_label_set_text(
        GTK_LABEL(status_label),
        "Inputs cleared."
    );

    show_message(
        "Welcome!\n\n"
        "Enter new page references and frame count "
        "to start another simulation."
    );
}

/* --------------------------------------------------
   Build and launch the GTK3 interface
   -------------------------------------------------- */

void start_gui(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *title;
    GtkWidget *subtitle;
    GtkWidget *input_grid;

    GtkWidget *references_label;
    GtkWidget *frames_label;
    GtkWidget *algorithm_label;

    GtkWidget *run_button;
    GtkWidget *clear_button;
    GtkWidget *button_box;

    GtkWidget *results_label;
    GtkWidget *results_scroll;

    /* Initialize GTK */
    gtk_init(&argc, &argv);

    /* Main window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(
        GTK_WINDOW(window),
        "Page Replacement Simulator"
    );

    gtk_window_set_default_size(
        GTK_WINDOW(window),
        850,
        650
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

    /* Main vertical layout */
    main_box = gtk_box_new(
        GTK_ORIENTATION_VERTICAL,
        12
    );

    gtk_container_set_border_width(
        GTK_CONTAINER(main_box),
        20
    );

    gtk_container_add(
        GTK_CONTAINER(window),
        main_box
    );

    /* Title */
    title = gtk_label_new(NULL);

    gtk_label_set_markup(
        GTK_LABEL(title),
        "<span size='xx-large' weight='bold'>"
        "PAGE REPLACEMENT SIMULATOR"
        "</span>"
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        title,
        FALSE,
        FALSE,
        4
    );

    /* Subtitle */
    subtitle = gtk_label_new(
        "Simulate FIFO, LRU and Optimal page replacement"
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        subtitle,
        FALSE,
        FALSE,
        2
    );

    /* Input grid */
    input_grid = gtk_grid_new();

    gtk_grid_set_row_spacing(
        GTK_GRID(input_grid),
        14
    );

    gtk_grid_set_column_spacing(
        GTK_GRID(input_grid),
        16
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        input_grid,
        FALSE,
        FALSE,
        8
    );

    /* Page-reference label */
    references_label = gtk_label_new(
        "Page-reference string:"
    );

    gtk_widget_set_halign(
        references_label,
        GTK_ALIGN_START
    );

    gtk_grid_attach(
        GTK_GRID(input_grid),
        references_label,
        0, 0, 1, 1
    );

    /* Page-reference input */
    references_entry = gtk_entry_new();

    gtk_entry_set_placeholder_text(
        GTK_ENTRY(references_entry),
        "Example: 7 0 1 2 0 3 0 4 2 3"
    );

    gtk_entry_set_max_length(
        GTK_ENTRY(references_entry),
        10000
    );

    gtk_widget_set_hexpand(
        references_entry,
        TRUE
    );

    gtk_grid_attach(
        GTK_GRID(input_grid),
        references_entry,
        1, 0, 1, 1
    );

    /* Frame-count label */
    frames_label = gtk_label_new(
        "Number of page frames:"
    );

    gtk_widget_set_halign(
        frames_label,
        GTK_ALIGN_START
    );

    gtk_grid_attach(
        GTK_GRID(input_grid),
        frames_label,
        0, 1, 1, 1
    );

    /* Frame-count input */
    frames_entry = gtk_entry_new();

    gtk_entry_set_placeholder_text(
        GTK_ENTRY(frames_entry),
        "Example: 3"
    );

    gtk_entry_set_input_purpose(
        GTK_ENTRY(frames_entry),
        GTK_INPUT_PURPOSE_DIGITS
    );

    gtk_grid_attach(
        GTK_GRID(input_grid),
        frames_entry,
        1, 1, 1, 1
    );

    /* Algorithm label */
    algorithm_label = gtk_label_new(
        "Select algorithm:"
    );

    gtk_widget_set_halign(
        algorithm_label,
        GTK_ALIGN_START
    );

    gtk_grid_attach(
        GTK_GRID(input_grid),
        algorithm_label,
        0, 2, 1, 1
    );

    /* Algorithm dropdown */
    algorithm_combo = gtk_combo_box_text_new();

    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(algorithm_combo),
        "FIFO"
    );

    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(algorithm_combo),
        "LRU"
    );

    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(algorithm_combo),
        "Optimal"
    );

    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(algorithm_combo),
        "Compare All"
    );

    gtk_combo_box_set_active(
        GTK_COMBO_BOX(algorithm_combo),
        0
    );

    gtk_grid_attach(
        GTK_GRID(input_grid),
        algorithm_combo,
        1, 2, 1, 1
    );

    /* Button layout */
    button_box = gtk_box_new(
        GTK_ORIENTATION_HORIZONTAL,
        10
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        button_box,
        FALSE,
        FALSE,
        4
    );

    /* Run Simulation button */
    run_button = gtk_button_new_with_label(
        "Run Simulation"
    );

    gtk_widget_set_size_request(
        run_button,
        160,
        42
    );

    gtk_box_pack_start(
        GTK_BOX(button_box),
        run_button,
        FALSE,
        FALSE,
        0
    );

    g_signal_connect(
        run_button,
        "clicked",
        G_CALLBACK(on_run_clicked),
        NULL
    );

    /* Clear Inputs button */
    clear_button = gtk_button_new_with_label(
        "Clear Inputs"
    );

    gtk_widget_set_size_request(
        clear_button,
        120,
        42
    );

    gtk_box_pack_start(
        GTK_BOX(button_box),
        clear_button,
        FALSE,
        FALSE,
        0
    );

    g_signal_connect(
        clear_button,
        "clicked",
        G_CALLBACK(on_clear_clicked),
        NULL
    );

    /* Status label */
    status_label = gtk_label_new(
        "Enter the reference string and frame count."
    );

    gtk_widget_set_halign(
        status_label,
        GTK_ALIGN_START
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        status_label,
        FALSE,
        FALSE,
        4
    );

    /* Results heading */
    results_label = gtk_label_new(
        "Simulation Output"
    );

    gtk_widget_set_halign(
        results_label,
        GTK_ALIGN_START
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        results_label,
        FALSE,
        FALSE,
        2
    );

    /* Scrollable results area */
    results_scroll = gtk_scrolled_window_new(
        NULL,
        NULL
    );

    gtk_widget_set_vexpand(
        results_scroll,
        TRUE
    );

    gtk_scrolled_window_set_policy(
        GTK_SCROLLED_WINDOW(results_scroll),
        GTK_POLICY_AUTOMATIC,
        GTK_POLICY_AUTOMATIC
    );

    results_view = gtk_text_view_new();

    gtk_text_view_set_editable(
        GTK_TEXT_VIEW(results_view),
        FALSE
    );

    gtk_text_view_set_cursor_visible(
        GTK_TEXT_VIEW(results_view),
        FALSE
    );

    gtk_text_view_set_monospace(
        GTK_TEXT_VIEW(results_view),
        TRUE
    );

    gtk_text_view_set_wrap_mode(
        GTK_TEXT_VIEW(results_view),
        GTK_WRAP_WORD_CHAR
    );

    gtk_container_add(
        GTK_CONTAINER(results_scroll),
        results_view
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        results_scroll,
        TRUE,
        TRUE,
        4
    );

    /* Initial welcome message */
    show_message(
        "Welcome to the Page Replacement Simulator!\n\n"
        "1. Enter page references separated by spaces or commas.\n"
        "2. Enter the number of frames.\n"
        "3. Select FIFO, LRU, Optimal or Compare All.\n"
        "4. Click Run Simulation to view the results.\n\n"
        "Your simulation results will appear here."
    );

    /* Display the window */
    gtk_widget_show_all(window);

    /* Start GTK event loop */
    gtk_main();
}
int main(int argc, char *argv[])
{
    start_gui(argc, argv);
    return 0;
}