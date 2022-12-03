DELETE FROM py_usuarios;
DELETE FROM py_libros;
DELETE FROM py_solicitudes;

INSERT INTO py_usuarios VALUES
       (200490, "Luis Angel", "Silva", "Mondragon", "a200490a@correo.uia.mx", "12345", "ITCT", 6, "1997-09-25", TRUE),
       (123456, "Juan", "Perez", "Martinez", "a123456a@correo.uia.mx", "12345", "Comunicación", 1, "2000-04-10", FALSE);
INSERT INTO py_libros VALUES (1010, "Señor de los Anillos: La Comunidad del Anillo", "ProEditorial", 3, 0);
