
/* 
 * File:   BigCinestar.h
 * Author: dzuvan
 *
 * Created on 13.01.2018., 20.15
 */

#include <stdio.h>
#include "definitions.h"

#ifndef BIGCINESTAR_H
#define BIGCINESTAR_H

typedef enum tip_projekcije {
    TWO,
    THREE,
    FOUR
} tip_projekcije;

struct film {
    int evidencioni_broj[EVIDENCIJA];
    char naziv[MAX_NAZIV];
    int prosecna_ocena;
    tip_projekcije tip;
    int duzina_trajnja;
    char vreme_i_datum[12]; //dd mm yyyy hh mm
};

struct baket {
    film film_baket[FAKTOR];
};

#endif /* BIGCINESTAR_H */