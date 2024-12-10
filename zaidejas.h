#ifndef ZAIDEJAS_H
#define ZAIDEJAS_H

#define VARDO_ILGIS 20
#define TASKU_FAILAS "zaideju_taskai.txt"

typedef struct 
{
    char vardas[VARDO_ILGIS];
    int taskai;
    int suzaistiRoundai;
    int ilgiausiaSerija;
} Lyderis;


// Funkcijų prototipai
void skaitytiTaskusIrRoundus(const char *vardas, int *taskai, int *roundai, int *ilgiausiaSerija);
void irasytiTaskusIrRoundus(const char *vardas, int taskai, int roundai, int ilgiausiaSerija);
void spausdintiLyderiuLenta();

#endif