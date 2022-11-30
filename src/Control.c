#include "Control.h"

void Control_init(struct Control *Control) {
    View_init(Control->View);
    Model_init(Control->Model);
}

void Control_connect_login(struct Control *Control) {
    g_signal_connect(Control->View->login->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(Control->View->login->button, "clicked", G_CALLBACK(Control_login_callback), (void*) Control);
}

void Control_login_callback(void *voidControl) {
    struct Control *Control = (struct Control*) voidControl;
    const char *user = gtk_entry_get_text(GTK_ENTRY(Control->View->login->cuentaEntry));
    const char *password = gtk_entry_get_text(GTK_ENTRY(Control->View->login->passwordEntry));
    int result = Model_Login(Control->Model, user, password);
    switch (result) {
        case -2:
            //Wrong usr/passwd
            break;
        case -1:
            //ERROR
            break;
        case 0:
            Control->Model->admin = 0;
            break;
        case 1:
            Control->Model->admin = 1;
        default:
            g_print("Unexpected value for Model_Login result\n");
    }

}
