#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
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
    int zaidejoTaskai = 0, suzaistiRoundai = 0, ilgiausiaSerija = 0;
    char zaidejoVardas[VARDO_ILGIS];

    
    // Parodo pradžios ekraną
    parodytiPradziosEkrana();

    // Žaidėjas įveda savo vardą
    scanf("%s", zaidejoVardas);

    // Nuskaito žaidėjo jau turimus taškus ir roundus(jeigu prieš tai jau žaidė)
    skaitytiTaskusIrRoundus(zaidejoVardas, &zaidejoTaskai, &suzaistiRoundai, &ilgiausiaSerija);
    ilgiausiaSerija = 0; // Prisijungus ilgiausia serija pradedama skaičiuoti nuo 0

    // Užkrauti pasiekimus
    uzkrautiPasiekimus();

    // Patikrina ar žaidėjas jau įvykdęs pasiekimus
    patikrintiPasiekimusPrisijungus(zaidejoTaskai, suzaistiRoundai, ilgiausiaSerija);
    
    while (1) 
    {
        // Rodo pagrindinį meniu ir leidžia žaidėjui pasirinkti
        int pasirinkimas = pagrindinisMeniu(zaidejoTaskai, zaidejoVardas);

        // Pradedamas žaidimas
        if (pasirinkimas == 1)
        {
            system("cls");
            printf(SPALVA_ZALIA "Pradedamas žaidimas...\n" SPALVA_PRADINE);

            // Pasirenkamas sunkumo lygis
            SunkumoLygis *lygiai = gautiLygius();
            int pasirinktasLygis = pasirinktiSunkumoLygi(zaidejoTaskai, lygiai);

            // Animacijos pradedant lygį
            if (strcmp(lygiai[pasirinktasLygis].lygioPavadinimas, "Lengvas") == 0) 
            {
                printf(SPALVA_ZALIA);
                parodytiLygioAnimacija("LENGVAS LYGIS");
                printf(SPALVA_PRADINE);
            }
            else if (strcmp(lygiai[pasirinktasLygis].lygioPavadinimas, "Vidutinis") == 0) 
            {
                printf(SPALVA_GELTONA);
                parodytiLygioAnimacija("VIDUTINIS LYGIS");
                printf(SPALVA_PRADINE);
            }
            else if (strcmp(lygiai[pasirinktasLygis].lygioPavadinimas, "Sunkus") == 0) 
            {
                printf(SPALVA_MELYNA);
                parodytiLygioAnimacija("SUNKUS LYGIS");
                printf(SPALVA_PRADINE);
            }
            else if (strcmp(lygiai[pasirinktasLygis].lygioPavadinimas, "Neįmanomas") == 0) 
            {
                printf(SPALVA_RAUSVA);
                parodytiLygioAnimacija("NEIMANOMAS LYGIS");
                printf(SPALVA_PRADINE);
            }
            
            system("cls"); // Išvalomas terminalo ekranas

            // Paimamas pasirinkto lygio failo vardas
            const char *failoVardas = lygiai[pasirinktasLygis].failoVardas;

            // Užkraunami klausimai ir atsakymai iš pasirinkto lygio
            Klausimas *klausimai = uzkrautiKlausimusIrAtsakymus(failoVardas, &skaiciuotiKlausimus);

            int zaidimasVyksta = 1;

            // Ciklas kol žaidėjas žaidžia
            while(zaidimasVyksta)
            {

                // Atspausdinamas atsitiktinis klausimas iš failo
                Klausimas *pasirinktasKlausimas = spausdintiAtsitiktiniKlausima(klausimai, skaiciuotiKlausimus);

                // Jeigu pasirinktas lygis "neįmanomas" taikome kitą žaidimo logiką
                if (strcmp(lygiai[pasirinktasLygis].lygioPavadinimas, "Neįmanomas") == 0)
                {
                    neimanomasLygis(pasirinktasKlausimas->klausimas, pasirinktasKlausimas->teisingiZenklai, &zaidejoTaskai, &lygiai[pasirinktasLygis], &ilgiausiaSerija);
                }
                else
                {
                    pakeistiZenklaIrPridetiTaskus(pasirinktasKlausimas->klausimas, pasirinktasKlausimas->teisingiZenklai, &zaidejoTaskai, &lygiai[pasirinktasLygis], &ilgiausiaSerija);
                }

                // Jeigu klausimas pasikartotų, jis grąžinamas į pradinę reikšmę su '?'
                strcpy(pasirinktasKlausimas->klausimas, pasirinktasKlausimas->pradinisKlausimas);

                // Pridedamas sužaistas roundas
                suzaistiRoundai++;

                char atsakymas[10];
                int tinkamasAtsakymas = 0;

                // Klausiama žaidėjo ar nori tęsti žaidimą
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

                    // Žaidimas tęsiamas (atspausdinamas kitas klausimas)
                    if (strcmp(atsakymas, "TAIP") == 0)
                    {
                        tinkamasAtsakymas = 1;
                        system("cls");
                    }

                    // Žaidėjas perkeliamas į pagrindinį meniu
                    else if (strcmp(atsakymas, "NE") == 0)
                    {
                        tinkamasAtsakymas = 1; // Tinkama įvestis, uždarome žaidimą
                        zaidimasVyksta = 0;
                        printf(SPALVA_MELYNA "Grįžtama į pagrindinį meniu...\n" SPALVA_PRADINE);
                        break;
                    }

                    // Žaidėjas įvedė neteisingai
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
            irasytiTaskusIrRoundus(zaidejoVardas, zaidejoTaskai, suzaistiRoundai, ilgiausiaSerija);
            
            // Patikrina žaidėjo pasiekimus
            patikrintiPasiekimusPoZaidimo(zaidejoTaskai, suzaistiRoundai, ilgiausiaSerija);
        }

        // Parodomi turimi žaidėjo taskai
        else if(pasirinkimas == 2)
        {
            system("cls");
            parodytiTaskus(zaidejoTaskai);
        }
        
        // Parodomi pasiekimai
        else if(pasirinkimas == 3)
        {
            system("cls");
            parodytiPasiekimus();
        }

        // Atspausdinama lyderių lenta
        else if(pasirinkimas == 4)
        {
            system("cls");
            spausdintiLyderiuLenta();
        }

        // Atspausdinamas pabaigos ekranas ir paklausiama dar kartą ar tikrai nori palikti žaidimą
        else if (pasirinkimas == 5) 
        {
            system("cls");
            parodytiPabaigosEkrana(zaidejoTaskai);

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


