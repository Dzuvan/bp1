#ifndef BIGCINESTAR_H
#define BIGCINESTAR_H

#include <stdio.h>
#include "definitions.h"

typedef enum tip_projekcije {
    DVA = 2,
    TRI = 3,
    CETIRI = 4
} tip_projekcije;

struct film {
    int evidencioni_broj;
    char naziv[MAX_NAZIV];
    tip_projekcije tip;
    int prosecna_ocena;
    int duzina_trajanja;
    char oznaka_sale[MAX_SALA];
    char vreme_i_datum[DATE_TIME]; //dd mm yyyy hh mm
    bool status;
    struct film *sledeci;
};

struct baket {
    film film_baket[FAKTOR_BAKETIRANJA];
};

struct pretraga {
    int pozicija;
    int broj;
    bool status;
};

int transformacija_kljuca(int);
void napravi_datoteku(char*);
void otvori_datoteku(char*);
pretraga pronadji_zapis(FILE*, int);
void dodaj_zapis();

#endif /* BIGCINESTAR_H */
