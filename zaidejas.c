#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "zaidejas.h"
#include "spalvos.h"

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

// Funkcija išvesti lyderių lentą
void spausdintiLyderiuLenta() {
    FILE *failas = fopen(TASKU_FAILAS, "r");
    if (!failas) {
        printf("Lyderių lentos nepavyko sukurti.\n");
        return;
    }

    Lyderis lyderiai[100];
    int zaidejuKiekis = 0;

    char line[256];
    while (fgets(line, sizeof(line), failas)) {
        if (sscanf(line, "%s %d %d", lyderiai[zaidejuKiekis].vardas, &lyderiai[zaidejuKiekis].taskai, &lyderiai[zaidejuKiekis].suzaistiRoundai) == 3) {
            zaidejuKiekis++;
        }
    }
    fclose(failas);

    for (int i = 0; i < zaidejuKiekis - 1; i++) {
        for (int j = i + 1; j < zaidejuKiekis; j++) {
            if (lyderiai[i].taskai < lyderiai[j].taskai ||
                (lyderiai[i].taskai == lyderiai[j].taskai && lyderiai[i].suzaistiRoundai < lyderiai[j].suzaistiRoundai)) {
                Lyderis temp = lyderiai[i];
                lyderiai[i] = lyderiai[j];
                lyderiai[j] = temp;
            }
        }
    }

    printf(SPALVA_MELYNA"|***************************************************************|\n", SPALVA_PRADINE);
    printf(SPALVA_GELTONA "                     Lyderių lenta\n", SPALVA_PRADINE);
    printf(SPALVA_MELYNA "|***************************************************************|\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "Vieta | Vardas:              | Taškai:  | Sužaisti raundai:\n", SPALVA_PRADINE);
    printf(SPALVA_MELYNA"|***************************************************************|\n", SPALVA_PRADINE);
    for (int i = 0; i < zaidejuKiekis && i < 10; i++) { // TOP 10
        printf(SPALVA_GELTONA"%-6d| %-20s | %-10d | %-6d\n", i + 1, lyderiai[i].vardas, lyderiai[i].taskai, lyderiai[i].suzaistiRoundai, SPALVA_PRADINE);
    }
    printf(SPALVA_MELYNA"|***************************************************************|\n", SPALVA_PRADINE);
    printf(SPALVA_GELTONA "  Grįžkite paspausdami Enter.\n" SPALVA_PRADINE);
    printf(SPALVA_MELYNA "|***************************************************************|\n" SPALVA_PRADINE);
    while (_getch() != '\r')
    {
    
    }
}
