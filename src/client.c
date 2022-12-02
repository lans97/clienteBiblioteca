#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>


static void print_hello (GtkWidget *widget, gpointer data);
void checkUsrPasswd(GtkWidget *widget, gpointer data);

GtkBuilder *builder;
MYSQL mysql;

int main(int argc, char* argv[]){
    gtk_init (&argc, &argv);

    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD *fields;

    GObject *loginWin;
    GObject *button;
    GError *error = NULL;

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

    loginWin = gtk_builder_get_object(builder, "loginWindow");
    g_signal_connect (loginWin, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_set_visible(GTK_WIDGET(loginWin), TRUE);
    button = gtk_builder_get_object(builder, "loginButtonLogin");

    g_signal_connect (button, "clicked", G_CALLBACK(checkUsrPasswd), NULL);

    gtk_main ();

    mysql_close(&mysql);

    return 0;
}

static void print_hello (GtkWidget *widget, gpointer data){
    g_print ("Hello World\n");
}

void checkUsrPasswd(GtkWidget *widget, gpointer data){
    MYSQL_RES *res;
    MYSQL_ROW row;

    char user[10];
    char passwd[21];
    int admin;

    GObject *userEntry = gtk_builder_get_object(builder, "usrEntryLogin");
    GObject *passwdEntry = gtk_builder_get_object(builder, "passwdEntryLogin");
    GObject *loginWin = gtk_builder_get_object(builder, "loginWindow");
    GObject *userWin;

    strcpy(user, gtk_entry_get_text(GTK_ENTRY(userEntry)));
    strcpy(passwd, gtk_entry_get_text(GTK_ENTRY(passwdEntry)));
    g_print("Usr: %s\nPasswd: %s\n", user, passwd);

    char qBuffer[1024];

    sprintf(qBuffer, "SELECT isadmin FROM py_usuarios WHERE cuenta = %s AND password = %s", user, passwd);

    if(mysql_query(&mysql, qBuffer)){
        fprintf(stderr, "Error: %s", mysql_error(&mysql));
        exit(EXIT_FAILURE);
    }

    if(!(res = mysql_store_result(&mysql))){
        fprintf(stderr, "Error: %s", mysql_error(&mysql));
        exit(EXIT_FAILURE);
    }

    if(row = mysql_fetch_row(res)){
        sscanf(row[0], "%d", &(admin));
        g_print("%s\n", (admin == 1) ? "admin" : "solic");
        if (admin == 1)
            userWin = gtk_builder_get_object(builder, "adminWindow");
        else
            userWin = gtk_builder_get_object(builder, "solicWindow");
        gtk_widget_hide(GTK_WIDGET(loginWin));
        gtk_widget_set_visible(GTK_WIDGET(userWin), TRUE);
    }else{
        return;
    }
}
