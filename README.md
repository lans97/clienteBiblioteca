# ClienteBiblioteca

## Curso: Sistemas de Bases de Datos O2022

Docente. Edgar Lopez Meneses

## Equipo 4
Integrantes:
- Luis Silva
- María Ramos
- Dylan del Olmo
- Marlene Serrano

## Descripción
Lenguaje: C
Libs: mysqlclient, gtk+-3.0
Plataforma: Linux

## Instrucciones
    $ make
    $ ./bin/BibClient

El archivo compila contiene un script que se encarga de compilar con las opciones necesarias.
El archivo BibClient es el resultado final de compilar el proyecto.

## Descripción del Proyecto

El objetivo del proyecto es diseñar una base de datos y un software que permita registrar, buscar, y visualizar los préstamos de libros en la biblioteca de la Universidad Iberoamericana. Este repositorio contiene el software que hace de interface entre los usuarios y la base de datos.

### Modulos

#### Registro y Actualización de Usuarios [admin]

Registra o actualiza un usuario con la siguiente información
- Nombre
- Apellidos
- Carrera
- Semestre
- Fecha de nacimiento
- Número de cuenta *
- Correo electrónico
- Contraseña del nuevo usuario
- Tipo de usuario que será (admin / solicitante)

\* El número de cuenta será la llave primaria por lo cual no podrá ser modificada.

#### Búsqueda [admin]

Busqueda de usuarios registrados con base en los siguientes criterios:
- Nombre
- Apellido paterno
- Número de cuenta
- Nombre de carrera
- Nombre del libro prestado
- ISBN del libro prestado

Resultados de busqueda:
- Cuenta
- Nombre
- Apellido paterno
- ISBN del libro(s) que tiene en préstamo
- Nombre del libro(s) que tiene en préstamo
- Fecha de solicitud del libro
- Fecha límite de devolución

Catálogo de libros que los usuarios pueden seleccionar, cada libro deberá tener:
- ISBN
- Nombre
- Editorial
- Ejemplares prestados
- Ejemplares disponibles

#### Préstamos y Devoluciones [solicitante]

1. Selección de libros disponibles para prestamo.
2. El sistema deberá revisar la disponibilidad y notificar al usuario. 
3. Registro de fecha de devolución (fecha actual + 8 dd naturales).
4. Devolución de libros solicitados.
