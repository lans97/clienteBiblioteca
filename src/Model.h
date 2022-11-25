#ifndef MODEL_H
#define MODEL_H
#include <mysql/mysql.h>
#include <gtk/gtk.h>

struct Model{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD *fields;

    char* server;
    char* user;
    char* passwd;
    char* db;
};

void Model_print_hello();

#endif // MODEL_H
