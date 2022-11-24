CREATE TABLE py_usuarios (
    cuenta INT PRIMARY KEY,
    nombre VARCHAR(30),
    a_paterno VARCHAR(25),
    a_materno VARCHAR(25),
    email VARCHAR(40),
    password VARCHAR(20),
    carrera VARCHAR(50),
    semestre INT,
    f_nac DATE,
    admin BOOLEAN);

CREATE TABLE py_libros (
    isbn INT PRIMARY KEY,
    nombre VARCHAR(50),
    editorial VARCHAR(20),
    disponibles INT,
    prestados INT
);

CREATE TABLE py_solicitudes (
    id_solicitud INT PRIMARY KEY AUTO INCREMENT,
    cuenta INT REFERENCES py_usuarios(cuenta),
    isbn INT REFERENCES py_libros(isbn),
    f_solicitud DATE,
    f_limite DATE
);
