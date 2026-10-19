#include "../gui.h"

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = create_gui();

    g_signal_connect(
        window,
        "destroy",
        G_CALLBACK(gtk_main_quit),
        NULL
    );

    gtk_main();

    return 0;
}
