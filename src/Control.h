#ifndef CONTROL_H_
#define CONTROL_H_

#include "View.h"
#include "Model.h"

struct Control{
    struct View *View;
    struct Model *Model;
};

void Control_init(struct Control *Control);
void Control_connect_login(struct Control *Control);
void Control_login_callback(void *voidControl);

#endif // CONTROL_H_
