CREATE TABLE py_users(
	n_cuenta INT PRIMARY KEY,
	nombre VARCHAR(25),
	a_paterno VARCHAR(25),
	a_materno VARCHAR(25),
	carrera VARCHAR(50),
	semestre INT,
	f_nac DATE,
	email VARCHAR(30),
	passwd VARCHAR(20),
	admin BOOLEAN
<<<<<<< HEAD
);
=======
)
>>>>>>> cd4d9beb795b43c085a37c87c07a8272e9b3cf15

CREATE TABLE py_libros(
	isbn INT PRIMARY KEY,
	nombre VARCHAR(50),
	editorial VARCHAR(20),
	prestados INT,
	disponibles INT
<<<<<<< HEAD
);
=======
)
>>>>>>> cd4d9beb795b43c085a37c87c07a8272e9b3cf15

CREATE TABLE py_solicitudes(
	id INT PRIMARY KEY,
	isbn INT REFERENCES py_libros(isbn),
	n_cuenta INT REFERENCES py_users(n_cuenta),
	f_devolucion DATE
<<<<<<< HEAD
);
=======
)
>>>>>>> cd4d9beb795b43c085a37c87c07a8272e9b3cf15
