#include <stdio.h>
#include <conio.h>
#include "pasiekimai.h"
#include "spalvos.h"

// Masyvas saugoti pasiekimams
Pasiekimas pasiekimai[PASIEKIMU_SKAICIUS];

// Funkcija užkrauti pasiekimams
void uzkrautiPasiekimus() 
{
    pasiekimai[0] = (Pasiekimas){"Mokyklinukas", "Pasiekite 10 taškų.", 10, 0, 0};
    pasiekimai[1] = (Pasiekimas){"Pradinukas", "Pasiekite 50 taškų.", 50, 0, 0};
    pasiekimai[2] = (Pasiekimas){"Studentas", "Pasiekite 100 taškų.", 100, 0, 0};
    pasiekimai[3] = (Pasiekimas){"Bakalauras", "Pasiekite 200 taškų.", 200, 0, 0};
    pasiekimai[4] = (Pasiekimas){"Magistras", "Pasiekite 500 taškų.", 500, 0, 0};
    pasiekimai[5] = (Pasiekimas){"Daktaras", "Pasiekite 1000 taškų.", 1000, 0, 0};
    pasiekimai[6] = (Pasiekimas){"Profesorius", "Pasiekite 2000 taškų.", 2000, 0, 0};
    pasiekimai[7] = (Pasiekimas){"Genijus", "Pasiekite 5000 taškų.", 5000, 0, 0};
    pasiekimai[8] = (Pasiekimas){"Legenda", "Pasiekite 10000 taškų.", 10000, 0, 0};
    pasiekimai[9] = (Pasiekimas){"Skaičiuotojas", "Sužaisk 10 roundų.", 10, 0, 1};
    pasiekimai[10] = (Pasiekimas){"Matematikos fanas", "Sužaisk 20 roundų.", 20, 0, 1};
    pasiekimai[11] = (Pasiekimas){"Skaičių meistras", "Sužaisk 40 roundų.", 40, 0, 1};
    pasiekimai[12] = (Pasiekimas){"Roundų karalius", "Sužaisk 100 roundų.", 100, 0, 1};
    pasiekimai[13] = (Pasiekimas){"Matematikas", "Laimėkite 5 roundus iš eilės.", 5, 0, 2};
    pasiekimai[14] = (Pasiekimas){"Laimėtojas", "Laimekite 10 roundų iš eilės.", 10, 0, 2};
    pasiekimai[15] = (Pasiekimas){"Nesustabdomas", "Laimėkite 20 roundų iš eilės.", 20, 0, 2};
    pasiekimai[16] = (Pasiekimas){"Vidutinis lygis", "Pasiekite vidutinį lygį.", 100, 0, 0};
    pasiekimai[17] = (Pasiekimas){"Sunkus lygis", "Pasiekite sunkų lygį.", 300, 0, 0};
    pasiekimai[18] = (Pasiekimas){"Neįmanomas lygis", "Pasiekite neįmanoma lygį.", 500, 0, 0};
}

// Funkcija patikrinti ir atrakinti pasiekimus baigus žaidimą
void patikrintiPasiekimusPoZaidimo(int zaidejoTaskai, int suzaistiRoundai, int laimetiRoundai) 
{
    printf(SPALVA_GELTONA "\nTikrinami pasiekimai...\n" SPALVA_PRADINE);
    for (int i = 0; i < PASIEKIMU_SKAICIUS; i++) 
    {
        if (!pasiekimai[i].arIvykdytas) 
        {
            if ((pasiekimai[i].tipas == 0 && zaidejoTaskai >= pasiekimai[i].salyga) ||
                (pasiekimai[i].tipas == 1 && suzaistiRoundai >= pasiekimai[i].salyga) ||
                (pasiekimai[i].tipas == 2 && laimetiRoundai >= pasiekimai[i].salyga))
            {
                pasiekimai[i].arIvykdytas = 1;
                printf(SPALVA_ZALIA "Pasiekimas atrakintas: %s - %s\n" SPALVA_PRADINE, pasiekimai[i].pavadinimas, pasiekimai[i].aprasymas);
            }
        }
    }
    printf(SPALVA_GELTONA "\nPasiekimai patikrinti! Spauskite Enter, kad tęstumėte.\n" SPALVA_PRADINE);
    while (_getch() != '\r');
}

// Funkcija patikrinti žaidėjo įvykdytus pasiekimus prisijungus
void patikrintiPasiekimusPrisijungus(int zaidejoTaskai, int suzaistiRoundai, int laimetiRoundai) 
{
    for (int i = 0; i < PASIEKIMU_SKAICIUS; i++) 
    {
        if (!pasiekimai[i].arIvykdytas) 
        {
            if ((pasiekimai[i].tipas == 0 && zaidejoTaskai >= pasiekimai[i].salyga) ||
                (pasiekimai[i].tipas == 1 && suzaistiRoundai >= pasiekimai[i].salyga) ||
                (pasiekimai[i].tipas == 2 && laimetiRoundai >= pasiekimai[i].salyga))
            {
                pasiekimai[i].arIvykdytas = 1;
            }
        }
    }
}
  
// Funkcija parodyti pasiekimus
void parodytiPasiekimus() 
{
    printf(SPALVA_MELYNA "\nPasiekimai:\n" SPALVA_PRADINE);
    for (int i = 0; i < PASIEKIMU_SKAICIUS; i++) 
    {
        printf(SPALVA_ZALIA "%s - %s " SPALVA_PRADINE, pasiekimai[i].pavadinimas, pasiekimai[i].aprasymas);
        printf(" [%s]\n", pasiekimai[i].arIvykdytas ? SPALVA_ZALIA "Įvykdytas" SPALVA_PRADINE : SPALVA_RAUSVA "Neįvykdytas" SPALVA_PRADINE);
    }
    printf(SPALVA_GELTONA"\nPaspauskite Enter, kad sugrįžtumėte į pagrindinį meniu.\n" SPALVA_PRADINE);
    while (_getch() != '\r');
}

