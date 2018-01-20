
/* 
 * File:   main.cpp
 * Author: dzuvan
 *
 * Created on 13.01.2018., 16.21
 */

#include <stdio.h>
#include <stdlib.h>

#include "BigCinestar.h"
#include "definitions.h"

/*
 * 
 */
int main(int argc, char** argv) {

    FILE *f;
    char n[40];
    char c;
    int broj_redova;
    int broj;

    printf("Unesite naziv datoteke(do 40 karaktera): \n");
    scanf("%s", n);


    printf("Unesite broj redova:\n");
    scanf("%d", &broj_redova);

    for (unsigned int i = 0; i < broj_redova; i++) {
        printf("Unesite broj");
        fscanf(f, "%d", &broj);
    }

    if ((f = fopen(n, "w")) == NULL) {
        printf("Datoteka <%s> nije uspesno otvorena.\n", n);
        exit(1);
    }

    printf("Datoteka<%s> je uspesno otvorena.\n", n);
    printf("Tekstualni sadrzaj datoteke. <%s>...\n", n);

    //        while ((c = fgetc(f)) != EOF) {
    //            putchar(c);
    //        }
    //        

    if (fclose(f) == EOF) {
        printf("\tNastupila je greska tokom zatvaranja");
    } else {
        printf("\tZatvarnje uspesno!");
    }

    return 0;
}
