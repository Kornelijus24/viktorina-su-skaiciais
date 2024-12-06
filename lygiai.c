#include <stdio.h>
#include <stdlib.h>
#include "lygiai.h"


// Sukuria ir grąžina sunkumo lygius
SunkumoLygis *gautiLygius(void) {
    SunkumoLygis *lygiai = (SunkumoLygis *)malloc(sizeof(SunkumoLygis) * LYGIU_SK);

    lygiai[0].failoVardas = "lengvas_lygis.txt";
    lygiai[0].lygioPavadinimas = "Lengvas";
    lygiai[0].lygioTaskai = 0;

    lygiai[1].failoVardas = "vidutinis_lygis.txt";
    lygiai[1].lygioPavadinimas = "Vidutinis";
    lygiai[1].lygioTaskai = 50;

    lygiai[2].failoVardas = "sunkus_lygis.txt";
    lygiai[2].lygioPavadinimas = "Sunkus";
    lygiai[2].lygioTaskai = 100;

    lygiai[3].failoVardas = "neimanomas_lygis.txt";
    lygiai[3].lygioPavadinimas = "Neįmanomas";
    lygiai[3].lygioTaskai = 200;

    return lygiai;
}

// Funkcija parodyti visus lygius ir kiek žaidėjui reikia taškų, kad galėtų pasirinkti tą lygį
int pasirinktiSunkumoLygi(int zaidejoTaskai, SunkumoLygis *lygiai) {
    printf("|***************************************************************|\n");
    printf(" Pasirinkite sunkumo lygį:\n");

    for (int i = 0; i < LYGIU_SK; i++) {
        if (zaidejoTaskai >= lygiai[i].lygioTaskai) 
        {
            printf(" %d. %s\n", i + 1, lygiai[i].lygioPavadinimas);
        } 
        else 
        {
            printf(" %d. %s (Reikia turėti %d taškų)\n", i + 1, lygiai[i].lygioPavadinimas, lygiai[i].lygioTaskai);
        }
    }

    int pasirinkimas;
    int tinkamaIvestis = 0;

    while (!tinkamaIvestis) 
    {
        printf("|***************************************************************|\n");
        printf(" Įveskite pasirinkto lygio numerį: ");

        
        if (scanf("%d", &pasirinkimas) != 1) 
        {
            printf("Klaida: Įveskite tinkamą skaičių.\n");
            printf("|***************************************************************|\n");
            while (getchar() != '\n');
            continue;
        }

        // Patikrina, ar skaičius yra tarp galimų pasirinkimų
        if (pasirinkimas >= 1 && pasirinkimas <= LYGIU_SK) 
        {
            if (zaidejoTaskai >= lygiai[pasirinkimas - 1].lygioTaskai) 
            {
                tinkamaIvestis = 1; 
            } 
            else 
            {
                printf("Klaida: Neturite pakankamai taškų šiam lygiui pasirinkti.\n");
            }
        } 
        else 
        {
            printf("Klaida: Pasirinkimas turi būti tarp 1 ir %d.\n", LYGIU_SK);
        }
    }

    return pasirinkimas - 1;
}
