DROP PROCEDURE p_resuelve_solicitud;
DELIMITER $

CREATE PROCEDURE p_resuelve_solicitud (v_n_cuenta INTEGER, v_isbn INTEGER)
BEGIN

    DECLARE f_id_solicitud  INT;
    DECLARE f_disponibles   INT;
    DECLARE f_prestados     INT;
    DECLARE f_activa        BOOLEAN DEFAULT FALSE;

    DECLARE cursor_solicitudes CURSOR FOR SELECT id_solicitud, activa FROM solicitudes WHERE n_cuenta = v_n_cuenta AND activa = TRUE AND isbn = v_isbn;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET f_activa = FALSE;

    OPEN cursor_solicitudes;
    FETCH NEXT FROM cursor_solicitudes INTO f_id_solicitud, f_activa;
    CLOSE cursor_solicitudes;

    IF f_activa THEN
        SET @f_disponibles = (SELECT disponibles FROM libros WHERE isbn = v_isbn);
        SET @f_prestados = (SELECT prestados FROM libros WHERE isbn = v_isbn);

        UPDATE solicitudes
        SET
            activa = FALSE
        WHERE id_solicitud = f_id_solicitud;

        UPDATE libros
        SET
            prestados = @f_prestados - 1,
            disponibles = @f_disponibles + 1
        WHERE isbn = v_isbn;

    ELSE
        SIGNAL SQLSTATE '60003' SET MESSAGE_TEXT = 'Tu numero de cuenta no tiene una solicitud activa con ese libro';
    END IF;
END $

DELIMITER ;
