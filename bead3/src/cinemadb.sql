DROP DATABASE IF EXISTS cinemadb;
CREATE DATABASE cinemadb;
USE cinemadb;

CREATE TABLE filmek(
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    cim VARCHAR(40),
	szarmazas VARCHAR(20),
	szinkronizalt INTEGER,
	rendezo VARCHAR(30),
	szinopszis VARCHAR(40),
	hossz INTEGER
);

CREATE TABLE termek (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    nev VARCHAR(30),
    sorok_oszlopok INT NOT NULL
);

CREATE TABLE eloadasok (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    film_id INTEGER NOT NULL,
	terem_id INTEGER NOT NULL,
    kezdo_idopont Date,
    CONSTRAINT eloadasoktotermek
        FOREIGN KEY (terem_id) 
        REFERENCES termek (id),
    CONSTRAINT eloadasoktofilmek
        FOREIGN KEY (film_id) 
        REFERENCES filmek (id)
);



CREATE TABLE helyek (
    hely_id INTEGER PRIMARY KEY AUTO_INCREMENT,
    eloadas_id INTEGER,
    terem_id INTEGER,
    sor INTEGER,
    oszlop INTEGER,
    status INTEGER,
    CONSTRAINT helyektoeloadasok
        FOREIGN KEY (eloadas_id) 
        REFERENCES eloadasok (id),
    CONSTRAINT renttotermek 
        FOREIGN KEY (terem_id) 
        REFERENCES termek (id)
);


insert into filmek(cim, szarmazas, szinkronizalt, rendezo, szinopszis, hossz) values ("Életrevalók", "Francia", 1 , "Olivier Nakache, Éric Toledano", NULL, 108);
insert into filmek(cim, szarmazas, szinkronizalt, rendezo, szinopszis, hossz) values ("DeadPool", "Amerika", 1 , "Tim Miller", NULL, 100);

insert into termek(nev, sorok_oszlopok) values ("kisterem", 3);
insert into termek(nev, sorok_oszlopok) values ("kozepes", 4);
insert into termek(nev, sorok_oszlopok) values ("nagy", 5);

insert into eloadasok(film_id, terem_id, kezdo_idopont) values(1, 1, '2016-04-16');
insert into eloadasok(film_id, terem_id, kezdo_idopont) values(1, 1, '2016-04-16');
insert into eloadasok(film_id, terem_id, kezdo_idopont) values(2, 2, '2016-05-16');

insert into helyek(eloadas_id, terem_id, sor, oszlop, status) values(1, 1, 5, 3, 1);
;
