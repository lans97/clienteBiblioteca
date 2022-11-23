#ifndef VIEW_H_
#define VIEW_H_

#include <gtk/gtk.h>

struct View{
    GtkBuilder *builder;
    GObject *winLogin;
    GObject *winMain;
};

struct LoginData{
    char user[21];
    char password[21];
};

void View_init(struct View *View);
struct LoginData View_login(struct View *View);
void View_del(struct View *View);

#endif // VIEW_H_
