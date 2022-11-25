#include "View.h"

void View_init(struct View *View) {
    View->error = NULL;
    View->builder = gtk_builder_new();
    if (gtk_builder_add_from_file (View->builder, "resources/builder.ui", &(View->error)) == 0) {
        g_printerr("Error loading file: %s\n", View->error->message);
        g_clear_error(&(View->error));
        exit(EXIT_FAILURE);
    }

    View->test->window = gtk_builder_get_object (View->builder, "window");
    View->test->b1 = gtk_builder_get_object (View->builder, "button1");
    View->test->b2 = gtk_builder_get_object (View->builder, "button2");
    View->test->b3 = gtk_builder_get_object (View->builder, "quit");

}

void View_del(struct View *View) {
    g_print("Por ahora nada");
}
