#ifndef VIEW_H_
#define VIEW_H_

#include <gtk/gtk.h>

struct _LoginWindow {
    GObject *window;
    GObject *cuentaEntry;
    GObject *passwordEntry;
    GObject *button;
};

struct _AdminWindow {
    GObject *window;
    GObject *stack;
    GObject *search;
};

struct _TestWindow {
    GObject *window;
    GObject *b1;
    GObject *b2;
    GObject *b3;
};

struct View{
    GtkBuilder *builder;
    struct _TestWindow *test;
    GError *error;
};

struct LoginData{
    char user[21];
    char password[21];
};

void View_init(struct View *View);
void View_del(struct View *View);

#endif // VIEW_H_
