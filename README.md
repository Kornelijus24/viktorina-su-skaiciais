# 🎯 Viktorina su skaičiais

Terminalinis žaidimas, kuriame tikrinamos tavo žinios ir loginis mąstymas per skaitinių klausimų viktoriną. Sukurta naudojant **C kalbą**.

---

## 📌 Projekto informacija

- **Autorius:** Kornelijus, Rokas
- **El. paštas:** kornelijus.baublys@mif.stud.vu.lt, rokas.perveneckas@mif.stud.vu.lt
- **Sukurta:** 2024-11-14
- **GitHub:** [https://github.com/Kornelijus24/viktorina-su-skaiciais](https://github.com/Kornelijus24/viktorina-su-skaiciais)

-------------------------------------------------------------------------------------------------------------------

## 🧠 Funkcionalumas

- ✅ Skirtingi sudėtingumo lygiai: lengvas, vidutinis, sunkus, neįmanomas
- ✅ Klausimai iš tekstinių failų pagal lygį
- ✅ Teisingų/neteisingų atsakymų skaičiavimas
- ✅ Taškų saugojimas `zaideju_taskai.txt` faile
- ✅ Spalvota išvestis terminale
- ✅ Pasiekimų sistema

-------------------------------------------------------------------------------------------------------------------

## 🚀 Paleidimas

### ✅ 1. Clone GIT repository
```bash
git clone https://github.com/Kornelijus24/viktorina-su-skaiciais.git
cd viktorina-su-skaiciais
```

### ✅ 2. Compile (Linux/Mac/WSL)
```bash
gcc zaidimas.c zaidejas.c klausimai.c lygiai.c spalvos.c pasiekimai.c -o zaidimas
```

### ✅ 3. Paleidimas
```bash
./zaidimas
```

🪟 **Windows vartotojams:** galite naudoti jau įkeltą `zaidimas.exe` failą.

---

## 🧩 Failų struktūra

| Failas / Katalogas        | Aprašymas |
|---------------------------|-----------|
| `zaidimas.c`              | Pagrindinis žaidimo failas |
| `zaidejas.[c/h]`          | Tvarko žaidėjo info, vardą, taškus |
| `klausimai.[c/h]`         | Klausimų nuskaitymas ir tikrinimas |
| `lygiai.[c/h]`            | Žaidimo lygių sistema |
| `spalvos.[c/h]`           | ANSI spalvos terminalui |
| `pasiekimai.[c/h]`        | Pasiekimų logika |
| `*.txt`                   | Klausimai bei taškų įrašai |

---

## 🏆 Pasiekimai

Žaidimo eigoje žaidėjas gali pasiekti skirtingus laimėjimus, pvz.:
- Atsakytas tam tikras klausimų skaičius!
- Pasiektas atitankamas taškų skaičius!
- Pasiektas atitinkamas sunkumo lygis!
- Laimėtas tam tikras roundų skaičius iš eilės!