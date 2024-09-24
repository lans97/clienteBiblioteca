DROP TABLE solicitudes;
DROP TABLE usuarios;
DROP TABLE libros;

CREATE TABLE usuarios(
    n_cuenta        INTEGER     PRIMARY KEY,
    nombre          VARCHAR(35) NOT NULL,
    a_p             VARCHAR(35) NOT NULL,
    a_m             VARCHAR(35) NOT NULL,
    carrera         VARCHAR(50),
    semestre        INTEGER,
    f_nac           DATE        NOT NULL,
    correo          VARCHAR(50) NOT NULL,
    pswd            VARCHAR(20) NOT NULL,
    tipo_usuario    BOOLEAN     NOT NULL
);

CREATE TABLE libros(
    isbn INTEGER PRIMARY KEY AUTO_INCREMENT,
    libro VARCHAR(50) NOT NULL,
    editorial VARCHAR(30) NOT NULL,
    prestados INTEGER NOT NULL,
    disponibles INTEGER NOT NULL
);

CREATE TABLE solicitudes(
    id_solicitud        INTEGER PRIMARY KEY AUTO_INCREMENT,
    n_cuenta            INTEGER,
    isbn                INTEGER,
    f_solicitud         DATE    NOT NULL,
    f_limite            DATE    NOT NULL,
    activa              BOOLEAN,
    FOREIGN KEY (n_cuenta)  REFERENCES py_usuarios(n_cuenta)    ON DELETE CASCADE,
    FOREIGN KEY (isbn)      REFERENCES py_libros(isbn)          ON DELETE CASCADE
    );
