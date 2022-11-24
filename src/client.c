#include "Model.h"
#include "View.h"
#include "Control.h"

static void print_hello (GtkWidget *widget, gpointer data);

int main(int argc, char* argv[]){
    gtk_init (&argc, &argv);

    struct View View;
    View.error = NULL;

    /* Construct a GtkBuilder instance and load our UI description */
    View.builder = gtk_builder_new ();
    if (gtk_builder_add_from_file (View.builder, "resources/builder.ui", &(View.error)) == 0)
        {
        g_printerr ("Error loading file: %s\n", (View.error)->message);
        g_clear_error (&(View.error));
        return 1;
        }

    /* Connect signal handlers to the constructed widgets. */
    View.window = gtk_builder_get_object (View.builder, "window");
    g_signal_connect (View.window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    View.button = gtk_builder_get_object (View.builder, "button1");
    g_signal_connect (View.button, "clicked", G_CALLBACK (print_hello), NULL);

    View.button = gtk_builder_get_object (View.builder, "button2");
    g_signal_connect (View.button, "clicked", G_CALLBACK (print_hello), NULL);

    View.button = gtk_builder_get_object (View.builder, "quit");
    g_signal_connect (View.button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

    gtk_main ();

    return 0;
}

static void print_hello (GtkWidget *widget, gpointer data){
  g_print ("Hello World\n");
}
