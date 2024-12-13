#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
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

// Funkcija pakeisti ženklus ir pridėti taškus
void pakeistiZenklaIrPridetiTaskus(char *klausimas, char *teisingiZenklai, int *zaidejoTaskai, SunkumoLygis *pasirinktasLygis, int *ilgiausiaSerija)
{
    // Apskaičiuojamas klausimo ilgis
    int klausimoIlgis = strlen(klausimas);
    int zenkluSkaicius = 0;

    // Suskaičiuojami visi '?' klausime
    for(int i = 0; i < klausimoIlgis; i++)
    {
        if(klausimas[i] == '?')
        {
            zenkluSkaicius++;
        }
    }

    // Sukuriama dinaminė atmintis įvestiems ženklams saugoti
    char *ivestiZenklai = (char *)malloc(sizeof(char) * (zenkluSkaicius + 1));
    ivestiZenklai[zenkluSkaicius] = '\0';

    int galutinisAtsakymas = 0;

    // Nukopijuojamas pradinis klausimas
    char *pradinisKlausimas = (char *)malloc(sizeof(char) * (klausimoIlgis + 1));
    strcpy(pradinisKlausimas, klausimas);

    // Kol žaidėjas nepatvirtina atsakymo
    while(!galutinisAtsakymas) 
    {
        printf(SPALVA_ZALIA "                Įveskite %d ženklus (+, -, /, *): \n", zenkluSkaicius, SPALVA_PRADINE);
        printf(SPALVA_MELYNA "|***************************************************************|\n", SPALVA_PRADINE);

        // Ženklų įvedimas
        for(int i = 0; i < zenkluSkaicius; i++)
        {
            char ivestasZenklas;
            int tinkamas = 0;

            // Žaidėjas įveda tinkamą ženklą
            do
            {
                printf(SPALVA_ZALIA "Pasirinkite %d ženklą: ", i + 1, SPALVA_PRADINE);
                scanf(" %c", &ivestasZenklas);
                while (getchar() != '\n');
                
                // Tikrinama, ar įvestas ženklas yra vienas iš leistinų
                if(ivestasZenklas == '+' || ivestasZenklas == '-' || ivestasZenklas == '*' || ivestasZenklas == '/')
                {
                    ivestiZenklai[i] = ivestasZenklas; // Išsaugomas ženklas masyve
                    tinkamas = 1; // Pažymima, kad įvestas ženklas yra tinkamas
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

        // Patikrinama, ar tai galutinis atsakymas
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

            // Jei atsakymas "TAIP", patikrinamas atsakymas ir atnaujinami taškai
            if(strcmp(atsakymas, "TAIP") == 0)
            {
                // Pašalinami nereikalingi tarpai iš teisingų ženklų
                teisingiZenklai = strtok(teisingiZenklai, " \t\r\n");

                int gautiTaskai = patikrintiAtsakymus(ivestiZenklai, teisingiZenklai, pasirinktasLygis);

                if(gautiTaskai > 0)
                {
                    *ilgiausiaSerija += 1; // Skaičiuojami laimėti roundai iš eilės
                    printf(SPALVA_ZALIA "Teisingai atspėjote ženklą!\n Jūsų atsakymas: %s\n Teisingas atsakymas: %s\n", ivestiZenklai, teisingiZenklai, SPALVA_PRADINE);
                    printf(SPALVA_ZALIA "Už šį klausimą gavote %d taškų (Sunkumo lygis: %s).\n", gautiTaskai, pasirinktasLygis->lygioPavadinimas, SPALVA_PRADINE);
    
                }
                else 
                {
                    *ilgiausiaSerija = 0; // Atstatomi laimėjimai iš eilės
                    printf(SPALVA_RAUSVA "Neteisingai. Teisingas atsakymas: %s, Jūsų atsakymas: %s\n", teisingiZenklai, ivestiZenklai, SPALVA_PRADINE);
                    printf(SPALVA_RAUSVA "Praradote %d taškų (Sunkumo lygis: %s).\n", -gautiTaskai, pasirinktasLygis->lygioPavadinimas, SPALVA_PRADINE);
                }

                *zaidejoTaskai += gautiTaskai;

                galutinisAtsakymas = 1;
                
                break;
            }
            // Jei atsakymas "NE", leidžiama pakartoti įvestį
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

    // Išlaisvinama dinaminė atmintis
    free(ivestiZenklai);
    free(pradinisKlausimas);
}

// Funkcija skirta neįmanomam lygiui
void neimanomasLygis(char *klausimas, char *teisingiZenklai, int *zaidejoTaskai, SunkumoLygis *pasirinktasLygis, int *ilgiausiaSerija) 
{
    // Suskaičiuojamas klausimo ilgis
    int klausimoIlgis = strlen(klausimas);
    int zenkluSkaicius = 0;

    // Apskaičiuojama, kiek ženklų reikia pakeisti
    for (int i = 0; i < klausimoIlgis; i++) 
    {
        if (klausimas[i] == '?') 
        {
            zenkluSkaicius++;
        }
    }

    // Dinaminė atmintis įvestiems ženklams saugoti
    char *ivestiZenklai = (char *)malloc(sizeof(char) * (zenkluSkaicius + 1));
    ivestiZenklai[zenkluSkaicius] = '\0';

    int laikmatis = 30; // 30 sekundžių atsakyti
    time_t pradziosLaikas = time(NULL); // Pradedamas skaičiuoti laikas

    printf(SPALVA_RAUSVA "NEĮMANOMAS LYGIS: Įveskite %d ženklus (+, -, /, *):\n", zenkluSkaicius, SPALVA_PRADINE);
    printf(SPALVA_MELYNA "|***************************************************************|\n", SPALVA_PRADINE);

    // Ciklas, skirtas ženklų įvedimui
    for (int i = 0; i < zenkluSkaicius; i++) 
    {
        char ivestasZenklas;
        int tinkamas = 0;

        do 
        {
            // Apskaičiuojamas likęs laikas
            int likoLaiko = laikmatis - (int)(time(NULL) - pradziosLaikas);

            // Patikrinama ar nesibaigė laikas
            if (likoLaiko <= 0) 
            {
                // Jei laikas baigėsi, žaidėjas praranda taškus ir roundas baigiamas
                printf(SPALVA_RAUSVA "\nLaikas baigėsi! Nespėjote atsakyti. Prarandate 15 taškų.\n" SPALVA_PRADINE);
                *zaidejoTaskai -= 15;
                *ilgiausiaSerija = 0;
                free(ivestiZenklai);
                return;
            }

            printf(SPALVA_ZALIA "\rLaiko liko: %d sekundžių. Pasirinkite %d ženklą: ", likoLaiko, i + 1, SPALVA_PRADINE);
            fflush(stdout);

            scanf(" %c", &ivestasZenklas);
            while (getchar() != '\n');

            // Patikrinama, ar įvestas ženklas yra tinkamas
            if (ivestasZenklas == '+' || ivestasZenklas == '-' || ivestasZenklas == '*' || ivestasZenklas == '/') 
            {
                ivestiZenklai[i] = ivestasZenklas;
                tinkamas = 1;
            } 
            else 
            {
                printf(SPALVA_RAUSVA "\nKlaida: Įvestas ženklas neegzistuoja. Pasirinkite ženklą. (+, -, *, /)\n" SPALVA_PRADINE);
            }
        } while (!tinkamas);
    }

    ivestiZenklai[zenkluSkaicius] = '\0';

    // Pakeisti '?' į įrašytus ženklus
    for (int i = 0, j = 0; i < klausimoIlgis; i++) 
    {
        if (klausimas[i] == '?') 
        {
            klausimas[i] = ivestiZenklai[j++];
        }
    }

    printf(SPALVA_ZALIA "\nGalutinis atsakymas užfiksuotas automatiškai dėl neįmanomo lygio.\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "Jūsų atsakymas: %s\n", klausimas, SPALVA_PRADINE);

    // Patikrinamas atsakymas
    teisingiZenklai = strtok(teisingiZenklai, " \t\r\n");
    int gautiTaskai = patikrintiAtsakymus(ivestiZenklai, teisingiZenklai, pasirinktasLygis);

    if (gautiTaskai > 0) 
    {
        *ilgiausiaSerija += 1;
        printf(SPALVA_ZALIA "Teisingai! Jūsų atsakymas: %s\n", ivestiZenklai, SPALVA_PRADINE);
        printf(SPALVA_ZALIA "Už šį klausimą gavote %d taškų (Sunkumo lygis: %s).\n", gautiTaskai, pasirinktasLygis->lygioPavadinimas, SPALVA_PRADINE);
    } 
    else 
    {
        *ilgiausiaSerija = 0;
        printf(SPALVA_RAUSVA "Neteisingai. Teisingas atsakymas: %s, Jūsų atsakymas: %s\n", teisingiZenklai, ivestiZenklai, SPALVA_PRADINE);
        printf(SPALVA_RAUSVA "Praradote %d taškų (Sunkumo lygis: %s).\n", -gautiTaskai, pasirinktasLygis->lygioPavadinimas, SPALVA_PRADINE);
    }

    // Pridedami žaidėjo gauti taškai
    *zaidejoTaskai += gautiTaskai;

    // Išlaisvinama dinaminė atmintis
    free(ivestiZenklai);
}


// Funkcija patikrinti atsakymą ir pridėti taškus
int patikrintiAtsakymus(char *ivestiZenklai, char *teisingiZenklai, SunkumoLygis *pasirinktasLygis) 
{
    int teisingiTaskai = 0;
    int neteisingiTaskai = 0;

    int ilgis = strlen(teisingiZenklai);

    for (int i = 0; i < ilgis; i++) 
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

    // Pridedami ir atimami taškai priklausomai nuo sunkumo ir atsakytų ženklų
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

    return taskai;
}


