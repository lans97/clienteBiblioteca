#include "View.h"

void View_init(struct View *View) {
    View->error = NULL;
    View->builder = gtk_builder_new();
    if (gtk_builder_add_from_file (View->builder, "resources/uiPrueba.glade", &(View->error)) == 0) {
        g_printerr("Error loading file: %s\n", View->error->message);
        g_clear_error(&(View->error));
        exit(EXIT_FAILURE);
    }

    View->login->window = gtk_builder_get_object (View->builder, "loginWindow");
    View->login->cuentaEntry = gtk_builder_get_object (View->builder, "usrEntryLogin");
    View->login->passwordEntry = gtk_builder_get_object (View->builder, "passwdEntryLogin");
    View->login->button = gtk_builder_get_object (View->builder, "loginButtonLogin");
}

void View_del(struct View *View) {
    g_print("Por ahora nada");
}
