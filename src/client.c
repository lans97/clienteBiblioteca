#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define DB_SERVER "localhost"
#define DB_USER "ic21lsm"
#define DB_PASSWD "200490"
#define DB_NAME "ic21lsm"

// for debug
static void print_hello (GtkWidget *widget, gpointer data);

//button functions
void devButton_clicked_cb(GtkWidget *widget, gpointer data);
void presButton_clicked_cb(GtkWidget *widget, gpointer data);
void buscaLibro_clicked_cb(GtkWidget *widget, gpointer data);
void buscaUser_clicked_cb(GtkWidget *widget, gpointer data);
void updateUser_clicked_cb(GtkWidget *widget, gpointer data);
void regUser_clicked_cb(GtkWidget *widget, gpointer data);
void msgButton_clicked_cb(GtkWidget *widget, gpointer data); // done
void loginButtonLogin_clicked_cb(GtkWidget *widget, gpointer data); // done


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

    if(!mysql_real_connect(&mysql, DB_SERVER, DB_USER, DB_PASSWD, DB_NAME, 0, NULL, 0)) {
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

void loginButton_clicked_cb(GtkWidget *widget, gpointer data){
    MYSQL_RES *res;
    MYSQL_ROW row;

    char user[10];
    char passwd[21];
    int admin;

    GObject *userEntry = gtk_builder_get_object(builder, "usrEntryLogin");
    GObject *passwdEntry = gtk_builder_get_object(builder, "passwdEntryLogin");
    GObject *loginWin = gtk_builder_get_object(builder, "loginWindow");
    GObject *msgWin = gtk_builder_get_object(builder, "msgWindow");
    GObject *msgLabel = gtk_builder_get_object(builder, "labelMsg");
    GObject *userWin;

    char queryBuffer[1024];
    char errorBuffer[1024];

    strcpy(user, gtk_entry_get_text(GTK_ENTRY(userEntry)));
    strcpy(passwd, gtk_entry_get_text(GTK_ENTRY(passwdEntry)));

    char *s = user;

    while (*s) {
        if (isdigit(*s++) == 0){
            sprintf(errorBuffer, "El número de cuenta sólo incluye números!!");
            gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
            gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
            return;
        }
    }

    sprintf(queryBuffer, "SELECT tipo_usuario FROM py_usuarios WHERE n_cuenta = %s AND pswd = \"%s\"", user, passwd);

    if(mysql_query(&mysql, queryBuffer)){
        sprintf(errorBuffer, "Error: %s", mysql_error(&mysql));
        gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        return;
    }

    if(!(res = mysql_store_result(&mysql))){
        sprintf(errorBuffer, "Error: %s", mysql_error(&mysql));
        gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        return;
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

void regUser_clicked_cb(GtkWidget *widget, gpointer data){

    MYSQL_RES *res;
    MYSQL_ROW row;

    GObject *msgWin = gtk_builder_get_object(builder, "msgWindow");
    GObject *msgLabel = gtk_builder_get_object(builder, "labelMsg");

    GObject *cuenta_e = gtk_builder_get_object(builder, "cuentaEntryReg");
    GObject *nombre_e = gtk_builder_get_object(builder, "nombreEntryReg");
    GObject *apaterno_e = gtk_builder_get_object(builder, "apatEntryReg");
    GObject *amaterno_e = gtk_builder_get_object(builder, "amatEntryReg");
    GObject *carrera_e = gtk_builder_get_object(builder, "carreraEntryReg");
    GObject *semestre_c = gtk_builder_get_object(builder, "semestreComboReg");
    GObject *fnac_c = gtk_builder_get_object(builder, "fnacCalReg");
    GObject *mail_e = gtk_builder_get_object(builder, "emailEntryReg");
    GObject *passwd_e = gtk_builder_get_object(builder, "passwordEntryReg");
    GObject *admin_b = gtk_builder_get_object(builder, "adminCheckReg");

    int semestre, admin, fnac_d, fnac_m, fnac_a;
    const char *cuenta, *nombre, *apaterno, *amaterno, *carrera, *mail, *passwd, fnac[12];

    char queryBuffer[1024], errorBuffer[1024];

    cuenta = gtk_entry_get_text(GTK_ENTRY(cuenta_e));
    nombre = gtk_entry_get_text(GTK_ENTRY(nombre_e));
    apaterno = gtk_entry_get_text(GTK_ENTRY(apaterno_e));
    amaterno = gtk_entry_get_text(GTK_ENTRY(amaterno_e));
    carrera = gtk_entry_get_text(GTK_ENTRY(carrera_e));
    semestre = gtk_combo_box_get_active(GTK_COMBO_BOX(semestre_c)) + 1;
    gtk_calendar_get_date(GTK_CALENDAR(fnac_c), &fnac_a, &fnac_m, &fnac_d);
    fnac_m++;
    mail = gtk_entry_get_text(GTK_ENTRY(mail_e));
    passwd = gtk_entry_get_text(GTK_ENTRY(passwd_e));
    admin = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(admin_b));

    sprintf(fnac, "%d/%d/%d", fnac_a, fnac_m, fnac_d);

    // TODO: Insertar campos leídos en la base de datos

    sprintf(queryBuffer, "CALL p_insertar_usuario(%s, \"%s\", \"%s\", \"%s\", \"%s\", %d, \"%s\", \"%s\", \"%s\", %d)",
            cuenta, nombre, apaterno, amaterno, carrera, semestre, fnac, mail, passwd, admin);

    if(mysql_query(&mysql, queryBuffer)){
        sprintf(errorBuffer, "Error: %s", mysql_error(&mysql));
        gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        return;
    }

    if(!(res = mysql_store_result(&mysql))){
        sprintf(errorBuffer, "Error: %s", mysql_error(&mysql));
        gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        return;
    }

    while(row = mysql_fetch_row(res));
}

void msgButton_clicked_cb(GtkWidget *widget, gpointer data){
    GObject *win = gtk_builder_get_object(builder, "msgWindow");
    gtk_widget_hide(GTK_WIDGET(win));
}

void devButton_clicked_cb(GtkWidget *widget, gpointer data){
    // CALL p_resuelve_solicitud(usuario activo)
}

void presButton_clicked_cb(GtkWidget *widget, gpointer data){
    // CALL p_alta_solicitud(usuario activo, libro seleccionado)
}

void buscaLibro_clicked_cb(GtkWidget *widget, gpointer data) {
    // SELECT isbn libro editorial disponibles prestados from py_libros;
    // pasar a liststore nombre en gui.glade
}

void buscaUser_clicked_cb(GtkWidget *widget, gpointer data){
    // SELECT n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite
}

void updateUser_clicked_cb(GtkWidget *widget, gpointer data){
    // UPDATE py_usuarios SET %s = \'%s\'    , columna, valor nuevo
}

