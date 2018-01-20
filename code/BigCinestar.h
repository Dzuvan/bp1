#ifndef BIGCINESTAR_H
#define BIGCINESTAR_H

#include <stdio.h>
#include "definitions.h"

typedef enum tip_projekcije {
    DVA,
    TRI,
    CETIRI
} tip_projekcije;

struct film {
    tip_projekcije tip;
    int prosecna_ocena;
    char evidencioni_broj[EVIDENCIJA];
    char naziv[MAX_NAZIV];
    int duzina_trajanja;
    char vreme_i_datum[12]; //dd mm yyyy hh mm
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

int transformacija_kljuca(int kljuc);
void napravi_datoteku(char* temp);
void otvori_datoteku(char* temp);

#endif /* BIGCINESTAR_H */
