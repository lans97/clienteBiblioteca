void buscaUser_clicked_cb(GtkWidget *widget, gpointer data){
    // SELECT n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite
    MYSQL_RES *res;
    MYSQL_ROW row;

    GObject *msgWin = gtk_builder_get_object(builder, "msgWindow");
    GObject *msgLabel = gtk_builder_get_object(builder, "labelMsg");

    GObject *columnCombo;
    GObject *searchEntry;
    // DUDA CON ESTA CREACIÓN DEL OBJETO PARA LA FECHA
    GObject *fsoli_c = gtk_builder_get_object(builder, "fsoliCalReg");
    // DUDA CON ESTA CREACIÓN DEL OBJETO PARA LA FECHA
    GObject *flim_c = gtk_builder_get_object(builder, "flimCalReg");
    
    //DUDA!!!
    int fsoli_d, fsoli_m, fsoli_a, flim_d, flim_m, flim_a;
    char fsoli[12];
    char flim[12];


    if(_userIsAdmin){
         columnCombo = gtk_builder_get_object(builder, "usuarioComboBusca");
         searchEntry = gtk_builder_get_object(builder, "usuarioEntryBusca");
    }
    else{
         columnCombo = gtk_builder_get_object(builder, "usuarioComboSol");
         searchEntry = gtk_builder_get_object(builder, "usuarioEntrySol");
    }

    char queryBuffer[1024], errorBuffer[1024];

    //DUDA!!!

    gtk_calendar_get_date(GTK_CALENDAR(fsoli_c), &fsoli_a, &fsoli_m, &fsoli_d);
    fsoli_m++;
    gtk_calendar_get_date(GTK_CALENDAR(flim_c), &flim_a, &flim_m, &flim_d);
    flim_m++;

    sprintf(fsoli, "%d/%d/%d", fsoli_a, fsoli_m, fsoli_d);
    sprintf(flim, "%d/%d/%d", flim_a, flim_m, flim_d);

    const char *searchV = gtk_entry_get_text(GTK_ENTRY(searchEntry));
    int column_i = gtk_combo_box_get_active(GTK_COMBO_BOX(columnCombo)); // n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite

    switch (column_i) {
        case 0:
            const char *s = searchV;
            while (*s) {
                if (isdigit(*s++) == 0){
                    sprintf(errorBuffer, "El n_cuenta sólo incluye números!!");
                    gtk_label_set_text(GTK_LABEL(msgLabel), errorBuffer);
                    gtk_widget_set_visible(GTK_WIDGET(msgWin), TRUE);
                    return;
                }
            }
        	sprintf(queryBuffer, "SELECT n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite, FROM py_solicitudes WHERE n_cuenta = %s", searchV);
        break;
        case 1:
            sprintf(queryBuffer, "SELECT n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite, FROM py_solicitudes WHERE nombre LIKE \"%s%s%s\"", "%", searchV, "%");
            break;
        case 2:
            sprintf(queryBuffer, "SELECT n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite, FROM py_solicitudes WHERE apat LIKE \"%s%s%s\"", "%", searchV, "%");
            break;
        case 3:
            sprintf(queryBuffer, "SELECT n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite, FROM py_solicitudes WHERE isbn LIKE  %s", searchV);
            break;
        case 4:
           sprintf(queryBuffer, "SELECT n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite, FROM py_solicitudes WHERE libro LIKE \"%s%s%s\"", "%", searchV, "%");
            //sprintf(queryBuffer, "SELECT isbn, libro, editorial, prestados, disponibles FROM py_libros WHERE disponibles > 0");
            break;
        //DUDA!!!
        case 5:
            sprintf(queryBuffer, "SELECT n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite, FROM py_solicitudes WHERE f_solicitud LIKE fsoli", searchV);
            break;
        case 6:
            sprintf(queryBuffer, "SELECT n_cuenta, nombre, apat, isbn, libro, f_solicitud, f_limite, FROM py_solicitudes WHERE f_limite LIKE flim", searchV);
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

    GtkTreeStore *soli_ts = GTK_TREE_STORE(gtk_builder_get_object(builder, "solicitudQuery"));
    GtkTreeIter columna;

    int n_cuenta_r, isbn_r;// las fechas se cuentan como enteros??
    char nombre_r[35], apat_r[35], libro[50], f_soli_r[12], f_lim_r[12];

    gtk_tree_store_clear(soli_ts);

    while(row = mysql_fetch_row(res)){
        sscanf(row[0], "%d", &n_cuenta_r);
        strcpy(nombre_r, row[1]);
        strcpy(apat_r, row[2]);
        sscanf(row[3], "%d", &isbn_r);

        //DUDA!!!
        strcpy(f_soli_r, row[4]);
        strcpy(f_lim_r, row[5]);

        gtk_tree_store_append(soli_ts, &columna, NULL);
        gtk_tree_store_set(soli_ts, &columna, 0, n_cuenta_r, -1);
        gtk_tree_store_set(soli_ts, &columna, 1, nombre_r, -1);
        gtk_tree_store_set(soli_ts, &columna, 2, apat_r, -1);
        gtk_tree_store_set(soli_ts, &columna, 3, isbn_r, -1);
        //DUDA!!!
        gtk_tree_store_set(soli_ts, &columna, 4, f_soli_r, -1);
        gtk_tree_store_set(soli_ts, &columna, 5, f_lim_r, -1);
 
    }

    mysql_free_result(res);

}