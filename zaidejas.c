#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "zaidejas.h"
#include "spalvos.h"

// Funkcija rasti žaidėjo taškus ir sužaistus roundus faile
void skaitytiTaskusIrRoundus(const char *vardas, int *taskai, int *roundai, int *ilgiausiaSerija) 
{
    FILE *failas = fopen(TASKU_FAILAS, "r");
    if (!failas) 
    {
        *taskai = 0;
        *roundai = 0;
        *ilgiausiaSerija = 0;

        return;
    }

    char failoVardas[VARDO_ILGIS];
    int nuskaitomiTaskai, nuskaitomiRoundai, nuskaitomaSerija;

    while (fscanf(failas, "%s %d %d %d", failoVardas, &nuskaitomiTaskai, &nuskaitomiRoundai, &nuskaitomaSerija) == 4) 
    {
        if (strcmp(failoVardas, vardas) == 0) 
        {
            *taskai = nuskaitomiTaskai;
            *roundai = nuskaitomiRoundai;
            *ilgiausiaSerija = nuskaitomaSerija;
            fclose(failas);
            return;
        }
    }

    fclose(failas);
    *taskai = 0;
    *roundai = 0;
    *ilgiausiaSerija = 0;
}


// Funkcija įrašyti žaidėjo taškus ir sužaistus roundus į failą
void irasytiTaskusIrRoundus(const char *vardas, int taskai, int roundai, int ilgiausiaSerija) 
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
    int esamiTaskai, esamiRoundai, esamaSerija;

    if (pagrindinisFailas)
    {
        while (fscanf(pagrindinisFailas, "%s %d %d %d", failoVardas, &esamiTaskai, &esamiRoundai, &esamaSerija) == 4) 
        {
            if (strcmp(failoVardas, vardas) == 0) 
            {

                // Atnaujinti ilgiausia serija, jeigu ji didesnė už jau buvusią
                if (ilgiausiaSerija < esamaSerija)
                {
                    ilgiausiaSerija = esamaSerija;
                }
                else if(ilgiausiaSerija > esamaSerija)
                {
                    esamaSerija = ilgiausiaSerija;
                }

                fprintf(laikinasFailas, "%s %d %d %d\n", vardas, taskai, roundai, ilgiausiaSerija);
                vardasRastas = 1;
            } 
            else 
            {
                fprintf(laikinasFailas, "%s %d %d %d\n", failoVardas, esamiTaskai, esamiRoundai, esamaSerija);
            }
        }
        fclose(pagrindinisFailas);
    }

    if (!vardasRastas) 
    {
        fprintf(laikinasFailas, "%s %d %d %d\n", vardas, taskai, roundai, ilgiausiaSerija);
    }

    fclose(laikinasFailas);

    remove(TASKU_FAILAS);
    rename("laikinas.txt", TASKU_FAILAS);
}

// Funkcija išvesti lyderių lentą
void spausdintiLyderiuLenta() {
    FILE *failas = fopen(TASKU_FAILAS, "r");
    if (!failas) 
    {
        printf("Lyderių lentos nepavyko sukurti.\n");
        return;
    }

    Lyderis lyderiai[100];
    int zaidejuKiekis = 0;

    char line[256];
    while (fgets(line, sizeof(line), failas)) 
    {
        if (sscanf(line, "%s %d %d %d", lyderiai[zaidejuKiekis].vardas, &lyderiai[zaidejuKiekis].taskai, &lyderiai[zaidejuKiekis].suzaistiRoundai, &lyderiai[zaidejuKiekis].ilgiausiaSerija) == 4) 
        {
            zaidejuKiekis++;
        }
    }
    fclose(failas);

    for (int i = 0; i < zaidejuKiekis - 1; i++) {
        for (int j = i + 1; j < zaidejuKiekis; j++) {
            if (lyderiai[i].taskai < lyderiai[j].taskai ||
                (lyderiai[i].taskai == lyderiai[j].taskai && lyderiai[i].ilgiausiaSerija < lyderiai[j].ilgiausiaSerija)) {
                Lyderis temp = lyderiai[i];
                lyderiai[i] = lyderiai[j];
                lyderiai[j] = temp;
            }
        }
    }

    printf(SPALVA_MELYNA"|******************************************************************************************|\n", SPALVA_PRADINE);
    printf(SPALVA_GELTONA "                     Lyderių lenta\n", SPALVA_PRADINE);
    printf(SPALVA_MELYNA "|*****************************************************************************************|\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "Vieta | Vardas:              | Taškai:    | Sužaisti raundai:    | Ilgiausia serija:\n", SPALVA_PRADINE);
    printf(SPALVA_MELYNA"|******************************************************************************************|\n", SPALVA_PRADINE);
    for (int i = 0; i < zaidejuKiekis && i < 10; i++) // // TOP 10
    { 
        printf(SPALVA_GELTONA"%-6d| %-20s | %-10d | %-6d               | %d \n", i + 1, lyderiai[i].vardas, lyderiai[i].taskai, lyderiai[i].suzaistiRoundai, lyderiai[i].ilgiausiaSerija, SPALVA_PRADINE);
    }
    printf(SPALVA_MELYNA"|******************************************************************************************|\n", SPALVA_PRADINE);
    printf(SPALVA_GELTONA "                         Grįžkite paspausdami Enter.\n" SPALVA_PRADINE);
    printf(SPALVA_MELYNA "|*****************************************************************************************|\n" SPALVA_PRADINE);
    while (_getch() != '\r')
    {
    
    }
}
