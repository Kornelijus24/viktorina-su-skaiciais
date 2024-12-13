#ifndef KLAUSIMAI_H
#define KLAUSIMAI_H

#include "lygiai.h"

typedef struct 
{
    char klausimas[256];
    char teisingiZenklai[20];
    char pradinisKlausimas[256];

} Klausimas;

// Funkcijų prototipai
Klausimas *uzkrautiKlausimusIrAtsakymus(const char *failoVardas, int *skaiciuotiKlausimus);
Klausimas *spausdintiAtsitiktiniKlausima(Klausimas *klausimai, int skaiciuotiKlausimus);
void atlaisvintiAtminti(Klausimas *klausimai);
void pakeistiZenklaIrPridetiTaskus(char *klausimas, char *teisingiZenklai, int *zaidejoTaskai, SunkumoLygis *pasirinktasLygis, int *ilgiausiaSerija);
void neimanomasLygis(char *klausimas, char *teisingiZenklai, int *zaidejoTaskai, SunkumoLygis *pasirinktasLygis, int *ilgiausiaSerija); 
int patikrintiAtsakymus(char *ivestiZenklai, char *teisingiZenklai, SunkumoLygis *pasirinktasLygis);

#endif