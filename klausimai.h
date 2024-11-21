#ifndef KLAUSIMAI_H
#define KLAUSIMAI_H

// Funkcijų prototipai
char **uzkrautiKlausimus(const char *failoVardas, int *skaiciuotiKlausimus);
void spausdintiAtsitiktiniKlausima(char **klausimai, int skaiciuotiKlausimus);
void atlaisvintiAtminti(char **klausimai, int skaiciuotiKlausimus);

#endif