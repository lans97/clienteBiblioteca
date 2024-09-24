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
    v_tipo_usuario BOOLEAN)

proc_lable: BEGIN
    DECLARE v_nombre_p VARCHAR(35);
    DECLARE v_apaterno_p VARCHAR(35);
    DECLARE v_amaterno_p VARCHAR(35);
    DECLARE v_fin INTEGER;

    DECLARE cursor_insertar_usuario CURSOR FOR SELECT
        nombre,
        a_p,
        a_m
        FROM usuarios;

    DECLARE CONTINUE HANDLER FOR NOT FOUND SET v_fin = 1;

    OPEN cursor_insertar_usuario;

    SET v_fin = 0;
        lee_insertar_usuario: LOOP
    FETCH NEXT FROM cursor_insertar_usuario INTO
        v_nombre_p,
        v_apaterno_p,
        v_amaterno_p;
    IF v_fin = 1 THEN
        LEAVE lee_insertar_usuario;
    END IF;

    IF v_nombre_p = v_nombre AND v_apaterno_p = v_apaterno AND v_amaterno_p = v_amaterno THEN
    SIGNAL SQLSTATE '60001' SET MESSAGE_TEXT = 'Ese usuario ya esta registrado en la base de datos.';
    LEAVE proc_lable;

    END IF;

    END LOOP lee_insertar_usuario;

    CLOSE cursor_insertar_usuario;

    INSERT INTO usuarios
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

END $$

DELIMITER ;
