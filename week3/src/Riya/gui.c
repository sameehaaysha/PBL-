#include <gtk/gtk.h>
#include "gui.h"
#include "../Sameeha/common.h"

/* Dashboard labels */
static GtkWidget *process_count_label;
static GtkWidget *resource_count_label;
static GtkWidget *available_label;
static GtkWidget *safety_label;
static GtkWidget *status_label;

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
   Button callback
   -------------------------------------------------- */

static void on_action_clicked(GtkButton *button, gpointer data)
{
    (void)button;

    const char *message = (const char *)data;
    update_status(message);
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
    const char *message,
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
        (gpointer)message
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

void create_gui(void)
{
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
            FALSE
        ),
        FALSE,
        FALSE,
        0
    );

    GtkWidget *exit_button = create_action_button(
        "12. Exit",
        "",
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