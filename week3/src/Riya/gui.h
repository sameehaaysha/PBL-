#ifndef GUI_H
#define GUI_H
#include "../sameeha/common.h"

#include <gtk/gtk.h>

/* Initialize and display the graphical interface */
void create_gui(SystemState *system);



/* Display the Resource Allocation Graph */
void draw_resource_allocation_graph(void);

#endif
