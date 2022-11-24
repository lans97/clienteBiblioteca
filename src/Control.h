#ifndef CONTROL_H_
#define CONTROL_H_
#include "Model.h"
#include "View.h"

struct Control{
    struct Model *Model;
    struct View *View;
    char* server;
    char* user;
    char* passwd;
};

static void print_hello(GtkWidget *widget, gpointer data);
void Control_login(struct Control *Control);
void Control_run(struct Control *Control);

#endif // CONTROL_H_
