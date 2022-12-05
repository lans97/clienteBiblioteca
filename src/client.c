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
unsigned char _userIsAdmin;
unsigned int _userID;

int main(int argc, char* argv[]){
    gtk_init (&argc, &argv);

    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD *fields;

    GObject *loginWin;
    GObject *button;
    GError *error = NULL;

    GtkTreeViewColumn *lsc[4];
    GtkCellRenderer *lsr[4];

    GtkTreeViewColumn *lac[4];
    GtkCellRenderer *lar[4];

    GtkTreeViewColumn *uac[6];
    GtkCellRenderer *uar[6];

    char gladeid[14];

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

    /*
    for(int i = 0; i < 4; i++){
        sprintf(gladeid, "lsc%d", i);
        lsc[i] = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, gladeid));
        sprintf(gladeid, "lsr%d", i);
        lsr[i] = GTK_CELL_RENDERER(gtk_builder_get_object(builder, gladeid));
        gtk_tree_view_column_add_attribute(lsc[i], lsr[i], "text", i);
    }
    */

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
            mysql_free_result(res);
            return;
        }
    }

    sprintf(queryBuffer, "SELECT tipo_usuario FROM py_usuarios WHERE n_cuenta = %s AND pswd = \"%s\"", user, passwd);

    if(mysql_query(&mysql, queryBuffer) != 0){
        sprintf(errorBuffer, "Error: %s", mysql_error(&mysql));
        gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        return;
    }

    if(!(res = mysql_store_result(&mysql))){
        sprintf(errorBuffer, "Error: %s", mysql_error(&mysql));
        mysql_free_result(res);
        gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        return;
    }

    if(row = mysql_fetch_row(res)){
        sscanf(row[0], "%d", &(_userIsAdmin));
        if (_userIsAdmin == 1)
            userWin = gtk_builder_get_object(builder, "adminWindow");
        else
            userWin = gtk_builder_get_object(builder, "solicWindow");

        sscanf(user, "%d", &_userID);
        gtk_widget_hide(GTK_WIDGET(loginWin));
        gtk_widget_set_visible(GTK_WIDGET(userWin), TRUE);
    }else{
        gtk_label_set_text(GTK_LABEL(msgLabel), "Usuario y/o Contraseña incorrectos");
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        mysql_free_result(res);
        return;
    }
    mysql_free_result(res);
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
    const char *cuenta, *nombre, *apaterno, *amaterno, *carrera, *mail, *passwd;
    char fnac[12];

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

    const char *s = cuenta;

    while (*s) {
        if (isdigit(*s++) == 0){
            sprintf(errorBuffer, "El número de cuenta sólo incluye números!!");
            gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
            gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
            return;
        }
    }

    sprintf(queryBuffer, "CALL p_insertar_usuario(%s, \"%s\", \"%s\", \"%s\", \"%s\", %d, \"%s\", \"%s\", \"%s\", %d)",
            cuenta, nombre, apaterno, amaterno, carrera, semestre, fnac, mail, passwd, admin);

    if(mysql_query(&mysql, queryBuffer) != 0){
        sprintf(errorBuffer, "Error: %s", mysql_error(&mysql));
        gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        return;
    }

    gtk_label_set_text(GTK_LABEL(msgLabel), "El usuario ha sido agregado con exito.");
    gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
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
    // usar gtk_tree_view_selection
    MYSQL_RES *res;
    MYSQL_ROW row;

    GObject *msgWin = gtk_builder_get_object(builder, "msgWindow");
    GObject *msgLabel = gtk_builder_get_object(builder, "labelMsg");

    GtkTreeSelection *selection;
    GtkTreeIter iter;
    GtkTreeModel *model;
    gint isbn_s;

    if(_userIsAdmin){
        selection = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "lats"));
    }
    else{
        selection = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "luts"));
    }

    if (!gtk_tree_selection_get_selected(selection, &model, &iter))
        return;

    gtk_tree_model_get(model, &iter, 0, &isbn_s, -1);

    char queryBuffer[1024], errorBuffer[1024];

    sprintf(queryBuffer, "CALL p_alta_solicitud(%i, %i)", _userID, isbn_s);

    if (mysql_query(&mysql, queryBuffer) != 0) {
        sprintf(errorBuffer, "Error: %s", mysql_error(&mysql));
        gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        return;
    }

    gtk_label_set_text(GTK_LABEL(msgLabel), "Su solicitud ha sido completada con exito.");
    gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
}

void buscaLibro_clicked_cb(GtkWidget *widget, gpointer data) {

    MYSQL_RES *res;
    MYSQL_ROW row;

    GObject *msgWin = gtk_builder_get_object(builder, "msgWindow");
    GObject *msgLabel = gtk_builder_get_object(builder, "labelMsg");

    GObject *columnCombo;
    GObject *searchEntry;

    if(_userIsAdmin){
         columnCombo = gtk_builder_get_object(builder, "librosComboBusca");
         searchEntry = gtk_builder_get_object(builder, "librosEntryBusca");
    }
    else{
         columnCombo = gtk_builder_get_object(builder, "librosComboSol");
         searchEntry = gtk_builder_get_object(builder, "librosEntrySol");
    }

    char queryBuffer[1024], errorBuffer[1024];

    const char *searchV = gtk_entry_get_text(GTK_ENTRY(searchEntry));
    int column_i = gtk_combo_box_get_active(GTK_COMBO_BOX(columnCombo)); // isbn, nombre, editorial, disponible

    switch (column_i) {
        case 0:
            const char *s = searchV;
            while (*s) {
                if (isdigit(*s++) == 0){
                    sprintf(errorBuffer, "El isbn sólo incluye números!!");
                    gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
                    gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
                    return;
                }
            }
            sprintf(queryBuffer, "SELECT isbn, libro, editorial, prestados, disponibles FROM py_libros WHERE isbn = %s", searchV);
            break;
        case 1:
            sprintf(queryBuffer, "SELECT isbn, libro, editorial, prestados, disponibles FROM py_libros WHERE libro LIKE \"%s%s%s\"", "%", searchV, "%");
            break;
        case 2:
            sprintf(queryBuffer, "SELECT isbn, libro, editorial, prestados, disponibles FROM py_libros WHERE editorial LIKE \"%s%s%s\"", "%", searchV, "%");
            break;
        case 3:
            sprintf(queryBuffer, "SELECT isbn, libro, editorial, prestados, disponibles FROM py_libros WHERE disponibles > 0");
            break;
    }

    if(mysql_query(&mysql, queryBuffer) != 0){
        sprintf(errorBuffer, "Error: %s", mysql_error(&mysql));
        gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        return;
    }

    if(!(res = mysql_store_result(&mysql))){
        sprintf(errorBuffer, "Error: %s", mysql_error(&mysql));
        mysql_free_result(res);
        gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        return;
    }

    GtkTreeStore *libros_ts = GTK_TREE_STORE(gtk_builder_get_object(builder, "librosQuery"));
    GtkTreeIter columna;

    int isbn_r, disp_r, pres_r;
    char titulo_r[51], editorial_r[31];

    gtk_tree_store_clear(libros_ts);

    while(row = mysql_fetch_row(res)){
        sscanf(row[0], "%d", &isbn_r);
        strcpy(titulo_r, row[1]);
        strcpy(editorial_r, row[2]);
        sscanf(row[3], "%d", &pres_r);
        sscanf(row[4], "%d", &disp_r);
        gtk_tree_store_append(libros_ts, &columna, NULL);
        gtk_tree_store_set(libros_ts, &columna, 0, isbn_r, -1);
        gtk_tree_store_set(libros_ts, &columna, 1, titulo_r, -1);
        gtk_tree_store_set(libros_ts, &columna, 2, editorial_r, -1);
        gtk_tree_store_set(libros_ts, &columna, 3, pres_r, -1);
        gtk_tree_store_set(libros_ts, &columna, 4, disp_r, -1);
    }

    mysql_free_result(res);

}

void buscaUser_clicked_cb(GtkWidget *widget, gpointer data){
    // SELECT n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite
    MYSQL_RES *res;
    MYSQL_ROW row;

    GObject *msgWin = gtk_builder_get_object(builder, "msgWindow");
    GObject *msgLabel = gtk_builder_get_object(builder, "labelMsg");

    GObject *columnCombo;
    GObject *searchEntry;

    /* Las fechas no necesitan un GtkCalendar porque son salidas y para ponerlo en tabla
    // sólo se necesita un string.
    // DUDA CON ESTA CREACIÓN DEL OBJETO PARA LA FECHA
    GObject *fsoli_c = gtk_builder_get_object(builder, "fsoliCalReg");
    // DUDA CON ESTA CREACIÓN DEL OBJETO PARA LA FECHA
    GObject *flim_c = gtk_builder_get_object(builder, "flimCalReg");
    */

    /*
    // DUDA!!!
    // Como la fecha se lee de la base de datos se obtiene un string.
    // int fsoli_d, fsoli_m, fsoli_a, flim_d, flim_m, flim_a;
    // Aquí se deben declarar las variables que van al TreeStore
    // (la estructura que guarda lo que se ve en pantalla.
    // El tipo debe corresponder con los especificados en TreeStore
    // (está en el archivo de glade)
    // a parte declaraste las variables abajo
    int cuenta, isbn;
    char nombre[36], apat[36], libro[51], f_sol[12], f_lim[12];
    */

    // gtk_builder_get_object(GtkBuilder *builder, char* idObjeto)
    // el idObjeto se define el el archivo de glade
    columnCombo = gtk_builder_get_object(builder, "usuariosComboBusca");
    searchEntry = gtk_builder_get_object(builder, "usuariosEntryBusca");

    char queryBuffer[1024], errorBuffer[1024];

    /* No hay calendarios en la vista de búsqueda de usuarios
    //DUDA!!!
    gtk_calendar_get_date(GTK_CALENDAR(fsoli_c), &fsoli_a, &fsoli_m, &fsoli_d);
    fsoli_m++;
    gtk_calendar_get_date(GTK_CALENDAR(flim_c), &flim_a, &flim_m, &flim_d);
    flim_m++;
    sprintf(fsoli, "%d/%d/%d", fsoli_a, fsoli_m, fsoli_d);
    sprintf(flim, "%d/%d/%d", flim_a, flim_m, flim_d);
    */

    const char *searchV = gtk_entry_get_text(GTK_ENTRY(searchEntry));
    int column_i = gtk_combo_box_get_active(GTK_COMBO_BOX(columnCombo)); // n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite

    const char *s = searchV;

    // Querry para la busqueda correcta
    // SELECT n_cuenta, nombre, a_p, isbn, libro, f_solicitud, f_limite FROM py_usuarios left join py_solicitudes using(n_cuenta) left join py_libros using(isbn) WHERE activa = TRUE
    switch (column_i) {
        case 0:
            sprintf(queryBuffer, "SELECT n_cuenta, nombre, a_p, isbn, libro, f_solicitud, f_limite FROM py_usuarios left join py_solicitudes using(n_cuenta) left join py_libros using(isbn) WHERE (activa = TRUE OR activa IS NULL) AND nombre LIKE \"%s%s%s\"", "%", searchV, "%");
        break;
        case 1:
            sprintf(queryBuffer, "SELECT n_cuenta, nombre, a_p, isbn, libro, f_solicitud, f_limite FROM py_usuarios left join py_solicitudes using(n_cuenta) left join py_libros using(isbn) WHERE (activa = TRUE OR activa IS NULL) AND a_p LIKE \"%s%s%s\"", "%", searchV, "%");
            break;
        case 2:
            while (*s) {
                if (isdigit(*s++) == 0){
                    sprintf(errorBuffer, "El n_cuenta sólo incluye números!!");
                    gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
                    gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
                    return;
                }
            }
            sprintf(queryBuffer, "SELECT n_cuenta, nombre, a_p, isbn, libro, f_solicitud, f_limite FROM py_usuarios left join py_solicitudes using(n_cuenta) left join py_libros using(isbn) WHERE (activa = TRUE OR activa IS NULL) AND n_cuenta LIKE %s", searchV);
            break;
        case 3:
            sprintf(queryBuffer, "SELECT n_cuenta, nombre, a_p, isbn, libro, f_solicitud, f_limite FROM py_usuarios left join py_solicitudes using(n_cuenta) left join py_libros using(isbn) WHERE (activa = TRUE OR activa IS NULL) AND carrera LIKE \"%s%s%s\"", "%", searchV, "%");
            break;
        case 4:
            sprintf(queryBuffer, "SELECT n_cuenta, nombre, a_p, isbn, libro, f_solicitud, f_limite FROM py_usuarios left join py_solicitudes using(n_cuenta) left join py_libros using(isbn) WHERE (activa = TRUE OR activa IS NULL) AND libro LIKE \"%s%s%s\"", "%", searchV, "%");
            break;
        case 5:
            while (*s) {
                if (isdigit(*s++) == 0){
                    sprintf(errorBuffer, "El isbn sólo incluye números!!");
                    gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
                    gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
                    return;
                }
            }
            sprintf(queryBuffer, "SELECT n_cuenta, nombre, a_p, isbn, libro, f_solicitud, f_limite FROM py_usuarios left join py_solicitudes using(n_cuenta) left join py_libros using(isbn) WHERE (activa = TRUE OR activa IS NULL) AND isbn LIKE %s", searchV);
            break;
        /* Las fechas no vienen en la especificación como parámetro de búsqueda
        //DUDA!!!
        case 5:
            sprintf(queryBuffer, "SELECT n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite, FROM py_solicitudes WHERE f_solicitud LIKE fsoli", searchV);
            break;
        case 6:
            sprintf(queryBuffer, "SELECT n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite, FROM py_solicitudes WHERE f_limite LIKE flim", searchV);
            break;
        */
    }

    if(mysql_query(&mysql, queryBuffer) != 0){
        sprintf(errorBuffer, "Error: %s", mysql_error(&mysql));
        gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        return;
    }

    if(!(res = mysql_store_result(&mysql))){
        sprintf(errorBuffer, "Error: %s", mysql_error(&mysql));
        mysql_free_result(res);
        gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
        gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
        return;
    }

    GtkTreeStore *usuarios_ts = GTK_TREE_STORE(gtk_builder_get_object(builder, "usuariosQuery"));
    GtkTreeIter columna;

    int cuenta_r, isbn_r;
    char nombre_r[36], apat_r[36], libro_r[51], f_sol_r[12], f_lim_r[12];

    gtk_tree_store_clear(usuarios_ts);

    // SELECT n_cuenta, nombre, a_p, isbn, libro, f_solicitud, f_limite FROM py_usuarios left join py_solicitudes using(n_cuenta) left join py_libros using(isbn) WHERE activa = TRUE
    while(row = mysql_fetch_row(res)){
        sscanf(row[0], "%d", &cuenta_r);
        strcpy(nombre_r, row[1]);
        strcpy(apat_r, row[2]);
        if (row[3] != NULL ) {
            sscanf(row[3], "%d", &isbn_r);
            strcpy(libro_r, row[4]);
            strcpy(f_sol_r, row[5]);
            strcpy(f_lim_r, row[6]);
        }

        gtk_tree_store_append(usuarios_ts, &columna, NULL);
        gtk_tree_store_set(usuarios_ts, &columna, 0, cuenta_r, -1);
        gtk_tree_store_set(usuarios_ts, &columna, 1, nombre_r, -1);
        gtk_tree_store_set(usuarios_ts, &columna, 2, apat_r, -1);

        if (row[3] != NULL ) {
            gtk_tree_store_set(usuarios_ts, &columna, 3, isbn_r, -1);
            gtk_tree_store_set(usuarios_ts, &columna, 4, libro_r, -1);

            gtk_tree_store_set(usuarios_ts, &columna, 5, f_sol_r, -1);
            gtk_tree_store_set(usuarios_ts, &columna, 6, f_lim_r, -1);
        }
    }
    mysql_free_result(res);
}

void updateUser_clicked_cb(GtkWidget *widget, gpointer data){
    // UPDATE py_usuarios SET %s = \'%s\'    , columna, valor nuevo
}

