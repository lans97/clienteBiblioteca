#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


static void print_hello (GtkWidget *widget, gpointer data);
void loginButtonLogin_clicked_cb(GtkWidget *widget, gpointer data);
void regButtonReg_clicked_cb(GtkWidget *widget, gpointer data);
void buttonMsj_clicked_cb(GtkWidget *widget, gpointer data);

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

    int getpk = 1;

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

    gtk_builder_connect_signals(builder, NULL);

    gtk_main ();

    mysql_close(&mysql);

    return 0;
}

static void print_hello (GtkWidget *widget, gpointer data){
    g_print ("Hello World\n");
}

void loginButtonLogin_clicked_cb(GtkWidget *widget, gpointer data){
    MYSQL_RES *res;
    MYSQL_ROW row;

    char user[10];
    char passwd[21];
    int admin;

    GObject *userEntry = gtk_builder_get_object(builder, "usrEntryLogin");
    GObject *passwdEntry = gtk_builder_get_object(builder, "passwdEntryLogin");
    GObject *loginWin = gtk_builder_get_object(builder, "loginWindow");
    GObject *msgWin = gtk_builder_get_object(builder, "msgWindow");
    GObject *userWin;
    GObject *msgLabel = gtk_builder_get_object(builder, "labelMsg");

    char tempBuffer[1024];

    strcpy(user, gtk_entry_get_text(GTK_ENTRY(userEntry)));
    strcpy(passwd, gtk_entry_get_text(GTK_ENTRY(passwdEntry)));

    char *s = user;

    while (*s) {
        if (isdigit(*s++) == 0){
            strcpy(tempBuffer, "El número de cuenta sólo incluye números!!");
            gtk_label_set_text(GTK_LABEL(msgLabel), tempBuffer);
            gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
            return;
        }
    }

    sprintf(tempBuffer, "SELECT isadmin FROM py_usuarios WHERE cuenta = %s AND password = \"%s\"", user, passwd);

    if(mysql_query(&mysql, tempBuffer)){
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
        gtk_label_set_text(GTK_LABEL(msgLabel), "Usuario y/o Contraseña incorrectos");
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        return;
    }
}

void regButtonReg_clicked_cb(GtkWidget *widget, gpointer data){

}

void buttonMsj_clicked_cb(GtkWidget *widget, gpointer data){
    GObject *win = gtk_builder_get_object(builder, "msgWindow");
    gtk_widget_hide(GTK_WIDGET(win));
}
