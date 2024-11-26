#ifndef KLAUSIMAI_H
#define KLAUSIMAI_H

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
void pakeistiZenklaIrPridetiTaskus(char *klausimas, char *teisingiZenklai, int *zaidejoTaskai);
int patikrintiAtsakymus(char *ivestiZenklai, char *teisingiZenklai);

#endif