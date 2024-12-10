#ifndef PASIEKIMAI_H
#define PASIEKIMAI_H

#define PASIEKIMU_SKAICIUS 19

typedef struct {
    char pavadinimas[50];
    char aprasymas[100];
    int salyga;          // sąlyga, kuri turi būti įvykdyta, kad gauti pasiekima (sužaisti roundai, surinkti taškai)
    int arIvykdytas;     // 1 jei įvykdytas, 0 jei ne
    int tipas;           // 0 taškam, 1 roundam, 2 laimėtiem roundam iš eilės
} Pasiekimas;

// Funkcijų prototipai
void uzkrautiPasiekimus();
void patikrintiPasiekimusPoZaidimo(int zaidejoTaskai, int suzaistiRoundai, int laimetiRoundai);
void patikrintiPasiekimusPrisijungus(int zaidejoTaskai, int suzaistiRoundai, int laimetiRoundai);
void parodytiPasiekimus();

#endif
