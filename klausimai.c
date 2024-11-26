#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "klausimai.h"


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
    printf("                Klausimas: %s\n", klausimai[atsitiktinis].klausimas);

     return &klausimai[atsitiktinis]; 
}

// Funkcija atlaisvinti atminčiai
void atlaisvintiAtminti(Klausimas *klausimai)
{
    free(klausimai);
}

// Funkcija pakeisti "?" į įvestą žaidėjo operaciją
void pakeistiZenklaIrPridetiTaskus(char *klausimas, char *teisingiZenklai, int *zaidejoTaskai)
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
        printf("                Įveskite %d ženklus (+, -, /, *): \n", zenkluSkaicius);
        printf("|***************************************************************|\n");


        for(int i = 0; i < zenkluSkaicius; i++)
        {
            char ivestasZenklas;
            int tinkamas = 0;

            do
            {
                printf("Pasirinkite %d ženklą: ", i + 1);
                scanf(" %c", &ivestasZenklas);
                while (getchar() != '\n');

                if(ivestasZenklas == '+' || ivestasZenklas == '-' || ivestasZenklas == '*' || ivestasZenklas == '/')
                {
                    ivestiZenklai[i] = ivestasZenklas;
                    tinkamas = 1;
                }
                else
                {
                    printf("|***************************************************************|\n");
                    printf("\nKlaida: Įvestas ženklas neegzistuoja. Pasirinkite ženklą. (+, -, *, /)\n");
                    printf("|***************************************************************|\n");
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

        printf("|***************************************************************|\n");
        printf("Jūsų įvesti ženklai: %s\n", klausimas);


        while(galutinisAtsakymas != 1)
        {
            char atsakymas[10];
            printf("Ar tai Jūsų galutinis atsakymas? (Taip/Ne): \n");
            printf("|***************************************************************|\n");
            scanf("%9s", atsakymas);
            while (getchar() != '\n');
            
            for(int i = 0; i < 4; i++)
            {
                atsakymas[i] = toupper(atsakymas[i]);
            }
            if(strcmp(atsakymas, "TAIP") == 0)
            {
                teisingiZenklai = strtok(teisingiZenklai, " \t\r\n");

                int gautiTaskai = patikrintiAtsakymus(ivestiZenklai, teisingiZenklai);
                printf("Jūs gavote %d taškų.\n", gautiTaskai);
                *zaidejoTaskai += gautiTaskai;

                galutinisAtsakymas = 1;
                
                break;
            }
            else if(strcmp(atsakymas, "NE") == 0)
            {
                printf("|***************************************************************|\n");
                printf("                Pakartokite ženklų įvedimą.\n");
                // Atstatomas klausimas su '?'
                strcpy(klausimas, pradinisKlausimas);
                printf("                Klausimas: %s\n", klausimas);
                break;
            }
            else
            {
                printf("|***************************************************************|\n");
                printf("Klaida: Atsakymas turi būti 'Taip' arba 'Ne'. Bandykite dar kartą.\n");
                printf("|***************************************************************|\n");
            }
            
        }

    }

    free(ivestiZenklai);
    free(pradinisKlausimas);
}

// Funkcija patikrinti atsakymą ir pridėti taškus
int patikrintiAtsakymus(char *ivestiZenklai, char *teisingiZenklai) 
{

    if (strcmp(ivestiZenklai, teisingiZenklai) == 0) 
    {
        printf("Teisingai! Jūsų atsakymas: %s\n", ivestiZenklai);
        return 10; // Pridedami taškai
    } 
    else 
    {
        printf("Neteisingai. Teisingas atsakymas: %s, Jūsų atsakymas: %s\n", teisingiZenklai, ivestiZenklai);
        return -5; // Atimami taškai
    }
}

