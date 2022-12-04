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


    DECLARE cursor_solicitudes CURSOR FOR SELECT activa FROM py_solicitudes WHERE n_cuenta = v_n_cuenta AND activa = TRUE;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET f_activa = FALSE;

    OPEN cursor_solicitudes;
    FETCH NEXT FROM cursor_solicitudes INTO f_activa;
    CLOSE cursor_solicitudes;

    SELECT @f_disponibles := disponibles, @f_prestados := prestados FROM py_libros WHERE isbn = v_id_isbn;

    SELECT !f_activa, @f_disponibles;

    IF @f_disponibles > 0 AND !f_activa THEN
        SELECT DATE(curdate()) INTO f_solicitud_v;
        SELECT DATE_ADD(f_solicitud_v, INTERVAL 8 DAY) INTO f_limite_v;

        INSERT INTO py_solicitudes
        VALUES (
            NULL,
            v_n_cuenta,
            v_id_isbn,
            f_solicitud_v,
            f_limite_v,
            TRUE
        );

        UPDATE py_libros
        SET
            disponibles = @f_disponibles - 1,
            prestados = @f_prestados + 1
        WHERE v_id_isbn = isbn;

        SELECT 'Tu solcitud se realizó con éxito' AS msg;
    ELSE
        SELECT CONCAT('No hay libros disponibles con el ISBN ', v_id_isbn, ' o ya cuentas con una solicitud activa') AS msg;
    END IF;
END $

DELIMITER ;
