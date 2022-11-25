#include "Control.h"

void Control_connect_test(struct Control *Control) {
    g_signal_connect(Control->View->test->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(Control->View->test->b1, "clicked", G_CALLBACK(Model_print_hello), NULL);
    g_signal_connect(Control->View->test->b2, "clicked", G_CALLBACK(Model_print_hello), NULL);
    g_signal_connect(Control->View->test->b3, "clicked", G_CALLBACK(gtk_main_quit), NULL);
}
