#include <stdio.h>
#include <stdlib.h>
#include "lygiai.h"
#include "spalvos.h"


// Sukuria ir grąžina sunkumo lygius
SunkumoLygis *gautiLygius(void) {
    SunkumoLygis *lygiai = (SunkumoLygis *)malloc(sizeof(SunkumoLygis) * LYGIU_SK);

    lygiai[0].failoVardas = "lengvas_lygis.txt";
    lygiai[0].lygioPavadinimas = "Lengvas";
    lygiai[0].lygioTaskai = 0;

    lygiai[1].failoVardas = "vidutinis_lygis.txt";
    lygiai[1].lygioPavadinimas = "Vidutinis";
    lygiai[1].lygioTaskai = 100;

    lygiai[2].failoVardas = "sunkus_lygis.txt";
    lygiai[2].lygioPavadinimas = "Sunkus";
    lygiai[2].lygioTaskai = 300;

    lygiai[3].failoVardas = "neimanomas_lygis.txt";
    lygiai[3].lygioPavadinimas = "Neįmanomas";
    lygiai[3].lygioTaskai = 500;

    return lygiai;
}

// Funkcija parodyti visus lygius ir kiek žaidėjui reikia taškų, kad galėtų pasirinkti tą lygį
int pasirinktiSunkumoLygi(int zaidejoTaskai, SunkumoLygis *lygiai) {
    printf(SPALVA_MELYNA "|***************************************************************|\n", SPALVA_PRADINE);
    printf(SPALVA_GELTONA " Pasirinkite sunkumo lygį:\n", SPALVA_PRADINE);

    for (int i = 0; i < LYGIU_SK; i++) {
        if (zaidejoTaskai >= lygiai[i].lygioTaskai) 
        {
            printf(SPALVA_ZALIA " %d. %s\n", i + 1, lygiai[i].lygioPavadinimas, SPALVA_PRADINE);
        } 
        else 
        {
            printf(SPALVA_ZALIA " %d. %s (Reikia turėti %d taškų)\n", i + 1, lygiai[i].lygioPavadinimas, lygiai[i].lygioTaskai, SPALVA_PRADINE);
        }
    }

    int pasirinkimas;
    int tinkamaIvestis = 0;

    while (!tinkamaIvestis) 
    {
        printf(SPALVA_MELYNA "|***************************************************************|\n", SPALVA_PRADINE);
        printf(SPALVA_GELTONA " Įveskite pasirinkto lygio numerį: ", SPALVA_PRADINE);

        
        if (scanf("%d", &pasirinkimas) != 1) 
        {
            printf(SPALVA_RAUSVA "Klaida: Įveskite tinkamą skaičių.\n", SPALVA_PRADINE);
            printf(SPALVA_MELYNA "|***************************************************************|\n", SPALVA_PRADINE);
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
                printf(SPALVA_RAUSVA "Klaida: Neturite pakankamai taškų šiam lygiui pasirinkti.\n", SPALVA_PRADINE);
            }
        } 
        else 
        {
            printf(SPALVA_RAUSVA "Klaida: Pasirinkimas turi būti tarp 1 ir %d.\n", LYGIU_SK, SPALVA_PRADINE);
        }
    }

    return pasirinkimas - 1;
}
