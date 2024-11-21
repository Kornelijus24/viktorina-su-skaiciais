#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
void spausdintiAtsitiktiniKlausima(char **klausimai, int skaiciuotiKlausimus)
{
    if (skaiciuotiKlausimus == 0)
    {
        printf("Failas neturi jokių klausimų.\n");
        return;
    }
    
    srand(time(NULL));

    int atsitiktinis = rand() % skaiciuotiKlausimus;
    printf("Klausimas: %s\n", klausimai[atsitiktinis]);
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