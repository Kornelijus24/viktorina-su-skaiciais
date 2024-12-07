#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "klausimai.h"
#include "spalvos.h"
#include "lygiai.h"


// Funkcija užkrauti klausimus iš failo 
Klausimas *uzkrautiKlausimusIrAtsakymus(const char *failoVardas, int *skaiciuotiKlausimus)
{
    FILE *failas = fopen(failoVardas, "r");
    if (!failas)
    {
        perror("Klaida atidarant failą");
        return NULL;
    }
    
    char eilute[256];
    int klausimuKiekis = 10;
    *skaiciuotiKlausimus = 0;

    Klausimas *klausimai = (Klausimas *)malloc(sizeof(Klausimas) * klausimuKiekis);

    // Nuskaito klausimus ir dinamiškai padidiną masyvo dydį, jeigu klausimų kiekis viršija 10
    while(fgets(eilute, sizeof(eilute), failas))
    { 
        if(*skaiciuotiKlausimus >= klausimuKiekis)
        {
            klausimuKiekis *= 2;
            klausimai = (Klausimas *)realloc(klausimai, sizeof(Klausimas) * klausimuKiekis);
        }

        char *atsakymas = strchr(eilute, '|');
        if (atsakymas) {
            *atsakymas = '\0'; // Atskiriamas klausimas nuo teisingų ženklų
            atsakymas++;

            // Pašalinami nereikalingi tarpai
            eilute[strcspn(eilute, "\n")] = '\0';
            atsakymas[strcspn(atsakymas, "\n")] = '\0';

            // Išsaugomas klausimas ir teisingi ženklus
            strcpy(klausimai[*skaiciuotiKlausimus].klausimas, eilute);
            strcpy(klausimai[*skaiciuotiKlausimus].pradinisKlausimas, eilute);
            strcpy(klausimai[*skaiciuotiKlausimus].teisingiZenklai, atsakymas);
            (*skaiciuotiKlausimus)++;

        }
    }

    fclose(failas);
    return klausimai;

}

// Funkcija atsitiktinai pasirinkti klausimą ir jį atspausdinti
Klausimas *spausdintiAtsitiktiniKlausima(Klausimas *klausimai, int skaiciuotiKlausimus)
{
    if (skaiciuotiKlausimus == 0)
    {
        printf("Failas neturi jokių klausimų.\n");
        return NULL;
    }
    
    srand(time(NULL));

    int atsitiktinis = rand() % skaiciuotiKlausimus;
    printf(SPALVA_MELYNA "                Klausimas: %s\n", klausimai[atsitiktinis].klausimas, SPALVA_PRADINE);

     return &klausimai[atsitiktinis]; 
}

// Funkcija atlaisvinti atminčiai
void atlaisvintiAtminti(Klausimas *klausimai)
{
    free(klausimai);
}

// Funkcija pakeisti "?" į įvestą žaidėjo operaciją
void pakeistiZenklaIrPridetiTaskus(char *klausimas, char *teisingiZenklai, int *zaidejoTaskai, SunkumoLygis *pasirinktasLygis)
{
    int klausimoIlgis = strlen(klausimas);
    int zenkluSkaicius = 0;

    for(int i = 0; i < klausimoIlgis; i++)
    {
        if(klausimas[i] == '?')
        {
            zenkluSkaicius++;
        }
    }

    char *ivestiZenklai = (char *)malloc(sizeof(char) * (zenkluSkaicius + 1));
    ivestiZenklai[zenkluSkaicius] = '\0';
    int galutinisAtsakymas = 0;
    char *pradinisKlausimas = (char *)malloc(sizeof(char) * (klausimoIlgis + 1));
    strcpy(pradinisKlausimas, klausimas); // Nukopijuojamas pradinis klausimas su '?'

    while(!galutinisAtsakymas) // Kol žaidėjas nepatvirtina atsakymo
    {
        printf(SPALVA_ZALIA "                Įveskite %d ženklus (+, -, /, *): \n", zenkluSkaicius, SPALVA_PRADINE);
        printf(SPALVA_MELYNA "|***************************************************************|\n", SPALVA_PRADINE);


        for(int i = 0; i < zenkluSkaicius; i++)
        {
            char ivestasZenklas;
            int tinkamas = 0;

            do
            {
                printf(SPALVA_ZALIA "Pasirinkite %d ženklą: ", i + 1, SPALVA_PRADINE);
                scanf(" %c", &ivestasZenklas);
                while (getchar() != '\n');

                if(ivestasZenklas == '+' || ivestasZenklas == '-' || ivestasZenklas == '*' || ivestasZenklas == '/')
                {
                    ivestiZenklai[i] = ivestasZenklas;
                    tinkamas = 1;
                }
                else
                {
                    printf(SPALVA_MELYNA "|***************************************************************|\n", SPALVA_PRADINE);
                    printf(SPALVA_RAUSVA "\nKlaida: Įvestas ženklas neegzistuoja. Pasirinkite ženklą. (+, -, *, /)\n", SPALVA_PRADINE);
                    printf(SPALVA_MELYNA "|***************************************************************|\n", SPALVA_PRADINE);
                }
                    
            } while(!tinkamas);
        }
        ivestiZenklai[zenkluSkaicius] = '\0';

        // Pakeičiame `?` įvestais ženklais
        int zenkloKeitimas = 0;
        for(int i = 0; i < klausimoIlgis; i++)
        {
            if(klausimas[i] == '?')
            {
                klausimas[i] = ivestiZenklai[zenkloKeitimas];
                zenkloKeitimas++;
            }
        }

        printf(SPALVA_MELYNA "|***************************************************************|\n", SPALVA_PRADINE);
        printf(SPALVA_ZALIA"Jūsų įvesti ženklai: %s\n", klausimas, SPALVA_PRADINE);


        while(galutinisAtsakymas != 1)
        {
            char atsakymas[10];
            printf(SPALVA_ZALIA "Ar tai Jūsų galutinis atsakymas? (Taip/Ne): \n", SPALVA_PRADINE);
            printf(SPALVA_MELYNA "|***************************************************************|\n", SPALVA_PRADINE);
            scanf("%9s", atsakymas);
            while (getchar() != '\n');
            
            for(int i = 0; i < 4; i++)
            {
                atsakymas[i] = toupper(atsakymas[i]);
            }
            if(strcmp(atsakymas, "TAIP") == 0)
            {
                teisingiZenklai = strtok(teisingiZenklai, " \t\r\n");

                int gautiTaskai = patikrintiAtsakymus(ivestiZenklai, teisingiZenklai, pasirinktasLygis);
                *zaidejoTaskai += gautiTaskai;

                galutinisAtsakymas = 1;
                
                break;
            }
            else if(strcmp(atsakymas, "NE") == 0)
            {
                printf(SPALVA_MELYNA "|***************************************************************|\n", SPALVA_PRADINE);
                printf(SPALVA_GELTONA "                Pakartokite ženklų įvedimą.\n", SPALVA_PRADINE);
                // Atstatomas klausimas su '?'
                strcpy(klausimas, pradinisKlausimas);
                printf(SPALVA_MELYNA "                Klausimas: %s\n", klausimas, SPALVA_PRADINE);
                break;
            }
            else
            {
                printf(SPALVA_MELYNA "|***************************************************************|\n", SPALVA_PRADINE);
                printf(SPALVA_RAUSVA "Klaida: Atsakymas turi būti 'Taip' arba 'Ne'. Bandykite dar kartą.\n", SPALVA_PRADINE);
                printf(SPALVA_MELYNA "|***************************************************************|\n", SPALVA_PRADINE);
            }
            
        }

    }

    free(ivestiZenklai);
    free(pradinisKlausimas);
}

// Funkcija patikrinti atsakymą ir pridėti taškus
int patikrintiAtsakymus(char *ivestiZenklai, char *teisingiZenklai, SunkumoLygis *pasirinktasLygis) 
{
    int teisingiTaskai = 0;
    int neteisingiTaskai = 0;

    size_t ilgis = strlen(teisingiZenklai);

    for (size_t i = 0; i < ilgis; i++) 
    {
        if (ivestiZenklai[i] == teisingiZenklai[i]) 
        {
            teisingiTaskai++;
        } 
        else 
        {
            neteisingiTaskai++;
        }
    }

    int taskai = (teisingiTaskai * 5 - neteisingiTaskai * 2);

    // Pridėti taškus priklausomai nuo sunkumo
    int sunkumas;

    if (strcmp(pasirinktasLygis->lygioPavadinimas, "Lengvas") == 0)
        sunkumas = 1;
    else if (strcmp(pasirinktasLygis->lygioPavadinimas, "Vidutinis") == 0)
        sunkumas = 2;
    else if (strcmp(pasirinktasLygis->lygioPavadinimas, "Sunkus") == 0)
        sunkumas = 3;
    else if (strcmp(pasirinktasLygis->lygioPavadinimas, "Neįmanomas") == 0)
        sunkumas = 5;
    else
        sunkumas = 1;

    taskai *= sunkumas;

    if (taskai > 0) 
    {
        printf(SPALVA_ZALIA "Teisingai atspėjote ženklą!\n Jūsų atsakymas: %s\n Teisingas atsakymas: %s\n", ivestiZenklai, teisingiZenklai, SPALVA_PRADINE);
        printf(SPALVA_ZALIA "Už šį klausimą gavote %d taškų (Sunkumo lygis: %s).\n", taskai, pasirinktasLygis->lygioPavadinimas, SPALVA_PRADINE);
    } 
    else 
    {
        printf(SPALVA_RAUSVA "Neteisingai. Teisingas atsakymas: %s, Jūsų atsakymas: %s\n", teisingiZenklai, ivestiZenklai, SPALVA_PRADINE);
        printf(SPALVA_RAUSVA "Praradote %d taškų (Sunkumo lygis: %s).\n", -taskai, pasirinktasLygis->lygioPavadinimas, SPALVA_PRADINE);
    }

    return taskai;
}


