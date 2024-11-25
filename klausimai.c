#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Funkcija užkrauti klausimus iš failo 
char **uzkrautiKlausimus(const char *failoVardas, int *skaiciuotiKlausimus)
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

    char **klausimai = (char **)malloc(sizeof(char *) * klausimuKiekis);

    // Nuskaito klausimus ir dinamiškai padidiną masyvo dydį, jeigu klausimų kiekis viršija 10
    while(fgets(eilute, sizeof(eilute), failas))
    { 
        if(*skaiciuotiKlausimus >= klausimuKiekis)
        {
            klausimuKiekis *= 2;
            klausimai = (char **)realloc(klausimai, sizeof(char *) * klausimuKiekis);
        }
        eilute[strcspn(eilute, "\n")] = 0; // Pašalina naujos eilutės simbolį
        klausimai[*skaiciuotiKlausimus] = strdup(eilute); // Dubliuoja eilutę, kuri nuskaitoma, kad neoverwritintu klausimų
        (*skaiciuotiKlausimus)++;
    }

    fclose(failas);
    return klausimai;

}

// Funkcija atsitiktinai pasirinkti klausimą ir jį atspausdinti
char *spausdintiAtsitiktiniKlausima(char **klausimai, int skaiciuotiKlausimus)
{
    if (skaiciuotiKlausimus == 0)
    {
        printf("Failas neturi jokių klausimų.\n");
        return NULL;
    }
    
    srand(time(NULL));

    int atsitiktinis = rand() % skaiciuotiKlausimus;
    printf("                Klausimas: %s\n", klausimai[atsitiktinis]);

     return klausimai[atsitiktinis]; 
}

// Funkcija atlaisvinti atminčiai
void atlaisvintiAtminti(char **klausimai, int skaiciuotiKlausimus)
{
    for (int i = 0; i < skaiciuotiKlausimus; i++)
    {
        free(klausimai[i]);
    }
    free(klausimai);
}

// Funkcija pakeisti "?" į įvestą žaidėjo operaciją
void pakeistiZenkla(char *klausimas)
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

    char *zenklai = (char *)malloc(sizeof(char) * zenkluSkaicius);
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

                if(ivestasZenklas == '+' || ivestasZenklas == '-' || ivestasZenklas == '*' || ivestasZenklas == '/')
                {
                    zenklai[i] = ivestasZenklas;
                    tinkamas = 1;
                }
                else
                {
                    printf("|***************************************************************|\n");
                    printf("\nKlaida: Įvestas ženklas neegzistuoja. Pasirinkite ženklą. (+, -, *, /)\n");
                    printf("|***************************************************************|\n");
                }

                while (getchar() != '\n'); // Išvalomas buffer
                    
            } while(!tinkamas);
        }

        // Pakeičiame `?` įvestais ženklais
        int zenkloKeitimas = 0;
        for(int i = 0; i < klausimoIlgis; i++)
        {
            if(klausimas[i] == '?')
            {
                klausimas[i] = zenklai[zenkloKeitimas];
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
            
            for(int i = 0; i < 4; i++)
            {
                atsakymas[i] = toupper(atsakymas[i]);
            }
            if(strcmp(atsakymas, "TAIP") == 0)
            {
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
                while (getchar() != '\n'); // Išvalomas buffer
            }
            
        }

    }
    
    free(zenklai);
}