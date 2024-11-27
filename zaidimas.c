#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // Lietuviškom raidėm
#include <conio.h> // Žaidimo startui
#include <string.h>
#include <ctype.h>
#include "klausimai.h"
#include "zaidejas.h"


int main() {
    
    system("chcp 65001 > nul");
    setlocale(LC_ALL, ".UTF-8");

    const char *failoVardas = "lengvas_lygis.txt";
    int skaiciuotiKlausimus;

    char zaidejoVardas[VARDO_ILGIS];
    printf("|***************************************************************|\n");
    printf("            Sveiki atvykę į viktoriną įstatant operacijas!\n");
    printf("                     Įveskite savo vardą: ");
    scanf("%s", zaidejoVardas);
    printf("|***************************************************************|\n");
    

    int zaidejoTaskai = skaitytiTaskus(zaidejoVardas);
    printf("            Sveiki, %s! Jūsų turimi taškai: %d\n", zaidejoVardas, zaidejoTaskai);

    printf("            Paspauskite enter, kad pradėtumėte žaidimą...\n");
    printf("|***************************************************************|\n");
    while (_getch() != '\r') {
    }

    Klausimas *klausimai = uzkrautiKlausimusIrAtsakymus(failoVardas, &skaiciuotiKlausimus);

    int zaidimasVyksta = 1;

    while(zaidimasVyksta)
    {

        // Atspausdina atsitiktinį klausimą
        Klausimas *pasirinktasKlausimas = spausdintiAtsitiktiniKlausima(klausimai, skaiciuotiKlausimus);

        // Pakeičia '?' į įvestus ženklus ir patikrina atsakymą
        pakeistiZenklaIrPridetiTaskus(pasirinktasKlausimas->klausimas, pasirinktasKlausimas->teisingiZenklai, &zaidejoTaskai);
        strcpy(pasirinktasKlausimas->klausimas, pasirinktasKlausimas->pradinisKlausimas); // Jeigu klausimas pasikartotų, jis grąžinamas į pradinę reikšmę su '?'

        char atsakymas[10];
        int tinkamasAtsakymas = 0;

        while(!tinkamasAtsakymas)
        {
            printf("|***************************************************************|\n");
            printf("               Ar norite tęsti žaidimą? (Taip/Ne): \n");
            printf("|***************************************************************|\n");
            scanf("%9s", atsakymas);

            for (int i = 0; i < 4; i++)
            {
                atsakymas[i] = toupper(atsakymas[i]);
            }

            if (strcmp(atsakymas, "TAIP") == 0)
            {
                tinkamasAtsakymas = 1; // Tinkama įvestis, tęsiame žaidimą
            }
            else if (strcmp(atsakymas, "NE") == 0)
            {
                tinkamasAtsakymas = 1; // Tinkama įvestis, uždarome žaidimą
                zaidimasVyksta = 0;
                printf("|***************************************************************|\n");
                printf("            Žaidimas baigtas! Iš viso turite: %d taškų\n", zaidejoTaskai);
                printf("|***************************************************************|\n");
            }
            else
            {   
                printf("|***************************************************************|\n");
                printf("Klaida: Atsakymas turi būti 'Taip' arba 'Ne'. Bandykite dar kartą.\n");
                printf("|***************************************************************|\n");
                while (getchar() != '\n'); // Išvalomas buffer
            }
        }

    }

    // Įrašo žaidėjo surinktus taškus į failą
    irasytiTaskus(zaidejoVardas, zaidejoTaskai);

    // Atlaisvina atmintį
    atlaisvintiAtminti(klausimai);

    printf("            Paspauskite Enter, kad uždarytumėte žaidimą...\n");
    printf("|***************************************************************|\n");
    while (_getch() != '\r')
    {
    }

    return 0;
}


