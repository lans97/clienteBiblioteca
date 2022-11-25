#include "Model.h"
#include "View.h"
#include "Control.h"

static void print_hello (GtkWidget *widget, gpointer data);

int main(int argc, char* argv[]){
    gtk_init (&argc, &argv);

    struct View View;
    struct _TestWindow testwin;
    View.test = &testwin;

    View_init(&View);

    g_signal_connect (View.test->window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (View.test->b1, "clicked", G_CALLBACK (print_hello), NULL);
    g_signal_connect (View.test->b2, "clicked", G_CALLBACK (print_hello), NULL);
    g_signal_connect (View.test->b3, "clicked", G_CALLBACK (gtk_main_quit), NULL);

    gtk_main ();

    return 0;
}

static void print_hello (GtkWidget *widget, gpointer data){
  g_print ("Hello World\n");
}
