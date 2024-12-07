#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zaidejas.h"

// Funkcija rasti žaidėjo taškus ir sužaistus roundus faile
void skaitytiTaskusIrRoundus(const char *vardas, int *taskai, int *roundai) 
{
    FILE *failas = fopen(TASKU_FAILAS, "r");
    if (!failas) 
    {
        *taskai = 0;
        *roundai = 0;
        return;
    }

    char failoVardas[VARDO_ILGIS];
    int nuskaitomiTaskai, nuskaitomiRoundai;

    while (fscanf(failas, "%s %d %d", failoVardas, &nuskaitomiTaskai, &nuskaitomiRoundai) == 3) 
    {
        if (strcmp(failoVardas, vardas) == 0) 
        {
            *taskai = nuskaitomiTaskai;
            *roundai = nuskaitomiRoundai;
            fclose(failas);
            return;
        }
    }

    fclose(failas);
    *taskai = 0;
    *roundai = 0;
}


// Funkcija įrašyti žaidėjo taškus ir sužaistus roundus į failą
void irasytiTaskusIrRoundus(const char *vardas, int taskai, int roundai) 
{
    FILE *pagrindinisFailas = fopen(TASKU_FAILAS, "r");
    FILE *laikinasFailas = fopen("laikinas.txt", "w");

    if (!laikinasFailas) 
    {
        perror("Nepavyko sukurti laikino failo");
        return;
    }

    int vardasRastas = 0;
    char failoVardas[VARDO_ILGIS];
    int esamiTaskai, esamiRoundai;

    if (pagrindinisFailas)
    {
        while (fscanf(pagrindinisFailas, "%s %d %d", failoVardas, &esamiTaskai, &esamiRoundai) == 3) 
        {
            if (strcmp(failoVardas, vardas) == 0) 
            {
                fprintf(laikinasFailas, "%s %d %d\n", vardas, taskai, roundai);
                vardasRastas = 1;
            } 
            else 
            {
                fprintf(laikinasFailas, "%s %d %d\n", failoVardas, esamiTaskai, esamiRoundai);
            }
        }
        fclose(pagrindinisFailas);
    }

    if (!vardasRastas) 
    {
        fprintf(laikinasFailas, "%s %d %d\n", vardas, taskai, roundai);
    }

    fclose(laikinasFailas);

    remove(TASKU_FAILAS);
    rename("laikinas.txt", TASKU_FAILAS);
}

