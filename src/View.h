#ifndef VIEW_H_
#define VIEW_H_

#include <gtk/gtk.h>

struct View{
    GtkBuilder *builder;
    GObject *window;
    GObject *button;
    GError *error;
};

struct LoginData{
    char user[21];
    char password[21];
};

void View_init(struct View *View);
void View_del(struct View *View);

#endif // VIEW_H_
