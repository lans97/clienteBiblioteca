#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>

struct database_auth {
    int id;
};

typedef struct {
    MYSQL mysql;
} Database;

void database_open(Database *db);
void database_close(Database *db);

#endif
