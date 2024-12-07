#ifndef PASIEKIMAI_H
#define PASIEKIMAI_H

#define PASIEKIMU_SKAICIUS 13

typedef struct {
    char pavadinimas[50];
    char aprasymas[100];
    int salyga;          // sąlyga, kuri turi būti įvykdyta, kad gauti pasiekima (sužaisti roundai, surinkti taškai)
    int arIvykdytas;     // 1 jei įvykdytas, 0 jei ne
    int tipas;           // 0 taškam, 1 roundam
} Pasiekimas;

// Funkcijų prototipai
void uzkrautiPasiekimus();
void patikrintiPasiekimusPoZaidimo(int zaidejoTaskai, int suzaistiRoundai);
void patikrintiPasiekimusPrisijungus(int zaidejoTaskai, int suzaistiRoundai);
void parodytiPasiekimus();

#endif
