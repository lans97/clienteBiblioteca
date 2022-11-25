#ifndef CONTROL_H_
#define CONTROL_H_

#include "View.h"
#include "Model.h"

struct Control{
    struct View *View;
    struct Model *Model;
};

void Control_connect_test(struct Control *Control);

#endif // CONTROL_H_
