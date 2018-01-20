#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BigCinestar.h"
#include "definitions.h"

FILE* datoteka;
FILE* pomocna_datoteka;

int main() {
    return 0;
}


void napravi_datoteku(char* temp) {
    struct baket baket;
    struct film film;
    char aktivna_datoteka[20];
    char trenutna[20];
    int zapis;

    if ((datoteka = fopen(temp, "wb+")) == NULL) {
        printf("\nDatoteka %s nije kreirana!", temp);
        fclose(datoteka);
        return;
    }

    for (unsigned int i = 0; i < FAKTOR_BAKETIRANJA; i++) {
        baket.film_baket[i].tip = DVA;
        baket.film_baket[i].prosecna_ocena = 0;
        baket.film_baket[i].evidencioni_broj[0] = '\0';
        baket.film_baket[i].naziv[0] = '\0';
        baket.film_baket[i].duzina_trajanja = 0;
        baket.film_baket[i].vreme_i_datum[0] = '\0';
        baket.film_baket[i].status = false;
    }

    for (unsigned int j = 0; j < BROJ_BAKETA; j++) {
      if (fwrite(&baket, sizeof(struct baket), 1, datoteka) != 1) {
          puts("Greska prilikom upisa u datoteku!\n");
      }
    }

    printf("\nDatoteka %s uspesno kreirana!", temp);
    strcpy(aktivna_datoteka, temp);

}
