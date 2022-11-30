#include "Model.h"

int Model_init(struct Model *Model){
    mysql_init(&(Model->mysql));

    if(!mysql_real_connect(&Model->mysql, "localhost", "ic21lsm", "200490", "ic21lsm", 0, NULL, 0)){
        strcpy(Model->error, "No se pudo conectar al servidor de MySQL");
        return -1;
    }

    if(mysql_select_db(&(Model->mysql), "ic21lsm")){
        strcpy(Model->error, "No se pudo seleccionar la base de datos ic21lsm");
        return -1;
    }

    return 0;
}

void Model_delete(struct Model *Model){
    mysql_close(&(Model->mysql));
}

int Model_Login(struct Model *Model, const char* user, const char* password){
    char q_getUser[100];
    int adminBool;
    sprintf(q_getUser, "SELECT admin FROM py_users WHERE cuenta = %s AND password = %s", user, password);
    if (mysql_query(&(Model->mysql), q_getUser)){
        sprintf(Model->error, "Error: %s", mysql_error(&(Model->mysql)));
        return -1;
    }
    if (!(Model->res = mysql_store_result(&(Model->mysql)))){
        sprintf(Model->error, "Error: %s", mysql_error(&(Model->mysql)));
        return -1;
    }


    if (Model->row = mysql_fetch_row(Model->res))
        sscanf(Model->row[0], "%d", &adminBool);
    else
        return -2;

    mysql_free_result(Model->res);

    return adminBool;
}

void Model_print_hello(){
    g_print("Hello world!\n");
}
