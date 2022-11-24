#ifndef APPLICATION_H_
#define APPLICATION_H_
#include "Model.h"
#include "View.h"

struct Application{
    struct Model *Model;
    struct View *View;
    char* server;
    char* user;
    char* passwd;
};

void Application_login(struct Application *app);
void Application_run(struct Application *app);

#endif // APPLICATION_H_
