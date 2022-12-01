#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

struct usrpasswd{
    MYSQL *mysql;
    GObject *userEntry;
    GObject *passwdEntry;
    char user[20];
    char passwd[20];
    int admin;
};

static void print_hello (GtkWidget *widget, gpointer data);
void checkUsrPasswd(GtkWidget *widget, gpointer data);

int main(int argc, char* argv[]){
    gtk_init (&argc, &argv);

    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD *fields;

    GtkBuilder *builder;
    GObject *window;
    GObject *userEntry;
    GObject *passwdEntry;
    GObject *button;
    GError *error = NULL;

    struct usrpasswd loginData;

    mysql_init(&mysql);

    if(!mysql_real_connect(&mysql, "localhost", "ic21lsm", "200490", "ic21lsm", 0, NULL, 0)) {
        fprintf(stderr, "Error al conectarse: %s\n", mysql_error(&mysql));
        exit(EXIT_FAILURE);
    }

    builder = gtk_builder_new ();
    if (gtk_builder_add_from_file (builder, "resources/gui.glade", &error) == 0) {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return 1;
    }

    window = gtk_builder_get_object(builder, "loginWindow");
    g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
    userEntry = gtk_builder_get_object(builder, "usrEntryLogin");
    passwdEntry = gtk_builder_get_object(builder, "passwdEntryLogin");
    button = gtk_builder_get_object(builder, "loginButtonLogin");

    loginData.userEntry = userEntry;
    loginData.passwdEntry = passwdEntry;
    loginData.mysql = &mysql;

    g_signal_connect (button, "clicked", G_CALLBACK(checkUsrPasswd), &loginData);

    gtk_main ();

    mysql_close(&mysql);

    return 0;
}

static void print_hello (GtkWidget *widget, gpointer data){
    g_print ("Hello World\n");
}

void checkUsrPasswd(GtkWidget *widget, gpointer data){
    struct usrpasswd *loginData = (struct usrpasswd*) data;

    MYSQL_RES *res;
    MYSQL_ROW row;

    strcpy(loginData->user, gtk_entry_get_text(GTK_ENTRY(loginData->userEntry)));
    strcpy(loginData->passwd, gtk_entry_get_text(GTK_ENTRY(loginData->passwdEntry)));
    g_print("Usr: %s\nPasswd: %s\n", loginData->user, loginData->passwd);

    char qBuffer[1024];

    sprintf(qBuffer, "SELECT admin FROM py_usuarios WHERE cuenta = %s AND password = %s", loginData->user, loginData->passwd);

    if(mysql_query(loginData->mysql, qBuffer)){
        fprintf(stderr, "Error: %s", mysql_error(loginData->mysql));
        exit(EXIT_FAILURE);
    }

    if(!(res = mysql_store_result(loginData->mysql))){
        fprintf(stderr, "Error: %s", mysql_error(loginData->mysql));
        exit(EXIT_FAILURE);
    }

    if(row = mysql_fetch_row(res)){
        sscanf(row[0], "%d", loginData->admin);
        g_print("%s\n", (loginData->admin == 1) ? "admin" : "solic");
    }else{
        return;
    }
}
