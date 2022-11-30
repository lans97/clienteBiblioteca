#ifndef MODEL_H
#define MODEL_H
#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include <string.h>

struct Model{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD *fields;

    char error[100];
    unsigned char admin;
};


int Model_init(struct Model *Model);
void Model_delete(struct Model *Model);
int Model_Login(struct Model *Model, const char *user, const char *password);
void Model_print_hello();

#endif // MODEL_H
