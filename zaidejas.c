#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zaidejas.h"

// Funkcija rasti žaidėjo taškus faile
int skaitytiTaskus(const char *vardas) {
   FILE *failas = fopen(TASKU_FAILAS, "r");
   if (!failas) 
   {
      return 0; // Jei failas neegzistuoja, grąžina 0 taškų
   }

   char failoVardas[VARDO_ILGIS];
   int taskai;

   while (fscanf(failas, "%s %d", failoVardas, &taskai) == 2) 
   {
      if (strcmp(failoVardas, vardas) == 0) 
      {
         fclose(failas);
         return taskai; // Grąžina surastus taškus
      }
   }

   fclose(failas);
   return 0; // Jei vardas nerastas, grąžina 0 taškų
}

// Funkcija įrašyti žaidėjo surinktus taškus į failą
void irasytiTaskus(const char *vardas, int taskai) 
{
    FILE *pagrindinisFailas = fopen(TASKU_FAILAS, "r");
    FILE *laikinasFailas = fopen("laikinas.txt", "w");

    if (!laikinasFailas) 
    {
      perror("Nepavyko sukurti laikino failo");
      return;
    }

    int vardasRastas = 0;
    char failoVardas[VARDO_ILGIS];
    int esamiTaskai;

    if (pagrindinisFailas) 
    {
      // Nuskaito visus įrašus iš originalaus failo
      while (fscanf(pagrindinisFailas, "%s %d", failoVardas, &esamiTaskai) == 2) 
      {
         if (strcmp(failoVardas, vardas) == 0) 
         {
            fprintf(laikinasFailas, "%s %d\n", vardas, taskai); // Atnaujinami žaidėjo taškai, jeigu jau toks vardas egzistuoja
            vardasRastas = 1;
         } 
         else 
         {
            fprintf(laikinasFailas, "%s %d\n", failoVardas, esamiTaskai);
         }
      }

      fclose(pagrindinisFailas);
   }

   // Jei žaidėjas nerastas, pridėti naują įrašą į laikiną failą
   if (!vardasRastas) 
   {
      fprintf(laikinasFailas, "%s %d\n", vardas, taskai);
   }

   fclose(laikinasFailas);

   // Perkeliam laikino failo turinį į originalų failą
   remove(TASKU_FAILAS);
   rename("laikinas.txt", TASKU_FAILAS);
}
