DROP PROCEDURE p_resuelve_solicitud;
DELIMITER $

CREATE PROCEDURE p_resuelve_solicitud (v_n_cuenta INTEGER)
BEGIN

    DECLARE f_id_solicitud  INT;
    DECLARE f_isbn          INT;
    DECLARE f_disponibles   INT;
    DECLARE f_prestados     INT;
    DECLARE f_activa        BOOLEAN DEFAULT FALSE;

    DECLARE cursor_solicitudes CURSOR FOR SELECT id_solicitud, activa FROM py_solicitudes WHERE n_cuenta = v_n_cuenta AND activa = TRUE;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET f_activa = FALSE;

    OPEN cursor_solicitudes;
    FETCH NEXT FROM cursor_solicitudes INTO f_id_solicitud, f_activa;
    CLOSE cursor_solicitudes;

    IF f_activa THEN
        SET @f_isbn = (SELECT isbn FROM py_solicitudes WHERE n_cuenta = v_n_cuenta AND activa = TRUE);
        SET @f_disponibles = (SELECT disponibles FROM py_libros WHERE isbn = @f_isbn);
        SET @f_prestados = (SELECT prestados FROM py_libros WHERE isbn = @f_isbn);

        UPDATE py_solicitudes
        SET
            activa = FALSE
        WHERE id_solicitud = f_id_solicitud;

        UPDATE py_libros
        SET
            prestados = @f_prestados - 1,
            disponibles = @f_disponibles + 1
        WHERE isbn = @f_isbn;

        SELECT CONCAT('Tu solcitud se resolvió con éxito') AS msg;
    ELSE
        SIGNAL SQLSTATE '60003' SET MESSAGE_TEXT = 'Tu numero de cuenta no tiene una solicitud activa';
    END IF;
END $

DELIMITER ;
