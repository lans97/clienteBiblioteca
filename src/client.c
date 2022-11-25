#include "Model.h"
#include "View.h"
#include "Control.h"

static void print_hello (GtkWidget *widget, gpointer data);

int main(int argc, char* argv[]){
    gtk_init (&argc, &argv);

    struct View View;
    struct Control Control;
    struct Model Model;
    struct _TestWindow testwin;
    Control.Model = &Model;
    Control.View = &View;
    View.test = &testwin;

    View_init(&View);
    Control_connect_test(&Control);



    gtk_main ();

    return 0;
}

static void print_hello (GtkWidget *widget, gpointer data){
  g_print ("Hello World\n");
}
