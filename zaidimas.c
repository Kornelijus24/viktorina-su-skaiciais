#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // Lietuviškom raidėm
#include <conio.h> // Žaidimo startui
#include "klausimai.h"

int main() {
    
    system("chcp 65001 > nul");
    setlocale(LC_ALL, ".UTF-8");


    const char *failoVardas = "lengvas_lygis.txt";
    int skaiciuotiKlausimus;

    printf("Sveiki atvykę į žaidimą.\n");
    printf("Paspauskite enter, kad pradėtumėte žaidimą...\n");
    while (_getch() != '\r') // // Padaro, kad žaidėjas nieko negalėtų įvesti, kol nepaspaudė enter
    { 
    }

    char **klausimai = uzkrautiKlausimus(failoVardas, &skaiciuotiKlausimus);

    // Atspausdina atsitiktinį klausimą
    char *klausimas = spausdintiAtsitiktiniKlausima(klausimai, skaiciuotiKlausimus);

    // Pakeičia '?' į įvestus ženklus
    pakeistiZenkla(klausimas);

    // Atlaisvina atmintį
    atlaisvintiAtminti(klausimai, skaiciuotiKlausimus);

    printf("\nPaspauskite Enter, kad uždarytumėte programą...\n");
    while (_getch() != '\r')
    {
    }
    

    return 0;
}
