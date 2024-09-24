#include "database.h"

#include <stdio.h>
#include "secrets.h"// easier than reading from env

void database_open(Database *db) {
    mysql_init(&db->mysql);
    if(!mysql_real_connect(&db->mysql, DB_SERVER, DB_USER, DB_PASSWD, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "Error al conectarse: %s\n", mysql_error(&db->mysql));
        exit(EXIT_FAILURE);
    }
}

void database_close(Database *db) {
    mysql_close(&db->mysql);
}
