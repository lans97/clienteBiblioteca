DROP PROCEDURE p_alta_solicitud;

DELIMITER $

CREATE PROCEDURE p_alta_solicitud (
    v_n_cuenta INTEGER,
    v_id_isbn INTEGER
)

BEGIN

    DECLARE f_solicitud_v DATE;
    DECLARE f_limite_v DATE;
    DECLARE f_disponibles INT;
    DECLARE f_prestados INT;

    SET @f_disponibles = (SELECT disponibles FROM py_libros WHERE isbn = v_id_isbn);
    SET @f_prestados = (SELECT prestados FROM py_libros WHERE isbn = v_id_isbn);

    IF @f_disponibles > 0 THEN
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
        SIGNAL SQLSTATE '60002' SET MESSAGE_TEXT = 'No hay libros disponibles';
    END IF;
END $

DELIMITER ;
