#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <windows.h>

using namespace std;


enum numerKoloru {
    green,
    blue,
    red,
    violet,
    yellow,
    white,
    black,
};


void tworzenieTaliiOrazRozdanieZad1Zad2(int n, int k, int g, int gv, int o, int e); //funkcja tworząca talie niepotasowaną (z możliwośćią zmiany na potasowaną) i rozdająca karty między graczy

void iloscOrazUlozenieKartWGrzeZad3();

void liczenieZielonychKartZad4a(char** wszystkieLinie, int iloscLinii);

void iloscKartZad4b(char** wszystkieLinie, int iloscLinii);

void sprawdzanieWartosciKartZad5(char** wszystkieLinie, int iloscLinii);

void sprawdzeniePoprawnosciStanuGryZad6(char** wszystkieLinie, int iloscLinii, int aktywnyGracz, int liczbaGraczy, int eksplozja);

void posuniecieIObslugaEksplozjiZad7(int aktywnyGracz, int liczbaGraczy, int eksplozja);


void wczytajWartosci(int t[], int n);

int charToInt(char a);

int iloscKart(char linia[]);

int iloscKartZielonych(char linia[]);

char wartoscZielonej(char linia[]);

int iloscKartKoloru(char kolor[], char linia[]);

int qsortFunckja(const void* a, const void* b);

int poprawnaNaReceTest(int aktywnyGracz, int iloscGraczy, int kartyNaRece[]);

int sumaWKociolku(char liniaKociolka[]);

void wczytajTrzyPierwszeLiniePlikNowy(char** linie, int* aktywnyGracz, int* liczbaGraczy, int* eksplozja);

int koloryWKociolkuTest(int iloscKartKoloru[], int liczbaKociolkow);

int numerKoloruInt(char* wyraz);

void taliaGracza(char linia[], int** talia, int* liczbaKart);

void deckGracza(char linia[], int** talia, int* liczbaKart);

void wczytajGrePlik(char** linie, int* iloscLinii);

int iloscKartKoloru(char kolor[], char linia[]);

int dozwolonyKociolekTest(char linia[], char karta[]);

int czyMaKarty(char liniaKociolka[]);

int sumaWKociolkuNowa(int** talia, int liczbaKart);

void koniecRozgrywnki(int aktywnyGracz, int liczbaGraczy, int eksplozja);

int kolorWKociolku(char* liniaKociolka);

void sumaKociolkaIwiodącyKolor(char** wszystkieLinie, int** parametryKociolka, int iloscKociolkow, int adresKociolka);

void wyborNajmniejszejLubNajwiekszejKarty(int aktywnyGracz, int liczbaGraczy, int eksplozja);

void wyborOptymalnejKarty(int aktywnyGracz, int liczbaGraczy, int eksplozja);


int main() {
    int liczbaGraczy = 0, liczbaKociolkow = 0, liczbaZielonych = 0, wartoscZielonych = 0, inneKarty = 0, eksplozja = 0;
    cin >> liczbaGraczy >> liczbaKociolkow >> liczbaZielonych >> wartoscZielonych >> inneKarty >> eksplozja;
    //wyborOptymalnejKarty(4, liczbaGraczy, eksplozja);
   // wyborNajmniejszejLubNajwiekszejKarty(4, liczbaGraczy, eksplozja);
    tworzenieTaliiOrazRozdanieZad1Zad2(liczbaGraczy, liczbaKociolkow, liczbaZielonych, wartoscZielonych, inneKarty, eksplozja);
    cout << endl << endl;
    /* cout << endl << endl << "MENU" << endl;
    cout << "choose command and write it down" << endl << endl;
     cout << "NEXT_ROUND - starts the whole new round" << endl;
     cout << "NEXT_PLAYER_MOVE - starts the active players move" << endl;
     cout << "CHECK - check if the state of the game is correct" << endl;*/

     double liczbaRund = ceil((liczbaKociolkow * inneKarty + liczbaZielonych) * 1.0 / liczbaGraczy * 1.0);
     //cout << endl << "Ilosc rund = " << liczbaRund << endl;
    int aktywnyGracz = 1;
    //double liczbaRund = 18;
     for (int i = 0; i < liczbaRund; i++) {
         for (int j = 0; j < liczbaGraczy; j++) {
             posuniecieIObslugaEksplozjiZad7(aktywnyGracz, liczbaGraczy, eksplozja);
             cout << endl;
             Sleep(300);
             if (aktywnyGracz + 1 > liczbaGraczy) {
                 aktywnyGracz = 1;
             }
             else {
                 aktywnyGracz += 1;
             }
         }
     }
    koniecRozgrywnki(aktywnyGracz, liczbaGraczy, eksplozja);
    return 0;
}

void tworzenieTaliiOrazRozdanieZad1Zad2(int n, int k, int g, int gv, int o, int e) {
    FILE* plik = fopen("stan_gry.txt", "w");
    char tablicaKolorow[7][10] = { "green", "blue", "red", "violet", "yellow", "white", "black" };
    int* wartosciKart = (int*)malloc(o * sizeof(int));
    wczytajWartosci(wartosciKart, o);
    int** nowaTalia = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        nowaTalia[i] = (int*)malloc((o * k + g) * sizeof(int));
    }
    int numer = 0;
    for (int i = 0; i < (k + 1); i++) {
        if (i == 0) {
            for (int j = i; j < g; j++) {
                nowaTalia[0][j] = i;
                nowaTalia[1][j] = gv;
                numer++;
            }
        }
        else {
            int wartosc = 0;
            for (int j = numer; j < numer + o; j++) {
                nowaTalia[0][j] = i;
                nowaTalia[1][j] = wartosciKart[wartosc];
                wartosc++;
            }
            numer = numer + o;
        }
    }
    /*   srand(time(NULL)); // funkcja tasująca talie i rozdająca talie posrotowaną
       int liczbaKart = 0;
       for (int i = 0; i < o * k + g; i++) {
           if (nowaTalia[1][i] != 0) {
               liczbaKart++;
           }
       }
       int** potasowanaTalia = new int* [2];
       for (int i = 0; i < 2; i++) {
           potasowanaTalia[i] = new int[liczbaKart];
       }
       for (int i = 0; i < liczbaKart; i++) {
           potasowanaTalia[0][i] = 0;
           potasowanaTalia[1][i] = 0;
       }
       int* wylosowane = new int [liczbaKart];
       for (int i = 0; i < liczbaKart; i++) {
           int pomoc = -1;
           int dobra = 0;
           while (dobra == 0) {
               pomoc = rand() % liczbaKart;
               int licznik = 0;
               for (int k = 0; k < liczbaKart; k++) {
                   if (wylosowane[k] == pomoc) {
                       licznik++;
                   }
               }
               if (licznik == 0) {
                   dobra = 1;
               }
           }
           potasowanaTalia[0][i] = nowaTalia[0][pomoc];
           potasowanaTalia[1][i] = nowaTalia[1][pomoc];
           wylosowane[i] = pomoc;
       }*/
    cout << endl << endl << "START OF THE GAME" << endl << "Let's see what we've got" << endl << endl;
    Sleep(500);
    fprintf(plik, "active player = %d\n", 1);
    cout << "active player = 1" << endl;
    fprintf(plik, "players number = %d\n", n);
    cout << "players number = " << n << endl;
    fprintf(plik, "explosion threshold = %d\n", e);
    cout << "explosion threshold = " << e << endl;
    for (int j = 0; j < n; j++) {
        fprintf(plik, "%d player hand cards:", (j + 1));
        cout << j + 1 << " player hand cards:";
        for (int i = j; i < (o * k + g); i++) {
            fprintf(plik, " %d ", nowaTalia[1][i]);
            cout << " " << nowaTalia[1][i] << " ";
            fprintf(plik, "%s", tablicaKolorow[nowaTalia[0][i]]);
            cout << tablicaKolorow[nowaTalia[0][i]];
            i = i + n - 1;
        }
        fprintf(plik, "\n%d player deck cards:\n", (j + 1));
        cout << endl << j + 1 << " player deck cards:" << endl;
    }
    for (int i = 0; i < k; i++) {
        fprintf(plik, "%d pile cards:\n", i + 1);
        cout << i + 1 << " pile cards:" << endl;
    }
    for (int i = 0; i < 2; i++) {
        free(nowaTalia[i]);
    }
    free(nowaTalia);
    free(wartosciKart);
    nowaTalia = NULL;
    wartosciKart = NULL;
    fclose(plik);
    Sleep(500);
    iloscOrazUlozenieKartWGrzeZad3();
}

void wczytajWartosci(int t[], int n) {
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
}

void iloscOrazUlozenieKartWGrzeZad3() {
    int aktywnyGracz = 0, liczbaGraczy = 0, eksplozja = 0;
    char** wszystkieLinie = new char* [100];
    for (int i = 0; i < 100; i++) {
        wszystkieLinie[i] = new char[1000];
    }
    int iloscLinii = 0;
    wczytajGrePlik(wszystkieLinie, &iloscLinii);
    wczytajTrzyPierwszeLiniePlikNowy(wszystkieLinie, &aktywnyGracz, &liczbaGraczy, &eksplozja);
    cout << endl << endl << "TEST" << endl;
    cout << "Now we have to check the whole new game to avoid any defects" << endl << endl;
    Sleep(2000);
    int gracz = 0;
    int adres1 = 3;
    int adres2 = 4;
    for (int i = 0; i < liczbaGraczy; i++) {
        cout << i + 1 << "player has " << iloscKart(wszystkieLinie[adres1]) << " cards on hand" << endl;
        cout << i + 1 << "player has " << iloscKart(wszystkieLinie[adres2]) << " cards in front of him" << endl;
        adres1 += 2;
        adres2 += 2;
    }
    int liczbaKociolkow = iloscLinii - (2 * liczbaGraczy) - 3;
    cout << endl;
    for (int i = 0; i < liczbaKociolkow - 1; i++) {
        cout << "There are " << iloscKart(wszystkieLinie[i + iloscLinii - liczbaKociolkow]) << " cards on " << i + 1 << " pile" << endl;
    }
    cout << endl;
    liczenieZielonychKartZad4a(wszystkieLinie, iloscLinii);
    iloscKartZad4b(wszystkieLinie, iloscLinii);
    sprawdzanieWartosciKartZad5(wszystkieLinie, iloscLinii);
    sprawdzeniePoprawnosciStanuGryZad6(wszystkieLinie, iloscLinii, aktywnyGracz, liczbaGraczy, eksplozja);
    for (int i = 0; i < 100; i++) {
         delete[] wszystkieLinie[i];
     }
     delete[]wszystkieLinie;
}

int charToInt(char a) {
    int liczba = 0;
    liczba = a - '0';
    return liczba;
}

int iloscKart(char linia[]) {
    int licznik = 0, i = 0;
    while (linia[i] != '\0') {
        if ((linia[i] > 47) && (linia[i] < 58)) {
            licznik++;
            if ((linia[i + 1] >= '0') && (linia[i + 1] <= '9')) {
                i++;
            }
            if ((linia[i + 2] >= '0') && (linia[i + 2] <= '9')) {
                i++;
            }
        }
        i++;
    }
    return licznik - 1;
}

void liczenieZielonychKartZad4a(char** wszystkieLinie, int iloscLinii) {
    int licznikZielonych = 0, licznik = 0;
    int koniec = 0;
    char wartosc;
    char wartoscKoncowa = ' ';
    for (int i = 3; i < iloscLinii; i++) {
        licznik = iloscKartZielonych(wszystkieLinie[i]);
        wartosc = wartoscZielonej(wszystkieLinie[i]);
        if (licznik == -1) {
            cout << "Different green cards values occurred" << endl;
            koniec = 1;
            break;
        }
        licznikZielonych += licznik;
        if (licznik > 0) {
            wartoscKoncowa = wartosc;
        }
    }
    if ((koniec != 1) && (licznikZielonych == 0)) {
        cout << "Green cards does not exist" << endl;
    }
    else if (koniec != 1) {
        cout << "Found " << licznikZielonych << " green cards, all with " << wartoscKoncowa << " value" << endl;
    }
}

int iloscKartZielonych(char linia[]) {
    int licznik = 0;
    int i = 0;
    char wartosc = ' ';
    char wartoscTest = ' ';
    while (linia[i] != '\0') {
        if (linia[i] == 'g') {
            licznik++;
            if (linia[i - 3] == ' ') {
                wartosc = linia[i - 2] + linia[i - 1];
                if (licznik == 1) {
                    wartoscTest = wartosc;
                }
            }
            else if (linia[i - 2] == ' ') {
                wartosc = linia[i - 1];
            }
            if (wartoscTest != wartosc) {
                licznik = -1;
                return licznik;
            }
        }
        i++;
    }
    return licznik;
}

char wartoscZielonej(char linia[]) {
    int i = 0;
    char wartosc = ' ';
    while (linia[i] != '\0') {
        if (linia[i] == 'g') {
            if (linia[i - 3] == ' ') {
                wartosc = linia[i - 2];
            }
            else if (linia[i - 3] != ' ') {
                wartosc = linia[i - 3];
                wartosc += linia[i - 2];
            }
        }
        i++;
    }
    return wartosc;
}

void iloscKartZad4b(char** wszystkieLinie, int iloscLinii) {
    char tablicaKolorow[7][10] = { "green", "blue", "red", "violet", "yellow", "white", "black" };
    int iloscKart[7] = { 0 };
    for (int j = 0; j < iloscLinii; j++) {
        for (int i = 1; i < 7; i++) {
            iloscKart[i] += iloscKartKoloru(tablicaKolorow[i], wszystkieLinie[j]);
        }
    }
    int czyTakieSame = 0;
    for (int i = 1; i < 6; i++) {
        if ((iloscKart[i] != iloscKart[i + 1]) && (iloscKart[i] != 0) && (iloscKart[i + 1] != 0)) {
            czyTakieSame = 1;
        }
    }
    if (czyTakieSame == 1) {
        cout << endl << "At least two colors with a different number of cards were found:" << endl;
        for (int j = 1; j < 7; j++) {
            if (iloscKart[j] != 0) {
                cout << tablicaKolorow[j] << " cards are " << iloscKart[j] << endl;
            }
        }
    }
    else {
        cout << endl << "The number cards of all colors is equal: " << iloscKart[1] << endl;
    }
}

void sprawdzanieWartosciKartZad5(char** wszystkieLinie, int iloscLinii) {
    char tablicaKolorow[7][10] = { "green", "blue", "red", "violet", "yellow", "white", "black" };
    int kartyOrazWartosci[7][100] = { 0 };
    int licznik[7] = { 0 };
    for (int j = 0; j < iloscLinii; j++) {
        for (int i = 1; i < 7; i++) {
            char* wynik = strstr(wszystkieLinie[j], tablicaKolorow[i]);
            while (wynik != NULL) {
                char* wynikKopia = wynik;
                wynikKopia -= 3;
                if (wynikKopia[0] == ' ') {
                    kartyOrazWartosci[i][licznik[i]] = charToInt(wynikKopia[1]);
                    licznik[i] ++;
                }
                else if (wynikKopia[0] != ' ') {
                    int liczbaDwucyfrowa;
                    liczbaDwucyfrowa = charToInt(wynikKopia[0]) * 10;
                    liczbaDwucyfrowa += charToInt(wynikKopia[1]);
                    kartyOrazWartosci[i][licznik[i]] = liczbaDwucyfrowa;
                    licznik[i] ++;
                }
                wynik += 3;
                wynik = strstr(wynik, tablicaKolorow[i]);
            }
        }
    }
    for (int i = 1; i < 7; i++) {
        qsort(kartyOrazWartosci[i], 100, sizeof(*kartyOrazWartosci[i]), qsortFunckja);
    }
    int kartyOrazWartosciPosortowane[7][100] = { 0 };
    for (int i = 1; i < 7; i++) {
        int numerKomorki = 0;
        for (int j = 0; j < 100; j++) {
            if (kartyOrazWartosci[i][j] != 0) {
                kartyOrazWartosciPosortowane[i][numerKomorki] = kartyOrazWartosci[i][j];
                numerKomorki++;
            }
        }
    }
    int test = 0;
    for (int i = 0; i < 100; i++) {
        for (int j = 1; j < 6; j++) {
            if ((kartyOrazWartosciPosortowane[j][i] != 0) && (kartyOrazWartosciPosortowane[j + 1][i] != 0)) {
                if (kartyOrazWartosciPosortowane[j][i] != kartyOrazWartosciPosortowane[j + 1][i]) {
                    test = 1;
                    break;
                }
            }
        }
    }
    if (test == 0) {
        cout << endl << "The values of cards of all colors are identical:" << endl;
        for (int j = 0; j < 100; j++) {
            if (kartyOrazWartosciPosortowane[1][j] != 0) {
                cout << kartyOrazWartosciPosortowane[1][j] << " ";
            }
        }
        cout << endl;
    }
    else {
        cout << endl << "The values of cards of all colors are not identical:" << endl;
        for (int j = 1; j < 7; j++) {
            cout << tablicaKolorow[j] << " cards values: ";
            for (int i = 0; i < 100; i++) {
                if (kartyOrazWartosciPosortowane[j][i] != 0) {
                    cout << kartyOrazWartosciPosortowane[j][i] << " ";
                }
            }
            cout << endl;
        }
    }
}

int qsortFunckja(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void sprawdzeniePoprawnosciStanuGryZad6(char** wszystkieLinie, int iloscLinii, int aktywnyGracz, int liczbaGraczy, int eksplozja) {
    int liczbaBledow = 0;
    char tablicaKolorow[7][10] = { "green", "blue", "red", "violet", "yellow", "white", "black" };
    int liczbaKociolkow = 0;
    int suma[7] = { 0 };
    int kartyNaRece[6] = { 0 };
    int kartyPrzedNim[6] = { 0 };
    int adres1 = 3;
    int adres2 = 4;
    for (int i = 1; i < liczbaGraczy + 1; i++) {
        kartyNaRece[i] = iloscKart(wszystkieLinie[adres1]);
        kartyPrzedNim[i] = iloscKart(wszystkieLinie[adres2]);
        adres1 += 2;
        adres2 += 2;
    }
    liczbaBledow = poprawnaNaReceTest(aktywnyGracz, liczbaGraczy, kartyNaRece);
    for (int j = 3 + liczbaGraczy * 2; j < iloscLinii; j++) {
        liczbaKociolkow++;
        int iloscKart[7] = { 0 };
        for (int i = 1; i < 7; i++) {
            iloscKart[i] += iloscKartKoloru(tablicaKolorow[i], wszystkieLinie[j]);
        }

        liczbaBledow = koloryWKociolkuTest(iloscKart, liczbaKociolkow);
        suma[liczbaKociolkow - 1] = sumaWKociolku(wszystkieLinie[j]);
    }
    for (int i = 0; i < 6; i++) {
        if (suma[i] > eksplozja) {
            cout << endl << "Pile number " << i + 1 << " should explode earlier" << endl;
            liczbaBledow = 1;
        }
    }
    if (liczbaBledow == 0) {
        cout << endl << "Current state of the game is ok" << endl;
    }
}

int poprawnaNaReceTest(int aktywnyGracz, int iloscGraczy, int kartyNaRece[]) {
    int poprawna = 0;
    if ((aktywnyGracz > 1) && (aktywnyGracz < iloscGraczy)) {
        for (int j = aktywnyGracz - 1; j > 0; j--) {
            if ((kartyNaRece[aktywnyGracz] < kartyNaRece[j]) || (kartyNaRece[aktywnyGracz] >= kartyNaRece[j] + 2)) {
                poprawna = 1;
                cout << "The number of players cards on hand is wrong" << endl;
                return poprawna;
                break;
            }
        }
        for (int j = aktywnyGracz + 1; j < iloscGraczy + 1; j++) {
            if ((kartyNaRece[aktywnyGracz] < kartyNaRece[j]) || (kartyNaRece[aktywnyGracz] <= kartyNaRece[j] - 2)) {
                poprawna = 1;
                cout << "The number of players cards on hand is wrong" << endl;
                return poprawna;
                break;
            }
        }
    }
    else if (aktywnyGracz == 1) {
        for (int j = aktywnyGracz + 1; j < iloscGraczy + 1; j++) {
            if ((kartyNaRece[aktywnyGracz] < kartyNaRece[j]) || (kartyNaRece[aktywnyGracz] <= kartyNaRece[j] - 2)) {
                poprawna = 1;
                cout << "The number of players cards on hand is wrong" << endl;
                return poprawna;
                break;
            }
        }
    }
    else if (aktywnyGracz == iloscGraczy) {
        for (int j = aktywnyGracz - 1; j > 0; j--) {
            if ((kartyNaRece[aktywnyGracz] < kartyNaRece[j]) || (kartyNaRece[aktywnyGracz] >= kartyNaRece[j] + 2)) {
                poprawna = 1;
                cout << "The number of players cards on hand is wrong" << endl;
                return poprawna;
                break;
            }
        }
    }
    return poprawna;
}

int sumaWKociolku(char liniaKociolka[]) {
    char tablicaKolorow[7][10] = { "green", "blue", "red", "violet", "yellow", "white", "black" };
    int suma = 0;
    for (int i = 0; i < 7; i++) {
        char* wynik = strstr(liniaKociolka, tablicaKolorow[i]);
        while (wynik != NULL) {
            char* wynikKopia = wynik;
            wynikKopia -= 3;
            if (wynikKopia[0] == ' ') {
                suma += charToInt(wynikKopia[1]);
            }
            else if (wynikKopia[0] != ' ') {
                int liczbaDwucyfrowa;
                liczbaDwucyfrowa = charToInt(wynikKopia[0]) * 10;
                liczbaDwucyfrowa += charToInt(wynikKopia[1]);
                suma += liczbaDwucyfrowa;
            }
            wynik += 3;
            wynik = strstr(wynik, tablicaKolorow[i]);
        }
    }
    return suma;
}

void wczytajTrzyPierwszeLiniePlikNowy(char** linie, int* aktywnyGracz, int* liczbaGraczy, int* eksplozja) {
    char* wyraz;
    wyraz = strtok(linie[0], " =:\n");
    for (int i = 0; i < 2; i++) {
        wyraz = strtok(NULL, " =:\n");
    }
    *aktywnyGracz = atoi(wyraz);
    wyraz = strtok(linie[1], " =:\n");
    for (int i = 0; i < 2; i++) {
        wyraz = strtok(NULL, " =:\n");
    }
    *liczbaGraczy = atoi(wyraz);
    wyraz = strtok(linie[2], " =:\n");
    for (int i = 0; i < 2; i++) {
        wyraz = strtok(NULL, " =:\n");
    }
    *eksplozja = atoi(wyraz);
}

int koloryWKociolkuTest(int iloscKartKoloru[], int liczbaKociolkow) {
    int licznikZer = 0;
    for (int i = 1; i < 7; i++) {
        if (iloscKartKoloru[i] == 0) {
            licznikZer++;
        }
    }
    if ((licznikZer != 6) && (licznikZer != 5)) {
        cout << "Two different colors were found on the " << liczbaKociolkow << " pile" << endl;
        return  1;
    }
    else {
        return 0;
    }
}

int numerKoloruInt(char* wyraz) {
    if (strstr(wyraz, "green") != NULL) {
        return 0;
    }
    else if (strstr(wyraz, "blue") != NULL) {
        return 1;
    }
    else if (strstr(wyraz, "red") != NULL) {
        return 2;
    }
    else if (strstr(wyraz, "violet") != NULL) {
        return 3;
    }
    else if (strstr(wyraz, "yellow") != NULL) {
        return 4;
    }
    else if (strstr(wyraz, "white") != NULL) {
        return 5;
    }
    else if (strstr(wyraz, "black") != NULL) {
        return 6;
    }
    else {
        return -1;
    }
}

void taliaGracza(char linia[], int** talia, int* liczbaKart) {
    char tablicaKolorow[7][10] = { "green", "blue", "red", "violet", "yellow", "white", "black" };
    char* wyraz = strtok(linia, " =\n");
    for (int i = 0; i < 3; i++) {
        wyraz = strtok(NULL, " =\n");
    }
    int licznik = -1;
    for (int j = 0; j < 1000; j++) {
        if (j % 2 == 0) {
            licznik++;
        }
        wyraz = strtok(NULL, " =\n");
        if (wyraz != NULL) {
            if (j % 2 == 0) {
                talia[0][licznik] = atoi(wyraz);
            }
            else {
                talia[1][licznik] = numerKoloruInt(wyraz);
            }
            *liczbaKart = licznik;
        }
    }
}

void deckGracza(char linia[], int** talia, int* liczbaKart) {
    char tablicaKolorow[7][10] = { "green", "blue", "red", "violet", "yellow", "white", "black" };
    char* wyraz = strtok(linia, " =\n");
    for (int i = 0; i < 2; i++) {
        wyraz = strtok(NULL, " =\n");
    }
    int licznik = -1;
    for (int j = 0; j < 1000; j++) {
        if (j % 2 == 0) {
            licznik++;
        }
        wyraz = strtok(NULL, " =\n");
        if (wyraz != NULL) {
            if (j % 2 == 0) {
                talia[0][licznik] = atoi(wyraz);
            }
            else {
                talia[1][licznik] = numerKoloruInt(wyraz);
            }
            *liczbaKart = licznik;
        }
    }
}

void wczytajGrePlik(char** linie, int* iloscLinii) {
    FILE* plik = fopen("stan_gry.txt", "r");
    int i = 0;
    while (!feof(plik)) {
        fgets(linie[i], 1000, plik);
        linie[i] = strtok(linie[i], "\n");
        i++;
    }
    *iloscLinii = i;
    fclose(plik);
}

int iloscKartKoloru(char kolor[], char linia[]) {
    int licznik = 0;
    char* wynik = strstr(linia, kolor);
    while (wynik != NULL) {
        licznik++;
        wynik += 3;
        wynik = strstr(wynik, kolor);
    }
    return licznik;
}

int dozwolonyKociolekTest(char linia[], char karta[]) {
    char tablicaKolorow[7][10] = { "green", "blue", "red", "violet", "yellow", "white", "black" };
    if (iloscKartKoloru(karta, linia) > 0) {
        return 0;
    }
    else if ((iloscKartKoloru(tablicaKolorow[0], linia) > 0) && (iloscKartKoloru(karta, linia) == 0)) {
        return 0;
    }
    else if (czyMaKarty(linia) == 0) {
        return 0;
    }
    else {
        return 1;
    }
}

int czyMaKarty(char liniaKociolka[]) {
    char* wyraz;
    wyraz = strtok(liniaKociolka, " \n");
    for (int i = 0; i < 3; i++) {
        wyraz = strtok(NULL, " \n");
    }
    if (wyraz == NULL) {
        return 0;
    }
    else {
        return 1;
    }
}

int sumaWKociolkuNowa(int** talia, int liczbaKart) {
    int suma = 0;
    for (int i = 0; i < liczbaKart + 1; i++) {
        suma += talia[0][i];
    }
    return suma;
}

void posuniecieIObslugaEksplozjiZad7(int aktywnyGracz, int liczbaGraczy, int eksplozja) {
    char** wszystkieLinie = new char* [100];
    for (int i = 0; i < 100; i++) {
        wszystkieLinie[i] = new char[1000];
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 1000; j++) {
            wszystkieLinie[i][j] = ' ';
        }
    }
    int iloscLinii = 0;
    wczytajGrePlik(wszystkieLinie, &iloscLinii);
    char** linieKopia = new char* [iloscLinii];
    for (int i = 0; i < iloscLinii; i++) {
        linieKopia[i] = new char[1000];
    }
    for (int i = 0; i < iloscLinii; i++) {
        for (int j = 0; j < 1000; j++) {
            linieKopia[i][j] = ' ';
        }
    }
    for (int i = 0; i < iloscLinii - 1; i++) {
        linieKopia[i] = wszystkieLinie[i];
    }
    int kociol = iloscLinii - 3 - 2 * liczbaGraczy;
    char linieKociolkow[6][1000] = { "" };
    for (int i = 0; i < kociol; i++) {
        for (int j = 0; j < 1000; j++) {
            linieKociolkow[i][j] = linieKopia[3 + (2 * liczbaGraczy) + i][j];
        }
    }
    char tablicaKolorow[7][10] = { "green", "blue", "red", "violet", "yellow", "white", "black" };
    int suma[6] = { 0 };
    int** karta = new int* [2];
    for (int i = 0; i < 2; i++) {
        karta[i] = new int[2];
    }
    int liczbaKart = 0;
    int liczbaKartDeck = 0;
    char scalona[2] = { "" };
    int** talia = new int* [2];
    for (int i = 0; i < 2; i++) {
        talia[i] = new int[1000];
    }
    int** deck = new int* [2];
    for (int i = 0; i < 2; i++) {
        deck[i] = new int[1000];
    }
    int** taliaKociolka = new int* [2];
    for (int j = 0; j < 2; j++) {
        taliaKociolka[j] = new int[1000];
    }
    for (int i = 0; i < 2; i++) {
        talia[0][i] = 0;
        talia[1][i] = 0;
        deck[0][i] = 0;
        deck[1][i] = 0;
        taliaKociolka[0][i] = 0;
        taliaKociolka[1][i] = 0;
    }
    int liczbaKociolkow = iloscLinii - 3 - (2 * liczbaGraczy);
    taliaGracza(wszystkieLinie[(aktywnyGracz * 2) + 1], talia, &liczbaKart);
    taliaGracza(wszystkieLinie[(aktywnyGracz * 2) + 2], deck, &liczbaKartDeck);
    liczbaKartDeck = 0;
    for (int i = 0; i < 100; i++) {
        if (deck[0][i] > 0) {
            liczbaKartDeck++;
        }
    }
    karta[0][0] = talia[0][0];
    karta[1][0] = talia[1][0];
    int liczba = karta[0][0];
    if (liczba < 10) {
        scalona[0] = liczba + '0';
    }
    else {
        int cyfra2 = liczba % 10;
        int cyfra1 = liczba / 10;
        scalona[0] = cyfra1 + '0';
        scalona[1] = cyfra2 + '0';
    }
    int liczbaKartaWKociolku = 0;
    int adresKociolka = 0;
    int czyEksplozja = 0;
    int numerKociolka = 0;
    int licznikPomocniczy = 0;
    int sumaPomocnicza = 0;
    if ((karta[0][0] != 0) || (karta[1][0] != 0)) {
        if (karta[1][0] != 0) {  // jeśli karta nie jest zielona
            for (int i = iloscLinii - liczbaKociolkow; i < iloscLinii + 1; i++) {
                numerKociolka++;
                if (dozwolonyKociolekTest(wszystkieLinie[i], tablicaKolorow[karta[1][0]]) == 0) {

                    deckGracza(wszystkieLinie[i], taliaKociolka, &liczbaKartaWKociolku);
                    licznikPomocniczy = 0;
                    for (int i = 0; i < 100; i++) {
                        if (taliaKociolka[0][i] > 0) {
                            sumaPomocnicza += taliaKociolka[0][i];
                            licznikPomocniczy++;
                        }
                    }
                    if (sumaPomocnicza + karta[0][0] > eksplozja) {
                        czyEksplozja = 1;
                        adresKociolka = i;
                        for (int j = 0; j < liczbaKart + 1; j++) {
                            if ((talia[0][j] == karta[0][0]) && (talia[1][j] == karta[1][0])) {
                                talia[0][j] = 0;
                                talia[1][j] = 0;
                                for (int k = j; k < liczbaKart; k++) {
                                    talia[0][k] = talia[0][k + 1];
                                    talia[1][k] = talia[1][k + 1];
                                }
                                break;
                            }
                        }
                        for (int j = liczbaKartDeck; j < liczbaKartDeck + licznikPomocniczy + 1; j++) {
                            deck[0][j] = taliaKociolka[0][j - liczbaKartDeck];
                            deck[1][j] = taliaKociolka[1][j - liczbaKartDeck];
                            taliaKociolka[0][j - liczbaKartDeck] = 0;
                            taliaKociolka[1][j - liczbaKartDeck] = 0;
                        }
                        deck[0][liczbaKartDeck + licznikPomocniczy] = karta[0][0];
                        deck[1][liczbaKartDeck + licznikPomocniczy] = karta[1][0];
                        break;
                    }
                    else {
                        adresKociolka = i;
                        for (int j = 0; j < liczbaKart + 1; j++) {
                            if ((talia[0][j] == karta[0][0]) && (talia[1][j] == karta[1][0])) {
                                for (int k = j; k < liczbaKart; k++) {
                                    talia[0][k] = talia[0][k + 1];
                                    talia[1][k] = talia[1][k + 1];
                                }
                                break;
                            }
                        }
                        taliaKociolka[0][licznikPomocniczy] = karta[0][0];
                        taliaKociolka[1][licznikPomocniczy] = karta[1][0];
                        break;
                    }
                }
            }
        }
        else {
            deckGracza(wszystkieLinie[iloscLinii - liczbaKociolkow], taliaKociolka, &liczbaKartaWKociolku);
            for (int i = 0; i < 100; i++) {
                if (taliaKociolka[0][i] > 0) {
                    sumaPomocnicza += taliaKociolka[0][i];
                    licznikPomocniczy++;
                }
            }
            numerKociolka++;
            if (sumaPomocnicza + karta[0][0] > eksplozja) {
                czyEksplozja = 1;
                adresKociolka = iloscLinii - liczbaKociolkow;
                for (int j = 0; j < liczbaKart + 1; j++) {
                    if ((talia[0][j] == karta[0][0]) && (talia[1][j] == karta[1][0])) {
                        talia[0][j] = 0;
                        talia[1][j] = 0;
                        for (int k = j; k < liczbaKart; k++) {
                            talia[0][k] = talia[0][k + 1];
                            talia[1][k] = talia[1][k + 1];
                        }
                        break;

                    }
                    for (int j = liczbaKartDeck; j < liczbaKartDeck + licznikPomocniczy + 1; j++) {
                        deck[0][j] = taliaKociolka[0][j - liczbaKartDeck];
                        deck[1][j] = taliaKociolka[1][j - liczbaKartDeck];
                        taliaKociolka[0][j - liczbaKartDeck] = 0;
                        taliaKociolka[1][j - liczbaKartDeck] = 0;
                    }
                    deck[0][liczbaKartDeck + liczbaKartaWKociolku] = karta[0][0];
                    deck[1][liczbaKartDeck + liczbaKartaWKociolku] = karta[1][0];
                }
            }
            else {
                adresKociolka = iloscLinii - liczbaKociolkow;
                for (int j = 0; j < liczbaKart + 1; j++) {
                    if ((talia[0][j] == karta[0][0]) && (talia[1][j] == karta[1][0])) {
                        for (int k = j; k < liczbaKart; k++) {
                            talia[0][k] = talia[0][k + 1];
                            talia[1][k] = talia[1][k + 1];
                        }
                        break;
                    }
                }
                taliaKociolka[0][licznikPomocniczy] = karta[0][0];
                taliaKociolka[1][licznikPomocniczy] = karta[1][0];
            }
        }
        FILE* plik;
        plik = fopen("stan_gry.txt", "w");
        for (int i = 0; i < iloscLinii - 1; i++) {
            if (i == 0) {
                if (aktywnyGracz + 1 > liczbaGraczy) {
                    fprintf(plik, "active player = %d\n", 1);
                    cout << "active player = " << 1 << endl;
                }
                else {
                    fprintf(plik, "active player = %d\n", aktywnyGracz + 1);
                    cout << "active player = " << aktywnyGracz + 1 << endl;
                }
            }
            else if (i == (aktywnyGracz * 2) + 1) {
                fprintf(plik, "%d player hand cards: ", aktywnyGracz);
                cout << aktywnyGracz << " player hand cards: ";
                for (int j = 0; j < liczbaKart; j++) {
                    fprintf(plik, "%d %s ", talia[0][j], tablicaKolorow[talia[1][j]]);
                    cout << talia[0][j] << " " << tablicaKolorow[talia[1][j]] << " ";
                }
                fprintf(plik, "\n");
                cout << endl;
            }
            else if (i == (aktywnyGracz * 2) + 2) {
                fprintf(plik, "%d player deck cards: ", aktywnyGracz);
                cout << aktywnyGracz << " player deck cards: ";
                if (czyEksplozja == 1) {
                    for (int j = 0; j < liczbaKartDeck + liczbaKartaWKociolku + 2; j++) {
                        fprintf(plik, "%d %s ", deck[0][j], tablicaKolorow[deck[1][j]]);
                        cout << deck[0][j] << " " << tablicaKolorow[deck[1][j]] << " ";
                    }
                }
                else {
                    for (int j = 0; j < liczbaKartDeck; j++) {
                        fprintf(plik, "%d %s ", deck[0][j], tablicaKolorow[deck[1][j]]);
                        cout << deck[0][j] << " " << tablicaKolorow[deck[1][j]] << " ";
                    }
                }
                fprintf(plik, "\n");
                cout << endl;
            }
            else if (i == adresKociolka) {
                if (czyEksplozja == 1) {
                    fprintf(plik, "%d pile cards: \n", numerKociolka);
                    cout << numerKociolka << " pile cards: " << endl;
                }
                else {
                    fprintf(plik, "%d pile cards: ", numerKociolka);
                    cout << numerKociolka << " pile cards: ";
                    for (int j = 0; j < licznikPomocniczy + 1; j++) {
                        fprintf(plik, "%d %s ", taliaKociolka[0][j], tablicaKolorow[taliaKociolka[1][j]]);
                        cout << taliaKociolka[0][j] << " " << tablicaKolorow[taliaKociolka[1][j]] << " ";
                    }
                    fprintf(plik, "\n");
                    cout << endl;
                }
            }
            else if (i >= 3 + 2 * liczbaGraczy) {
                fprintf(plik, "%s\n", linieKociolkow[i - (3 + 2 * liczbaGraczy)]);
                cout << linieKociolkow[i - (3 + 2 * liczbaGraczy)] << endl;
            }
            else {
                fprintf(plik, "%s\n", linieKopia[i]);
                cout << linieKopia[i] << endl;
            }
        }
        fclose(plik);
        /*     for (int j = 0; j < 100; j++) {
                 delete[]wszystkieLinie[j];
             }
             delete[]wszystkieLinie;
             for (int i = 0; i < iloscLinii - 1; i++) {
                 delete[]linieKopia[i];
             }
             delete[]linieKopia;
             for (int j = 0; j < 2; j++) {
                 delete[]taliaKociolka[j];
                 delete[]deck[j];
                 delete[]talia[j];
                 delete[]karta[j];
             }
             delete[]taliaKociolka;
             delete[]deck;
             delete[]talia;
             delete[]karta;*/
    }
}

void koniecRozgrywnki(int aktywnyGracz, int liczbaGraczy, int eksplozja) {
    char tablicaKolorow[7][10] = { "green", "blue", "red", "violet", "yellow", "white", "black" };
    int suma[6] = { 0 };
    char** wszystkieLinie = new char* [100];
    for (int i = 0; i < 100; i++) {
        wszystkieLinie[i] = new char[1000];
    }
    int iloscLinii = 0;
    wczytajGrePlik(wszystkieLinie, &iloscLinii);
    int** wynikGracza = new int* [liczbaGraczy];
    for (int i = 0; i < liczbaGraczy; i++) {
        wynikGracza[i] = new int[7];
    }
    for (int i = 0; i < liczbaGraczy; i++) {
        for (int j = 0; j < 7; j++) {
            wynikGracza[i][j] = 0;
        }
    }
    int gracz = 0;
    int iloscKociolkow = iloscLinii - (2 * liczbaGraczy) - 3;
    for (int j = 3; j < liczbaGraczy * 2 + 2; j += 2) {
        for (int i = 0; i < 7; i++) {
            char* wynik = strstr(wszystkieLinie[j + 1], tablicaKolorow[i]);
            while (wynik != NULL) {
                char* wynikKopia = wynik;
                wynikKopia -= 3;
                wynikGracza[gracz][i]++;
                wynik += 3;
                wynik = strstr(wynik, tablicaKolorow[i]);
            }
        }
        gracz++;
    }
    int czyJestGraczOdporny[7] = { 0 };
    int** numerGraczaOdpornego = new int* [liczbaGraczy];
    for (int i = 0; i < liczbaGraczy; i++) {
        numerGraczaOdpornego[i] = new int[7];
    }
    for (int i = 0; i < liczbaGraczy; i++) {
        for (int j = 0; j < 7; j++) {
            numerGraczaOdpornego[i][j] = 0;
        }
    }
    for (int i = 0; i < 7; i++) {
        int max = -1;
        for (int j = 0; j < liczbaGraczy; j++) {
            if (wynikGracza[j][i] > max) {
                max = wynikGracza[j][i];
            }
        }
        int licznik = 0;
        for (int j = 0; j < liczbaGraczy; j++) {
            if (wynikGracza[j][i] == max) {
                licznik++;
                numerGraczaOdpornego[j][i] = 1;
                czyJestGraczOdporny[i] = 1;
            }
        }
        if (licznik != 1) {
            czyJestGraczOdporny[i] = 0;
        }
    }
    cout << endl << endl << "THE END OF THE GAME" << endl << endl;
    for (int i = 1; i < 7; i++) {
        if (czyJestGraczOdporny[i] == 1) {
            for (int k = 0; k < liczbaGraczy; k++) {
                if (numerGraczaOdpornego[k][i] == 1) {
                    cout << "The player " << k + 1 << " is immune to the color " << tablicaKolorow[i] << endl;
                    wynikGracza[k][i] = 0;
                }
            }

        }
    }
    for (int j = 0; j < liczbaGraczy; j++) {
        int sumaKoncowa = 0;
        for (int i = 0; i < 7; i++) {
            if (i == 0) {
                sumaKoncowa = sumaKoncowa + 2 * wynikGracza[j][i];
            }
            else {
                sumaKoncowa += wynikGracza[j][i];
            }
        }
        cout << "Player's " << j + 1 << " score = " << sumaKoncowa << endl;
    }
    for (int j = 0; j < 100; j++) {
        delete[]wszystkieLinie[j];
    }
    delete[]wszystkieLinie;
    for (int i = 0; i < liczbaGraczy; i++) {
        delete[]wynikGracza[i];
        delete[]numerGraczaOdpornego[i];
    }
    delete[]wynikGracza;
    delete[]numerGraczaOdpornego;
}

/*void sumaKociolkaIwiodącyKolor(char** wszystkieLinie, int **parametryKociolka, int iloscKociolkow, int adresKociolka) {
    for (int i = 0; i < iloscKociolkow; i++) {
        parametryKociolka[0][i] = sumaWKociolku(wszystkieLinie[adresKociolka + i]);
        parametryKociolka[1][i] = kolorWKociolku(wszystkieLinie[adresKociolka + i]);
    }
}*/

/*void wyborNajmniejszejLubNajwiekszejKarty(int aktywnyGracz, int liczbaGraczy, int eksplozja) {
    char** wszystkieLinie = new char* [100];
    for (int i = 0; i < 100; i++) {
        wszystkieLinie[i] = new char[1000];
    }
    int iloscLinii = 0;
    wczytajGrePlik(wszystkieLinie, &iloscLinii);
    char tablicaKolorow[7][10] = { "green", "blue", "red", "violet", "yellow", "white", "black" };
    int suma[6] = { 0 };
    int liczbaKart = 0;
    int liczbaKartDeck = 0;
    int liczbaKociolkow = iloscLinii - 3 - (2 * liczbaGraczy);
    int adresKociolka = iloscLinii - liczbaKociolkow;
    int** kartaMax = new int* [2];
    int** kartaMin = new int* [2];
    int** karta = new int* [2];
    char** scalonaMin = new char* [2];
    char** scalonaMax = new char* [2];
    int** talia = new int* [2];
    int** deck = new int* [2];
    int** taliaKociolka = new int* [2];
    for (int i = 0; i < 2; i++) {
        kartaMax[i] = new int[1000];
        kartaMin[i] = new int[1000];
        karta[i] = new int[1000];
        scalonaMin[i] = new char[1000];
        scalonaMax[i] = new char[1000];
        talia[i] = new int[1000];
        deck[i] = new int[1000];
        taliaKociolka[i] = new int[1000];
    }
    int** parametryKociolka = new int* [2];
    for (int i = 0; i < 2; i++) {
        parametryKociolka[i] = new int[liczbaKociolkow];
    }
    for (int i = 0; i < 1000; i++) {
        kartaMax[0][i] = 0;
        kartaMax[1][i] = 0;
        kartaMin[0][i] = 0;
        kartaMin[1][i] = 0;
        karta[0][i] = 0;
        karta[1][i] = 0;
        talia[0][i] = 0;
        talia[1][i] = 0;
        deck[0][i] = 0;
        deck[1][i] = 0;
        taliaKociolka[0][i] = 0;
        taliaKociolka[1][i] = 0;
        scalonaMin[0][i] = 0;
        scalonaMin[1][i] = 0;
        scalonaMax[0][i] = 0;
        scalonaMax[1][i] = 0;
    }
    for (int i = 0; i < liczbaKociolkow; i++) {
        parametryKociolka[0][i] = 0;
        parametryKociolka[1][i] = 0;
    }
    sumaKociolkaIwiodącyKolor(wszystkieLinie, parametryKociolka, liczbaKociolkow, adresKociolka);
    int licznikMinPomocniczy = 0;
    int licznikMaxPomocniczy = 0;
    taliaGracza(wszystkieLinie[(aktywnyGracz * 2) + 1], talia, &liczbaKart);
    deckGracza(wszystkieLinie[(aktywnyGracz * 2) + 2], deck, &liczbaKartDeck);

    int min = INT_MAX;
    int max = -1;
    for (int k = 0; k < liczbaKart + 1; k++) {
        if (talia[0][k] < min) {
            min = talia[0][k];
        }
        if (talia[0][k] > max) {
            max = talia[0][k];
        }
    }
    licznikMinPomocniczy = 0;
    licznikMaxPomocniczy = 0;
    for (int k = 0; k < liczbaKart + 1; k++) {
        if (talia[0][k] == min) {
            kartaMin[0][licznikMinPomocniczy] = min;
            kartaMin[1][licznikMinPomocniczy] = talia[1][k];
            licznikMinPomocniczy++;
        }
        if (talia[0][k] == max) {
            kartaMax[0][licznikMaxPomocniczy] = max;
            kartaMax[1][licznikMaxPomocniczy] = talia[1][k];
            licznikMaxPomocniczy++;
        }
    }
    for (int i = 0; i < licznikMinPomocniczy; i++) {
        int liczba = kartaMin[0][i];
        if (liczba < 10) {
            scalonaMin[0][i] = liczba + '0';
        }
        else {
            int cyfra2 = liczba % 10;
            int cyfra1 = liczba / 10;
            scalonaMin[0][i] = cyfra1 + '0';
            scalonaMin[1][i] = cyfra2 + '0';
        }
    }
    for (int i = 0; i < licznikMaxPomocniczy; i++) {
        int liczba = kartaMax[0][i];
        if (liczba < 10) {
            scalonaMax[0][i] = liczba + '0';
        }
        else {
            int cyfra2 = liczba % 10;
            int cyfra1 = liczba / 10;
            scalonaMax[0][i] = cyfra1 + '0';
            scalonaMax[1][i] = cyfra2 + '0';
        }
    }
    int czyEksplozja = 0;
    int sumaMin = INT_MAX;
    int kociolekMin = 0;
    int numerKarty = -1;
    for (int j = 0; j < licznikMinPomocniczy; j++) {
        int istniejeKociolekWKolorzeKarty = 0;
        int suma = 0;
        int kociolek = 0;
        if (kartaMin[1][j] != 0) {
            for (int i = 0; i < liczbaKociolkow; i++) {
                if (parametryKociolka[1][i] == kartaMin[1][j]) {
                    istniejeKociolekWKolorzeKarty = 1;
                    suma = parametryKociolka[0][i];
                    kociolek = i;
                    if (suma < sumaMin) {
                        sumaMin = suma;
                        kociolekMin = kociolek;
                        numerKarty = j;
                    }
                    break;
                }
            }
            if (istniejeKociolekWKolorzeKarty == 0) {
                for (int i = 0; i < liczbaKociolkow; i++) {
                    if (parametryKociolka[1][i] == 7) {
                        suma = 0;
                        kociolek = i;
                        if (suma < sumaMin) {
                            sumaMin = suma;
                            kociolekMin = kociolek;
                            numerKarty = j;
                        }
                        break;
                    }
                }
            }
        }
        else {
            for (int i = 0; i < liczbaKociolkow; i++) {
                suma = parametryKociolka[0][i];
                kociolek = i;
                if (suma < sumaMin) {
                    sumaMin = suma;
                    kociolekMin = kociolek;
                    numerKarty = j;
                }
                break;
            }
        }
    }
    if (sumaMin + kartaMin[0][numerKarty] > eksplozja) {
        sumaMin = INT_MAX;
        kociolekMin = 0;
        numerKarty = -1;
        for (int j = 0; j < licznikMaxPomocniczy; j++) {
            int istniejeKociolekWKolorzeKarty = 0;
            int suma = 0;
            int kociolek = 0;
            if (kartaMax[1][j] != 0) {
                for (int i = 0; i < liczbaKociolkow; i++) {
                    if (parametryKociolka[1][i] == kartaMax[1][j]) {
                        istniejeKociolekWKolorzeKarty = 1;
                        suma = parametryKociolka[0][i];
                        kociolek = i;
                        if (suma < sumaMin) {
                            sumaMin = suma;
                            kociolekMin = kociolek;
                            numerKarty = j;
                        }
                        break;
                    }
                }
                if (istniejeKociolekWKolorzeKarty == 0) {
                    for (int i = 0; i < liczbaKociolkow; i++) {
                        if (parametryKociolka[1][i] == 7) {
                            suma = 0;
                            kociolek = i;
                            if (suma < sumaMin) {
                                sumaMin = suma;
                                kociolekMin = kociolek;
                                numerKarty = j;
                            }
                            break;
                        }
                    }
                }
            }
            else {
                for (int i = 0; i < liczbaKociolkow; i++) {
                    suma = parametryKociolka[0][i];
                    kociolek = i;
                    if (suma < sumaMin) {
                        sumaMin = suma;
                        kociolekMin = kociolek;
                        numerKarty = j;
                    }
                    break;
                }
            }
        }
        karta[0][0] = kartaMax[0][numerKarty];
        karta[1][0] = kartaMax[1][numerKarty];
        czyEksplozja = 1;
    }
    else {
        karta[0][0] = kartaMin[0][numerKarty];
        karta[1][0] = kartaMin[1][numerKarty];
    }
    int liczbaKartaWKociolku = 0;
    deckGracza(wszystkieLinie[iloscLinii - liczbaKociolkow + kociolekMin], taliaKociolka, &liczbaKartaWKociolku);  // talia kociołka, do którego będziemy dokładać kartę
    if (czyEksplozja == 1) {
        int j = 0;
        for (j = 0; j < liczbaKart + 1; j++) {
            if ((talia[0][j] == karta[0][0]) && (talia[1][j] == karta[1][0])) {
                talia[0][j] = 0;
                talia[1][j] = 0;
                for (int k = j; k < liczbaKart; k++) {
                    talia[0][k] = talia[0][k + 1];
                    talia[1][k] = talia[1][k + 1];
                }
                break;
            }
        }
        for (j = liczbaKartDeck; j < liczbaKartDeck + liczbaKartaWKociolku + 1; j++) {
            deck[0][j] = taliaKociolka[0][j - liczbaKartDeck];
            deck[1][j] = taliaKociolka[1][j - liczbaKartDeck];
            taliaKociolka[0][j - liczbaKartDeck] = 0;
            taliaKociolka[1][j - liczbaKartDeck] = 0;
        }
        deck[0][liczbaKartDeck + liczbaKartaWKociolku + 1] = karta[0][0];
        deck[1][liczbaKartDeck + liczbaKartaWKociolku + 1] = karta[1][0];
    }
    else {
        int j = 0;
        for (j = 0; j < liczbaKart + 1; j++) {
            if ((talia[0][j] == karta[0][0]) && (talia[1][j] == karta[1][0])) {
                for (int k = j; k < liczbaKart; k++) {
                    talia[0][k] = talia[0][k + 1];
                    talia[1][k] = talia[1][k + 1];
                }
            }
        }
        taliaKociolka[0][liczbaKartaWKociolku + 1] = karta[0][0];
        taliaKociolka[1][liczbaKartaWKociolku + 1] = karta[1][0];
    }
   // FILE* plik;
   // plik = fopen("stan_gry.txt", "w");
   for (int i = 0; i < iloscLinii - 1; i++) {
        if (i == 0) {
            if (aktywnyGracz + 1 > liczbaGraczy) {
                //fprintf(plik, "active player = %d\n", 1);
                cout << "active player = " << 1 << endl;
            }
            else {
                //fprintf(plik, "active player = %d\n", aktywnyGracz + 1);
                cout << "active player = " << aktywnyGracz + 1 << endl;
            }
        }
        else if (i == (aktywnyGracz * 2) + 1) {
           // fprintf(plik, "%d player hand cards: ", aktywnyGracz);
            cout << aktywnyGracz << " player hand cards: ";
            for (int j = 0; j < liczbaKart; j++) {
                //fprintf(plik, "%d %s ", talia[0][j], tablicaKolorow[talia[1][j]]);
                 cout << talia[0][j] << " " << tablicaKolorow[talia[1][j]] << " ";
            }
            //fprintf(plik, "\n");
            cout << endl;
        }
        else if (i == (aktywnyGracz * 2) + 2) {
            //fprintf(plik, "%d player deck cards: ", aktywnyGracz);
            cout << aktywnyGracz << " player deck cards: ";
            if (czyEksplozja == 1) {
                for (int j = 0; j < liczbaKartDeck + liczbaKartaWKociolku + 2; j++) {
                    //fprintf(plik, "%d %s ", deck[0][j], tablicaKolorow[deck[1][j]]);
                    cout << deck[0][j] << " " << tablicaKolorow[deck[1][j]] << " ";
                }
            }
            else {
                for (int j = 0; j < liczbaKartDeck; j++) {
                    //fprintf(plik, "%d %s ", deck[0][j], tablicaKolorow[deck[1][j]]);
                    cout << deck[0][j] << " " << tablicaKolorow[deck[1][j]] << " ";
                }
            }
            //fprintf(plik, "\n");
            cout << endl;
        }
        else if (i == iloscLinii - liczbaKociolkow + kociolekMin) {
            if (czyEksplozja == 1) {
                //fprintf(plik, "%d pile cards:", kociolekMin + 1);
                cout << kociolekMin + 1 << " pile cards:" << endl;
            }
            else {
                //fprintf(plik, "%d pile cards: ", kociolekMin + 1);
                cout << kociolekMin + 1 << " pile cards: ";
                for (int j = 0; j < liczbaKartaWKociolku + 2; j++) {
                    //fprintf(plik, "%d %s ", taliaKociolka[0][j], tablicaKolorow[taliaKociolka[1][j]]);
                    cout << taliaKociolka[0][j] << " " << tablicaKolorow[taliaKociolka[1][j]] << " ";
                }
                //fprintf(plik, "\n");
                cout << endl;
            }
        }
        else {
            //fprintf(plik, "%s\n", wszystkieLinie[i]);
            cout << wszystkieLinie[i] << endl;
        }
    }
   // fclose(plik);
    for (int j = 0; j < 100; j++) {
             delete[]wszystkieLinie[j];
    }
    delete[]wszystkieLinie;
    for (int j = 0; j < 2; j++) {
        delete[]taliaKociolka[j];
        delete[]deck[j];
        delete[]talia[j];
        delete[]karta[j];
        delete[]kartaMax[j];
        delete[]kartaMin[j];
        delete[]scalonaMin[j];
        delete[]scalonaMax[j];
        delete[]parametryKociolka[j];
    }
    delete[]taliaKociolka;
    delete[]deck;
    delete[]talia;
    delete[]karta;
    delete[]kartaMax;
    delete[]kartaMin;
    delete[]scalonaMin;
    delete[]scalonaMax;
    delete[]talia;
    delete[]parametryKociolka;
}*/

/*void wyborOptymalnejKarty(int aktywnyGracz, int liczbaGraczy, int eksplozja) {
    char** wszystkieLinie = new char* [100];
    for (int i = 0; i < 100; i++) {
        wszystkieLinie[i] = new char[1000];
    }
    int iloscLinii = 0;
    wczytajGrePlik(wszystkieLinie, &iloscLinii);
    char tablicaKolorow[7][10] = { "green", "blue", "red", "violet", "yellow", "white", "black" };
    int suma[6] = { 0 };
    int liczbaKart = 0;
    int liczbaKartDeck = 0;
    int liczbaKociolkow = iloscLinii - 3 - (2 * liczbaGraczy);
    int adresKociolka = iloscLinii - liczbaKociolkow;
    int** kartaMax = new int* [2];
    int** karta = new int* [2];
    char** scalona = new char* [2];
    int** talia = new int* [2];
    int** deck = new int* [2];
    int** taliaKociolka = new int* [2];
    for (int i = 0; i < 2; i++) {
        kartaMax[i] = new int[1000];
        karta[i] = new int[1000];
        scalona[i] = new char[1000];
        talia[i] = new int[1000];
        deck[i] = new int[1000];
        taliaKociolka[i] = new int[1000];
    }
    int** parametryKociolka = new int* [2];
    for (int i = 0; i < 2; i++) {
        parametryKociolka[i] = new int[liczbaKociolkow];
    }
    for (int i = 0; i < 1000; i++) {
        kartaMax[0][i] = 0;
        kartaMax[1][i] = 0;
        karta[0][i] = 0;
        karta[1][i] = 0;
        talia[0][i] = 0;
        talia[1][i] = 0;
        deck[0][i] = 0;
        deck[1][i] = 0;
        taliaKociolka[0][i] = 0;
        taliaKociolka[1][i] = 0;
        scalona[0][i] = 0;
        scalona[1][i] = 0;
    }
    for (int i = 0; i < liczbaKociolkow; i++) {
        parametryKociolka[0][i] = 0;
        parametryKociolka[1][i] = 0;
    }
    sumaKociolkaIwiodącyKolor(wszystkieLinie, parametryKociolka, liczbaKociolkow, adresKociolka);
    int licznikMaxPomocniczy = 0;
    int max = -1;
    int* posortowaneWartosciTalii;
    taliaGracza(wszystkieLinie[(aktywnyGracz * 2) + 1], talia, &liczbaKart);
    deckGracza(wszystkieLinie[(aktywnyGracz * 2) + 2], deck, &liczbaKartDeck);
    for (int k = 0; k < liczbaKart + 1; k++) {
        if (talia[0][k] > max) {
            max = talia[0][k];
        }
    }
    licznikMaxPomocniczy = 0;
    posortowaneWartosciTalii = new int [liczbaKart];
    for (int i = 0; i < liczbaKart + 1; i++) {
        posortowaneWartosciTalii[i] = 0;
    }
    for (int i = 0; i < liczbaKart + 1; i++) {
        posortowaneWartosciTalii[i] = talia[0][i];
    }
    qsort(posortowaneWartosciTalii, liczbaKart + 1, sizeof(*posortowaneWartosciTalii), qsortFunckja);

    for (int k = 0; k < liczbaKart + 1; k++) {
        if (talia[0][k] == max) {
            kartaMax[0][licznikMaxPomocniczy] = max;
            kartaMax[1][licznikMaxPomocniczy] = talia[1][k];
            licznikMaxPomocniczy++;
        }
    }
    for (int i = 0; i < licznikMaxPomocniczy; i++) {
        int liczba = kartaMax[0][i];
        if (liczba < 10) {
            scalona[0][i] = liczba + '0';
        }
        else {
            int cyfra2 = liczba % 10;
            int cyfra1 = liczba / 10;
            scalona[0][i] = cyfra1 + '0';
            scalona[1][i] = cyfra2 + '0';
        }
    }
    int sprawdzoneKarty = 0;
    int czyEksplozja = 0;
    int sumaMin = INT_MAX;
    int kociolekMax = 0;
    int numerKarty = -1;
    while (sprawdzoneKarty <= liczbaKart) {
        sumaMin = INT_MAX;
        kociolekMax = 0;
        numerKarty = -1;
        for (int j = 0; j < licznikMaxPomocniczy; j++) {
            int istniejeKociolekWKolorzeKarty = 0;
            int suma = 0;
            int kociolek = 0;
            if (kartaMax[1][j] != 0) {
                for (int i = 0; i < liczbaKociolkow; i++) {

                    if (parametryKociolka[1][i] == kartaMax[1][j]) {
                        istniejeKociolekWKolorzeKarty = 1;
                        suma = parametryKociolka[0][i];
                        kociolek = i;
                        if (suma < sumaMin) {
                            sumaMin = suma;
                            kociolekMax = kociolek;
                            numerKarty = j;
                        }
                        break;
                    }
                }
                if (istniejeKociolekWKolorzeKarty == 0) {
                    for (int i = 0; i < liczbaKociolkow; i++) {
                        if (parametryKociolka[1][i] == 7) {
                            suma = 0;
                            kociolek = i;
                            if (suma < sumaMin) {
                                sumaMin = suma;
                                kociolekMax = kociolek;
                                numerKarty = j;
                            }
                            break;
                        }
                    }
                }

            }
            else {
                for (int i = 0; i < liczbaKociolkow; i++) {
                    suma = parametryKociolka[0][i];
                    kociolek = i;
                    if (suma < sumaMin) {
                        sumaMin = suma;
                        kociolekMax = kociolek;
                        numerKarty = j;
                    }
                    break;
                }
            }
        }
        sprawdzoneKarty += licznikMaxPomocniczy;
        if (sumaMin + kartaMax[0][numerKarty] > eksplozja) {
            czyEksplozja = 1;
            int nowyMax = -1;
            for (int j = 0; j < liczbaKart; j++) {
                if (posortowaneWartosciTalii[liczbaKart - j] < max){
                    nowyMax = posortowaneWartosciTalii[liczbaKart - j];
                    break;
                }
            }
            licznikMaxPomocniczy = 0;
            for (int k = 0; k < liczbaKart + 1; k++) {
                if (talia[0][k] == nowyMax) {
                    kartaMax[0][licznikMaxPomocniczy] = nowyMax;
                    kartaMax[1][licznikMaxPomocniczy] = talia[1][k];
                    licznikMaxPomocniczy++;
                }
            }
            for (int i = 0; i < licznikMaxPomocniczy; i++) {
                int liczba = kartaMax[0][i];
                if (liczba < 10) {
                    scalona[0][i] = liczba + '0';
                }
                else {
                    int cyfra2 = liczba % 10;
                    int cyfra1 = liczba / 10;
                    scalona[0][i] = cyfra1 + '0';
                    scalona[1][i] = cyfra2 + '0';
                }
            }
            max = nowyMax;


        }
        else {
            czyEksplozja = 0;
            karta[0][0] = kartaMax[0][numerKarty];
            karta[1][0] = kartaMax[1][numerKarty];
            sprawdzoneKarty = liczbaKart;
            break;
        }
    }
    if (czyEksplozja == 1) {
        wyborNajmniejszejLubNajwiekszejKarty(aktywnyGracz, liczbaGraczy, eksplozja);
    }
    else {
        int liczbaKartaWKociolku = 0;
        deckGracza(wszystkieLinie[iloscLinii - liczbaKociolkow + kociolekMax], taliaKociolka, &liczbaKartaWKociolku);
        int j = 0;
        for (j = 0; j < liczbaKart + 1; j++) {
            if ((talia[0][j] == karta[0][0]) && (talia[1][j] == karta[1][0])) {
                for (int k = j; k < liczbaKart; k++) {
                    talia[0][k] = talia[0][k + 1];
                    talia[1][k] = talia[1][k + 1];
                }
            }
        }
        taliaKociolka[0][liczbaKartaWKociolku + 1] = karta[0][0];
        taliaKociolka[1][liczbaKartaWKociolku + 1] = karta[1][0];
        // FILE* plik;
        // plik = fopen("stan_gry.txt", "w");
        for (int i = 0; i < iloscLinii - 1; i++) {
            if (i == 0) {
                if (aktywnyGracz + 1 > liczbaGraczy) {
                    //fprintf(plik, "active player = %d\n", 1);
                    cout << "active player = " << 1 << endl;
                }
                else {
                    //fprintf(plik, "active player = %d\n", aktywnyGracz + 1);
                    cout << "active player = " << aktywnyGracz + 1 << endl;
                }
            }
            else if (i == (aktywnyGracz * 2) + 1) {
                // fprintf(plik, "%d player hand cards: ", aktywnyGracz);
                cout << aktywnyGracz << " player hand cards: ";
                for (int j = 0; j < liczbaKart; j++) {
                    //fprintf(plik, "%d %s ", talia[0][j], tablicaKolorow[talia[1][j]]);
                    cout << talia[0][j] << " " << tablicaKolorow[talia[1][j]] << " ";
                }
                //fprintf(plik, "\n");
                cout << endl;
            }
            else if (i == (aktywnyGracz * 2) + 2) {
                //fprintf(plik, "%d player deck cards: ", aktywnyGracz);
                cout << aktywnyGracz << " player deck cards: ";
                if (czyEksplozja == 1) {
                    for (int j = 0; j < liczbaKartDeck + liczbaKartaWKociolku + 2; j++) {
                        //fprintf(plik, "%d %s ", deck[0][j], tablicaKolorow[deck[1][j]]);
                        cout << deck[0][j] << " " << tablicaKolorow[deck[1][j]] << " ";
                    }
                }
                else {
                    for (int j = 0; j < liczbaKartDeck; j++) {
                        //fprintf(plik, "%d %s ", deck[0][j], tablicaKolorow[deck[1][j]]);
                        cout << deck[0][j] << " " << tablicaKolorow[deck[1][j]] << " ";
                    }
                }
                //fprintf(plik, "\n");
                cout << endl;
            }
            else if (i == iloscLinii - liczbaKociolkow + kociolekMax) {
                if (czyEksplozja == 1) {
                    //fprintf(plik, "%d pile cards:", kociolekMin + 1);
                    cout << kociolekMax + 1 << " pile cards:" << endl;
                }
                else {
                    //fprintf(plik, "%d pile cards: ", kociolekMin + 1);
                    cout << kociolekMax + 1 << " pile cards: ";
                    for (int j = 0; j < liczbaKartaWKociolku + 2; j++) {
                        //fprintf(plik, "%d %s ", taliaKociolka[0][j], tablicaKolorow[taliaKociolka[1][j]]);
                        cout << taliaKociolka[0][j] << " " << tablicaKolorow[taliaKociolka[1][j]] << " ";
                    }
                    //fprintf(plik, "\n");
                    cout << endl;
                }
            }
            else {
                //fprintf(plik, "%s\n", wszystkieLinie[i]);
                cout << wszystkieLinie[i] << endl;
            }
        }
        // fclose(plik);
        for (int j = 0; j < 100; j++) {
            delete[]wszystkieLinie[j];
        }
        delete[]wszystkieLinie;
        for (int j = 0; j < 2; j++) {
            delete[]taliaKociolka[j];
            delete[]deck[j];
            delete[]talia[j];
            delete[]karta[j];
            delete[]kartaMax[j];
            delete[]scalona[j];
            delete[]parametryKociolka[j];
        }
        delete[]taliaKociolka;
        delete[]deck;
        delete[]talia;
        delete[]karta;
        delete[]kartaMax;
        delete[]scalona;
        delete[]parametryKociolka;
        delete[]posortowaneWartosciTalii;
    }
}*/
