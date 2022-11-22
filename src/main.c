#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void activate (GtkApplication* app, gpointer user_data);

int main (int argc, char* argv[]){

    // GTK
    GtkApplication *app;
    int status;

    app = gtk_application_new("edu.ibero.basesproyecto", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

static void activate (GtkApplication* app, gpointer user_data){
    GtkWidget *window;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_widget_show_all(window);
}

// int main (int argc, char **argv)
// {
//     unsigned int i = 0;
//     char     buffer[1024];
//     unsigned int num_fields;
//
//     char *server = "localhost";
//     char *user = "ic21lsm";
//     char *passwd = "200490";
//     char *db;
//
//     // Variables para lograr la comunicación con la BD y que vienen incluidas en la librería mysql.h
//     MYSQL mysql;  /*Estructura que representa el manejador de la conexión a la base de datos.*/
//     MYSQL_RES *res; /*Estructura que representa el resultado de un query que regresa renglones (resul set)*/
//     MYSQL_ROW row; /*Este tipo de datos es el utilizado para obtener un solo renglón como resultado de un query.
// 	                 Los renglones pueden ser obtenidos llamando a la función mysql_fetch_row().*/
//     MYSQL_FIELD *fields; /*Esta estructura contiene información acerca del campo obtenido, tal y como su nombre,
// 					tipo y tamaño. Los campos de una tabla se pueden obtener mandando llamar a la función
// 					mysql_fetch_field(). Los valores de los campos no son parte de esta estructura sino que se
// 					encuentran en la estructura MYSQL_ROW.*/
//
//     /* TODO: comboboxes for querries -> output to new window */
//
//     db = strdup(argv[1]);
//
//     mysql_init(&mysql); // Prepara la conexión al servidor de bases de datos
//
//     // Se conecta al servidor de base de datos y verifica que no haya error
//     if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
//       fprintf(stderr, "Error al conectarse a la BD: Error: %s\n",mysql_error(&mysql));
//       return(0);
//     }
//
//     // Se conecta a la base de datos deseada
//     if( mysql_select_db(&mysql,argv[1]) ){
//         fprintf(stderr,"No existe la base de datos seleccionada: Error: %s\n",mysql_error(&mysql));
//         exit(1);
//     }
//
//     // Ejecuta el query
// 	strcpy(buffer,argv[2]);
//     if( mysql_query(&mysql,buffer) ){
//         fprintf(stderr,"Error al procesar el query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
//         exit(1);
//     }
//
//     // Obtiene el query
//     if( !(res = mysql_store_result(&mysql)) ){
//         fprintf(stderr,"Error al obtener el resultado Error: %s\n",mysql_error(&mysql));
//         exit(1);
//     }
//
//
//     // Despliega el resultado del query
//     while( (row = mysql_fetch_row(res)) ){
//         i = 0;
//
//         for( i=0 ; i < mysql_num_fields(res); i++ ){
// 	  if(row[i] != NULL){
//             printf("%s ",row[i]);
// 	  }
// 	  else{
// 	    printf(" \n");
// 	  }
//         }
//         fputc('\n',stdout);
//     }
//
//     mysql_free_result(res);
//
//     // cierra la conexion al servidor
//     mysql_close(&mysql);
//
//     return 0;
// }
//
