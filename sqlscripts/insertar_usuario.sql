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
    v_tipo_usuario VARCHAR(35))

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
        FROM py_usuarios;

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

    SELECT CONCAT ("El usuario ", v_nombre_p, " ", v_apaterno_p, " ", v_amaterno_p, " ya existe en la base de datos.") AS msg;
    LEAVE proc_lable;

    END IF;

    END LOOP lee_insertar_usuario;

    CLOSE cursor_insertar_usuario;

    INSERT INTO py_usuarios
    VALUES(
        v_cuenta,
        v_nombre,
        v_apaterno,
        v_amaterno,
        v_carrera,
        v_semestre,
        v_f_nac,
        v_mail,
        v_contra,
        v_tipo_usuario
    );

    SELECT * FROM py_usuarios WHERE n_cuenta = v_cuenta;

END $$

DELIMITER ;
