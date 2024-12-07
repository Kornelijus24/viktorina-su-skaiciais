#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // Lietuviškom raidėm
#include <string.h>
#include <ctype.h>
#include "klausimai.h"
#include "zaidejas.h"
#include "lygiai.h"
#include "spalvos.h"
#include "pasiekimai.h"


int main() 
{
    
    system("chcp 65001 > nul");
    setlocale(LC_ALL, ".UTF-8");

    int skaiciuotiKlausimus;
    int zaidejoTaskai = 0, suzaistiRoundai = 0;
    char zaidejoVardas[VARDO_ILGIS];

    // Užkrauti pasiekimus
    uzkrautiPasiekimus();


    parodytiPradziosEkrana();
    scanf("%s", zaidejoVardas);

    skaitytiTaskusIrRoundus(zaidejoVardas, &zaidejoTaskai, &suzaistiRoundai);
    patikrintiPasiekimusPrisijungus(zaidejoTaskai, suzaistiRoundai);
    

    while (1) 
    {
        int pasirinkimas = pagrindinisMeniu(zaidejoTaskai, zaidejoVardas); // Rodo pagrindinį meniu ir leidžia pasirinkti

        if (pasirinkimas == 1)
        {
            SunkumoLygis *lygiai = gautiLygius();
            int pasirinktasLygis = pasirinktiSunkumoLygi(zaidejoTaskai, lygiai);
            
            system("cls"); // Išvalo ekraną

            const char *failoVardas = lygiai[pasirinktasLygis].failoVardas;

            Klausimas *klausimai = uzkrautiKlausimusIrAtsakymus(failoVardas, &skaiciuotiKlausimus);

            int zaidimasVyksta = 1;

            while(zaidimasVyksta)
            {

                // Atspausdina atsitiktinį klausimą
                Klausimas *pasirinktasKlausimas = spausdintiAtsitiktiniKlausima(klausimai, skaiciuotiKlausimus);

                // Pakeičia '?' į įvestus ženklus ir patikrina atsakymą
                pakeistiZenklaIrPridetiTaskus(pasirinktasKlausimas->klausimas, pasirinktasKlausimas->teisingiZenklai, &zaidejoTaskai, &lygiai[pasirinktasLygis]);
                strcpy(pasirinktasKlausimas->klausimas, pasirinktasKlausimas->pradinisKlausimas); // Jeigu klausimas pasikartotų, jis grąžinamas į pradinę reikšmę su '?'

                // Pridedamas sužaistas roundas
                suzaistiRoundai++;

                char atsakymas[10];
                int tinkamasAtsakymas = 0;

                while(!tinkamasAtsakymas)
                {
                    printf(SPALVA_MELYNA "|***************************************************************|\n" SPALVA_PRADINE);
                    printf(SPALVA_GELTONA"Ar norite tęsti žaidimą? (Taip/Ne): \n", SPALVA_PRADINE);
                    printf(SPALVA_MELYNA "|***************************************************************|\n" SPALVA_PRADINE);
                    scanf("%9s", atsakymas);

                    for (int i = 0; i < 4; i++)
                    {
                        atsakymas[i] = toupper(atsakymas[i]);
                    }

                    if (strcmp(atsakymas, "TAIP") == 0)
                    {
                        tinkamasAtsakymas = 1; // Tinkama įvestis, tęsiame žaidimą
                        system("cls"); // Išvalo ekraną
                    }
                    else if (strcmp(atsakymas, "NE") == 0)
                    {
                        tinkamasAtsakymas = 1; // Tinkama įvestis, uždarome žaidimą
                        zaidimasVyksta = 0;
                        printf(SPALVA_MELYNA "Grįžtama į pagrindinį meniu...\n" SPALVA_PRADINE);
                        break;

                    }
                    else
                    {   
                        printf(SPALVA_MELYNA "|***************************************************************|\n" SPALVA_PRADINE);
                        printf(SPALVA_RAUSVA "Klaida: Atsakymas turi būti 'Taip' arba 'Ne'. Bandykite dar kartą.\n" SPALVA_PRADINE);
                        printf(SPALVA_MELYNA "|***************************************************************|\n" SPALVA_PRADINE);
                        while (getchar() != '\n'); // Išvalomas buffer
                    }
                }
            }

            // Įrašo žaidėjo surinktus taškus į failą
            irasytiTaskusIrRoundus(zaidejoVardas, zaidejoTaskai, suzaistiRoundai);
            
            // Patikrina žaidėjo pasiekimus
            patikrintiPasiekimusPoZaidimo(zaidejoTaskai, suzaistiRoundai);
        }

        if (pasirinkimas == 2)
        {
            ;
        }
        
        if (pasirinkimas == 3)
        {
            parodytiPasiekimus();
        }

        if (pasirinkimas == 4) 
        {
            printf(SPALVA_MELYNA "Ar tikrai norite išeiti? (Taip/Ne): " SPALVA_PRADINE);

            char atsakymas[10];
                scanf("%9s", atsakymas);

                for (int i = 0; i < 4; i++) 
                {
                    atsakymas[i] = toupper(atsakymas[i]);
                }
                if (strcmp(atsakymas, "TAIP") == 0) 
                {
                    printf(SPALVA_RAUSVA "Ačiū, kad žaidėte! Žaidimas uždaromas...\n" SPALVA_PRADINE);
                    return 0;
                } 
                else if (strcmp(atsakymas, "NE") == 0) 
                {
                    printf(SPALVA_ZALIA "Grįžtama į pagrindinį meniu...\n" SPALVA_PRADINE);
                    continue;
                } 
                else 
                {
                    printf(SPALVA_RAUSVA "Neteisingas pasirinkimas. Grįžtama į pagrindinį meniu.\n" SPALVA_PRADINE);
                    continue;
                }
        } 
    }

    return 0;
}


