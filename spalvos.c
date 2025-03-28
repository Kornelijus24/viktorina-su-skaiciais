#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include "spalvos.h"
#include "zaidejas.h"
#include "pasiekimai.h"

// Funkcija parodyti pradžios ekraną
void parodytiPradziosEkrana() 
{
    printf(SPALVA_MELYNA "|****************************************************************************************************|\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "                                                                   \n");
    printf(SPALVA_ZALIA "               ██                                                 ██\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "                                                                  \n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA " ██        ██  ██   ██   ██   ████████     ██████     ██████      ██   ████     ██          ██\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "  ██      ██   ██   ██  ██       ██      ██      ██   ██    ██    ██   ██ ██    ██        ██  ██\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "   ██    ██    ██   ██ ██        ██     ██        ██  ██     ██   ██   ██  ██   ██       ██    ██ \n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "    ██  ██     ██   ████         ██     ██        ██  ███████     ██   ██   ██  ██      ██████████\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "     ████      ██   ██  ██       ██      ██      ██   ██    ██    ██   ██    ██ ██     ██        ██\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "      ██       ██   ██   ██      ██        ██████     ██      ██  ██   ██     ████    ██          ██ \n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "                                                                   \n");
    printf(SPALVA_MELYNA "|****************************************************************************************************|\n" SPALVA_PRADINE);
    printf(SPALVA_GELTONA "                          Sveiki atvykę į matematinę viktoriną!\n" SPALVA_PRADINE);
    printf(SPALVA_GELTONA "                     Atspėkite trūkstamus simbolius ir surinkite taškų.\n" SPALVA_PRADINE);
    printf(SPALVA_MELYNA "|****************************************************************************************************|\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "                                   Pasiruošę? Pradėkime!\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "                                    Įveskite savo vardą: " SPALVA_PRADINE);
}

// Funkcija parodyti pabaigos ekraną
void parodytiPabaigosEkrana(int zaidejoTaskai)
{
    printf(SPALVA_MELYNA "|****************************************************************************************************|\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "                                                                   \n");
    printf(SPALVA_ZALIA "               ██                                                 ██\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "                                                                  \n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA " ██        ██  ██   ██   ██   ████████     ██████     ██████      ██   ████     ██          ██\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "  ██      ██   ██   ██  ██       ██      ██      ██   ██    ██    ██   ██ ██    ██        ██  ██\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "   ██    ██    ██   ██ ██        ██     ██        ██  ██     ██   ██   ██  ██   ██       ██    ██ \n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "    ██  ██     ██   ████         ██     ██        ██  ███████     ██   ██   ██  ██      ██████████\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "     ████      ██   ██  ██       ██      ██      ██   ██    ██    ██   ██    ██ ██     ██        ██\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "      ██       ██   ██   ██      ██        ██████     ██      ██  ██   ██     ████    ██          ██ \n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "                                                                   \n");
    printf(SPALVA_MELYNA "|****************************************************************************************************|\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "          Sveikiname! Jūs sėkmingai užbaigėte žaidimą.\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "          Surinkti taškai: " SPALVA_GELTONA "%d\n" SPALVA_PRADINE, zaidejoTaskai);
    printf(SPALVA_ZALIA "          Ačiū, kad žaidėte! Tikimės, jog jums patiko!\n" SPALVA_PRADINE);
    printf(SPALVA_MELYNA "|****************************************************************************************************|\n" SPALVA_PRADINE);

}

// Funkcija parodyti meniu
void parodytiPagrindiniMeniu(const char *zaidejoVardas)
{
    printf(SPALVA_MELYNA "|***************************************************************|\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "                       Pagrindinis meniu\n" SPALVA_PRADINE);
    printf(SPALVA_MELYNA "|***************************************************************|\n" SPALVA_PRADINE);
    printf(SPALVA_GELTONA "                       Sveiki %s,\n", zaidejoVardas, SPALVA_PRADINE);
    printf(SPALVA_GELTONA "  1. Pradėti žaidimą\n" SPALVA_PRADINE);
    printf(SPALVA_GELTONA "  2. Turimi taškai\n" SPALVA_PRADINE);
    printf(SPALVA_GELTONA "  3. Pasiekimai\n" SPALVA_PRADINE);
    printf(SPALVA_GELTONA "  4. Turnyrinė lentelė\n" SPALVA_PRADINE);
    printf(SPALVA_GELTONA "  5. Palikti žaidimą\n" SPALVA_PRADINE);
    printf(SPALVA_MELYNA "|***************************************************************|\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "  Pasirinkite opciją: " SPALVA_PRADINE);
}

// Funkcija rodyti turimus taškus
void parodytiTaskus(int zaidejoTaskai)
{
    system("cls"); // Išvalo ekraną
    printf(SPALVA_MELYNA "|***************************************************************|\n" SPALVA_PRADINE);
    printf(SPALVA_ZALIA "                         Taškai\n" SPALVA_PRADINE);
    printf(SPALVA_MELYNA "|***************************************************************|\n" SPALVA_PRADINE);
    printf(SPALVA_GELTONA "  Jūsų surinkti taškai: " SPALVA_PRADINE);
    printf(SPALVA_ZALIA "%d\n" SPALVA_PRADINE, zaidejoTaskai);
    printf(SPALVA_GELTONA "  Grįžkite paspausdami Enter.\n" SPALVA_PRADINE);
    printf(SPALVA_MELYNA "|***************************************************************|\n" SPALVA_PRADINE);
    while (_getch() != '\r');
    
    
}
// Funkcija animacijai su spalvų perėjimu, skirta „Neįmanomam“ lygiui
void parodytiLygioAnimacija(const char *tekstas)
{
    const int laikas = 200;

    system("cls");
    printf("|****************************************************************************************************|\n");

    printf("                                        ");
    for (int i = 0; i < strlen(tekstas); i++)
    {
        printf("%c", tekstas[i]);
        fflush(stdout);
        Sleep(laikas);
    }
    printf("\n|****************************************************************************************************|\n");
    printf("SPAUSKITE ENTER, KAD PRADĖTUMĖTE!\n");
    while (_getch() != '\r');
}

// Funkcija veiksmams su pagrindiniu meniu
int pagrindinisMeniu(int zaidejoTaskai, const char *zaidejoVardas)
{
    int pasirinkimas = 0;

    while (1) 
    {
        system("cls"); // Išvalo ekraną
        parodytiPagrindiniMeniu(zaidejoVardas);

        if (scanf("%d", &pasirinkimas) != 1 || pasirinkimas < 1 || pasirinkimas > 5)
        {
            while (getchar() != '\n');
            printf(SPALVA_RAUSVA "  Klaida: Pasirinkimas turi būti 1, 2, 3, 4 arba 5.\n" SPALVA_PRADINE);
            printf(SPALVA_ZALIA "  Paspauskite Enter ir bandykite dar kartą.\n" SPALVA_PRADINE);
            while (_getch() != '\r');
        }
        else
        {
            break;
        }
    }

    return pasirinkimas;
}

