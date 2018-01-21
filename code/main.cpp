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
        baket.film_baket[i].evidencioni_broj = 0;
        baket.film_baket[i].naziv[0] = '\0';
        baket.film_baket[i].duzina_trajanja = 0;
        baket.film_baket[i].vreme_i_datum[0] = '\0';
        baket.film_baket[i].oznaka_sale[0] = '\0';
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
                pretraga.broj = i;
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

void dodaj_zapis() {
    film film;

    do {
        printf("\nUnesite evidencioni broj filma[%d cifara]: ", EVIDENCIJA);
        scanf("%d", &film.evidencioni_broj);
    } while (film.evidencioni_broj < 10000 || film.evidencioni_broj > 99999 );

    do {
        printf("\nUnesite naziv filma[%d karaktera]: ", MAX_NAZIV);
        scanf("%s", film.naziv);
    } while (strlen(film.naziv) > MAX_NAZIV);

    do {
        printf("\nUnesite prosecnu ocenu[1-5]: ");
    } while (film.prosecna_ocena < 1 || film.prosecna_ocena > 5);

    do {
        printf("\nUnesite vreme i datum prikazivanja filma[%d cifri]: ", DATE_TIME);
        scanf("%s", film.vreme_i_datum);
    } while (strlen(film.vreme_i_datum) > DATE_TIME);

    do {
        printf("\nUnesite oznaku sale u kojoj se prikazuje film[%d karaktera]: ", MAX_SALA);
        scanf("%s", film.oznaka_sale);
    } while (strlen(film.oznaka_sale) > MAX_SALA);

    do {
        printf("\nOdaberite tip projekcije[2/3/4]: ");
        scanf("%d", &film.tip);
    } while (film.tip < 2 || film.tip > 4);

    do {
        printf("\nUnesite duzinu trajanja filma u minutima[do %d minuta]:", MAX_TRAJANJE);
        scanf("%d", &film.duzina_trajanja);
    } while (film.duzina_trajanja < 0 || film.duzina_trajanja > MAX_TRAJANJE);

    film.status = true;
    if ((fwrite(&film, sizeof(film), 1, pomocna_datoteka)) != 1) {
        puts("\nGreska prilikom ucitavanja datoteke.");
    }
    puts ("Slog uspesno dodat.");
}

void napravi_glavnu_datoteku() {
    baket baket;
    film film;
    pretraga pretraga;
    int adresa;
    int i;

    for (adresa = 0; adresa < FAKTOR_BAKETIRANJA * BROJ_BAKETA; adresa ++) {
        fseek(pomocna_datoteka, sizeof(film) * adresa, SEEK_SET);
        if (fread(&film, sizeof(film), 1, pomocna_datoteka) != 1) {
            printf("\nGreska prilikom citanja pomocne datoteke.");
            return;
        }
        pretraga = pronadji_zapis(datoteka, film.evidencioni_broj);
        if (pretraga.status == false) {
            i = pretraga.broj;
            fseek(datoteka, pretraga.pozicija, SEEK_SET);
            if (fread(&baket, sizeof(baket), 1, datoteka) != 1) {
                printf("\nGreska prilikom citanja glavne datoteke.");
                return;
            }

            baket.film_baket[i].evidencioni_broj = film.evidencioni_broj;
            baket.film_baket[i].prosecna_ocena = film.prosecna_ocena;
            baket.film_baket[i].duzina_trajanja = film.duzina_trajanja;
            baket.film_baket[i].tip = film.tip;
            baket.film_baket[i].status = film.status;
            strcpy(baket.film_baket[i].naziv,film.naziv);
            strcpy(baket.film_baket[i].vreme_i_datum, film.vreme_i_datum);
            strcpy(baket.film_baket[i].oznaka_sale, film.oznaka_sale);

            fseek(datoteka, pretraga.pozicija, SEEK_SET);
            if ((fwrite(&baket, sizeof(baket), 1, datoteka) != 1)) {
                puts("\nGreska prilikom upisa u glavnu datoteku");
            }
        }
    }
    if ((pomocna_datoteka = fopen("Help.bin", "wb+")) == NULL) {
        printf("\nNeuspesno otvaranje pomocne datoteke");
        fclose(pomocna_datoteka);
    }
}

