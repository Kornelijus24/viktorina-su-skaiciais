#ifndef LYGIAI_H
#define LYGIAI_H

#define LYGIU_SK 4

// Sunkumo lygio struktūra
typedef struct {
    const char *failoVardas;       // Failo pavadinimas
    const char *lygioPavadinimas; // Lygio pavadinimas vartotojui
    int lygioTaskai;              // Minimalūs taškai lygio pasirinkimui
} SunkumoLygis;

// Funkcijų prototipai
SunkumoLygis *gautiLygius(void);
int pasirinktiSunkumoLygi(int zaidejoTaskai, SunkumoLygis *lygiai);

#endif
