#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BigCinestar.h"
#include "definitions.h"

FILE* datoteka;
FILE* pomocna_datoteka;
char aktivna_datoteka[20];
char trenutna[20];
int zapis;

int main() {
    return 0;
}

void napravi_datoteku(char* temp) {
    printf("Kreiram datoteku...\n");
    baket baket;

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

    printf("\nDatoteka <%s> uspesno kreirana!", temp);
    strcpy(aktivna_datoteka, temp);
}

void otvori_datoteku(char* temp) {
    printf("Otvaram...\n");

    fclose(datoteka);
    if ((datoteka = fopen(temp, "rb+")) == NULL) {
        printf("\nDatoteka <%s> ne postoji", temp);
        return;
    }
    printf("Datoteka <%s> uspesno otvorena", temp);
    strcpy(aktivna_datoteka, temp);
}

int transformacija_kljuca(int kljuc) {
  return kljuc % BROJ_BAKETA + 1;
}

pretraga pronadji_zapis(FILE* dat, int kljuc) {
  int adresa = transformacija_kljuca(kljuc);
  int a = 2;
  pretraga pretraga;
  baket baket;

  do {
      fseek(dat,sizeof(baket) * (adresa - 1), SEEK_SET );
      if (fread(&baket, sizeof(baket), 1, datoteka) != 1) {
          printf("Greska prilikom citanja datoteke u toku pretrage.");
          a = 0;
          return;
      }
      for (unsigned int i = 0; i < FAKTOR_BAKETIRANJA; i++) {
          if (!baket.film_baket[i].status ) {
              pretraga.broj = i;
              pretraga.pozicija = sizeof(baket) * (adresa - 1);
              pretraga.status = false;
              a = 1;
              return pretraga;
          }
          if (baket.film_baket[i].evidencioni_broj == kljuc) {
              pretraga.broj =i;
              pretraga.pozicija = sizeof(baket) * (adresa - 1);
              pretraga.status = true;
              a = 1;
              return pretraga;
          }
          if (i == 2) {
              adresa++;
          }
      }
  } while(a == 2);
}
