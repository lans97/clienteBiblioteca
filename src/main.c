#include "database/database.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    Database db;
    database_open(&db);

    printf("Hello, world!");

    database_close(&db);
    return 0;
}
