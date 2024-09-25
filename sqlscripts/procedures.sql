DROP PROCEDURE p_insertar_usuario;
DELIMITER $$

CREATE PROCEDURE p_insertar_usuario (
    v_cuenta INTEGER,
    v_nombre VARCHAR(35),
    v_apaterno VARCHAR(35),
    v_amaterno VARCHAR(35),
    v_carrera VARCHAR(50),
    v_semestre INTEGER,
    v_f_nac DATE,
    v_mail VARCHAR(50),
    v_contra VARCHAR(35),
    v_tipo_usuario VARCHAR(35)
)

proc_lable: BEGIN
    DECLARE v_n_cuenta_p INTEGER;
    DECLARE v_nombre_p VARCHAR(35);
    DECLARE v_apaterno_p VARCHAR(35);
    DECLARE v_amaterno_p VARCHAR(35);
    DECLARE v_carrera_p VARCHAR(50);
    DECLARE v_semestre_p INTEGER;
    DECLARE v_f_nac_p DATE;
    DECLARE v_correo_p VARCHAR(50);
    DECLARE v_pswd_p VARCHAR (35);
    DECLARE v_tipo_usuario_p BOOLEAN;
    DECLARE v_fin INTEGER;

    DECLARE cursor_insertar_usuario CURSOR FOR SELECT
        n_cuenta,
        nombre,
        a_p,
        a_m,
        carrera,
        semestre,
        f_nac,
        correo,
        pswd,
        tipo_usuario
        FROM registro;

    DECLARE CONTINUE HANDLER FOR NOT FOUND SET v_fin = 1;

    OPEN cursor_insertar_usuario;

    SET v_fin = 0;
        lee_insertar_usuario: LOOP
    FETCH NEXT FROM cursor_insertar_usuario INTO
        v_n_cuenta_p,
        v_nombre_p,
        v_apaterno_p,
        v_amaterno_p,
        v_carrera_p,
        v_semestre_p,
        v_f_nac_p,
        v_correo_p,
        v_pswd_p,
        v_tipo_usuario_p;
    IF v_fin = 1 THEN
        LEAVE lee_insertar_usuario;
    END IF;

    IF v_nombre_p = v_nombre AND v_apaterno_p = v_apaterno AND v_amaterno_p = v_amaterno THEN

    SELECT CONCAT ("El usuario", v_nombre_p, " ", v_apaterno_p, " ", v_amaterno_p, " ya existe en la base de datos.") AS msg
    LEAVE proc_lable;

    END IF;

    END LOOP lee_insertar_usuario;

    CLOSE cursor_insertar_usuario;

    INSERT INTO py_usuarios
    VALUES(
        v_nombre,
        v_apaterno,
        v_amaterno,
        v_carrera,
        v_semestre,
        v_f_nac,
        v_cuenta,
        v_mail,
        v_contra,
        v_tipo_usuario
    );

    SELECT * FROM py_usuarios WHERE n_cuenta = v_cuenta;

END $$

DELIMITER ;

---

DROP PROCEDURE alta_solicitud;
DELIMITER $

CREATE PROCEDURE alta_solicitud (
    v_n_cuenta INTEGER,
    v_id_isbn INTEGER
)

BEGIN

    DECLARE f_solicitud_v DATE;
    DECLARE f_limite_v DATE;
    DECLARE f_disponibles INT;
    DECLARE f_prestados INT;
    DECLARE f_activa BOOLEAN DEFAULT FALSE;

    SELECT f_disponibles:= disponibles, f_prestados:=prestados FROM py_libros WHERE isbn = v_id_isbn;

    DECLARE cursor_solicitudes CURSOR FOR SELECT activa FROM py_solicitudes WHERE n_cuenta = v_n_cuenta AND activa = TRUE;

    DECLARE CONTINUE HANDLER FOR NOT FOUND SET v_activa = FALSE;

    OPEN cursor_solicitudes;
    FETCH FIRST FROM cursor_solicitudes INTO f_activa;
    CLOSE cursor_solicitudes;

    IF f_disponibles > 0 AND !f_activa THEN
        SELECT DATE(NOW ()) INTO f_solicitud_v;
        SELECT DATE_ADD(f_solicitud_v, INTERVAL 8 DAY) INTO f_limite_v;

        INSERT INTO solicitudes
        VALUES (
            NULL,
            v_n_cuenta,
            v_id_isbn,
            f_solicitud_v,
            f_limite_v
            TRUE
        );

        UPDATE py_libros
        SET
            disponibles = f_disponibles - 1,
            prestados = f_prestados + 1
        WHERE v_id_isbn = isbn;

        SELECT CONCAT('Tu solcitud se realizó con éxito con id', v_id_solicitud) AS msg;
    ELSE
        SELECT CONCAT('No hay libros disponibles con el ISBN ', v_id_isbn) AS msg;
    END IF;
END $

DELIMITER;

---

DROP PROCEDURE resuelve_solicitud;
DELIMITER $

CREATE PROCEDURE resuelve_solicitud (v_n_cuenta INTEGER)

BEGIN

    DECLARE f_id_solicitud;
    DECLARE f_isbn;
    DECLARE f_disponibles INT;
    DECLARE f_prestados INT;
    DECLARE f_activa BOOLEAN DEFAULT FALSE;

    DECLARE cursor_solicitudes CURSOR FOR SELECT id_solicitud, activa FROM py_solicitudes WHERE n_cuenta = v_n_cuenta AND activa = TRUE;

    DECLARE CONTINUE HANDLER FOR NOT FOUND SET v_activa = FALSE;

    OPEN cursor_solicitudes;
    FETCH FIRST FROM cursor_solicitudes INTO f_id_solicitud, f_activa;
    CLOSE cursor_solicitudes;

    IF f_activa THEN
        SELECT f_isbn:=isbn FROM py_solicitudes WHERE n_cuenta = v_n_cuenta AND activa = TRUE;
        SELECT f_disponibles:= disponibles, f_prestados:=prestados FROM py_libros WHERE isbn = f_isbn;

        UPDATE py_solicitudes
        SET
            activa = FALSE
        WHERE id_solicitud = f_id_solicitud;

        UPDATE py_libros
        SET
            prestados = f_prestados - 1;
            disponible = f_disponibles + 1;
        WHERE isbn = f_isbn;

        SELECT CONCAT('Tu solcitud se resolvió con éxito') AS msg;
    ELSE
        SELECT CONCAT('Tu número de cuenta no tiene una solicitud activa') AS msg;
    END IF;
END $

DELIMITER;
