#ifndef MODEL_H
#define MODEL_H
#include <mysql/mysql.h>

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

void Model_init(struct Model *Model);
void Model_login(struct Model *Model);
void Model_querry(struct Model *Model);
void Model_del(struct Model *Model);

#endif // MODEL_H
