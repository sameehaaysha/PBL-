#include "gui.h"

/* Status label displayed in the main window */
static GtkWidget *status_label;

/* Display a message when a button is clicked */
static void show_message(GtkWidget *widget, gpointer data)
{
    (void)widget;

    const char *message = (const char *)data;

    gtk_label_set_text(GTK_LABEL(status_label), message);
}

/* Create and arrange the GUI components */
GtkWidget *create_gui(void)
{
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *title;
    GtkWidget *banker_button;
    GtkWidget *detect_button;
    GtkWidget *rag_button;
    GtkWidget *reset_button;

    /* Create the main window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(
        GTK_WINDOW(window),
        "Interactive Deadlock Simulation System"
    );

    gtk_window_set_default_size(GTK_WINDOW(window), 750, 500);

    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    /* Create a vertical box to arrange components */
    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);

    gtk_container_add(GTK_CONTAINER(window), main_box);

    /* Add the project title */
    title = gtk_label_new(
        "INTERACTIVE DEADLOCK SIMULATION SYSTEM"
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        title,
        FALSE,
        FALSE,
        10
    );

    /* Create the status label */
    status_label = gtk_label_new(
        "Welcome! Select an operation below."
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        status_label,
        FALSE,
        FALSE,
        10
    );

    /* Create the Banker's Algorithm button */
    banker_button = gtk_button_new_with_label(
        "Run Banker's Algorithm"
    );

    g_signal_connect(
        banker_button,
        "clicked",
        G_CALLBACK(show_message),
        "Banker's Algorithm: Waiting for algorithm integration."
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        banker_button,
        FALSE,
        FALSE,
        5
    );

    /* Create the deadlock detection button */
    detect_button = gtk_button_new_with_label(
        "Detect Deadlock"
    );

    g_signal_connect(
        detect_button,
        "clicked",
        G_CALLBACK(show_message),
        "Deadlock Detection: Waiting for algorithm integration."
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        detect_button,
        FALSE,
        FALSE,
        5
    );

    /* Create the Resource Allocation Graph button */
    rag_button = gtk_button_new_with_label(
        "Display Resource Allocation Graph"
    );

    g_signal_connect(
        rag_button,
        "clicked",
        G_CALLBACK(show_message),
        "RAG: Graph drawing will be added in the next stage."
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        rag_button,
        FALSE,
        FALSE,
        5
    );

    /* Create the reset button */
    reset_button = gtk_button_new_with_label(
        "Reset Status"
    );

    g_signal_connect(
        reset_button,
        "clicked",
        G_CALLBACK(show_message),
        "Simulation status has been reset."
    );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        reset_button,
        FALSE,
        FALSE,
        5
    );

    /* Show all components */
    gtk_widget_show_all(window);

    return window;
}