DELETE FROM usuarios;
DELETE FROM libros;

INSERT INTO usuarios
VALUES
/*
 n_cuenta, nombre,              a_p,        a_m,          carrera,      semestre,  f_nac,        correo,               pswd,    tipo_usuario
*/
(213747,   'Dylan',            'Del Olmo', 'Alba',       'ITCT',        7,        '2000/01/27', 'dylandoa@gmail.com', '1o2s3s', 1),
(215222,   'María del Carmen', 'Ramos',    'Gonzalez',   'Mecatrónica', 7,        '2001/09/06', 'maria@gmail.com',    '4o5o6o', 1),
(200490,   'Luis Angel',       'Silva',    'Mondragon',  'ITCT',        6,        '1997/09/25', 'luisilva@gmail.com', '12345',  1),
(781620,   'Marlene',          'Serrano',  'Rodríguez',  'ITCT',        4,        '2000/03/15', 'marlene@gmail.com',  '10s11e', 1);

INSERT INTO libros (libro, editorial, prestados, disponibles)
VALUES
/*
  libro,                         editorial      prestados,  disponibles
*/
('Señor de los anillos',        'Perro Guango', 0,          7),
('Los caballeros',              'Morungo',      0,          5),
('Ratón Vaquero',               'Tuntun',       0,          5),
('Tornado Peligroso',           'Sustituto',    0,          1),
('Sinfónicos Locos',            'Triunfo',      0,          4),
('Cotorro Salvaje',             'Trinchera',    0,          3),
('Catarsis',                    'Zum',          0,          1),
('Wally Rojas',                 'Tronco',       0,          4),
('Calle Elm',                   'Terricola',    0,          5),
('Trucos Legales',              'vuela',        0,          2),
('Catalejo',                    'Pilares',      0,          1),
('Harry Potter',                'Magic',        0,          6),
('El Principito',               'Castillo',     0,          2),
('Guarros',                     'Gula',         0,          1),
('Pedro Paramo',                'rm',           0,          3),
('Efecto Mariposa',             'Timbre',       0,          2),
('La Medicina Contemporanea',   'Buena vida',   0,          7),
('Mala Vibra',                  'Trillas',      0,          3),
('Triunfo',                     'Oceano',       0,          11),
('Castillo Encantado',          'Buena vida',   0,          7),
('Ritmos Sociales',             'Trillas',      0,          3),
('Efectos de la vida',          'Trillas',      0,          3),
('Sin pasión no hay acción',    'alfagara',     0,          9),
('El arte de mirar',            'Planeta',      0,          3),
('Los juegos del hambre',       'Oceano',       0,          4),
('Maze Runner',                 'Trillas',      0,          2),
('Yo, Díaz',                    'Grijalbo',     0,          2),
('Iturbide',                    'Grijalbo',     0,          3);
