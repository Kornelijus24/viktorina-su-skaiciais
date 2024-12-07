#ifndef SPALVOS_H
#define SPALVOS_H

// Spalvos
#define SPALVA_MELYNA "\033[1;34m"
#define SPALVA_ZALIA "\033[1;32m"
#define SPALVA_RAUSVA "\033[1;31m"
#define SPALVA_GELTONA "\033[1;33m"
#define SPALVA_PRADINE "\033[0m"

// ASCII  funkcijos
void parodytiPradziosEkrana();
void parodytiPabaigosEkrana(int zaidejoTaskai);
void parodytiPagrindiniMeniu(const char *zaidejoVardas);
void parodytiTaskus(int zaidejoTaskai);
int pagrindinisMeniu(int zaidejoTaskai, const char *zaidejoVardas);

#endif