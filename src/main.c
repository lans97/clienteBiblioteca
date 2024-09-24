#include <stdio.h>
#include "database/database.h"

int main(int argc, char* argv[]) {
    Database db;
    database_open(&db);

    database_close(&db);
    return 0;
}
