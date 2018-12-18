#include <iostream>
#include <set>
#include <cmath>
#include <climits>
#include <cassert>

using namespace std;
constexpr int LICZBA_LISCI = 131072;
constexpr int LICZBA_WEZLOW = 262144;
using para = pair<int, int>;

para drzewoMin[LICZBA_WEZLOW];
para drzewoMax[LICZBA_WEZLOW];

set<para, greater<para>> kandydaciMax[100001]; // Przechowuje zbior kandydatow na max zaczynajacych sie w danym czasie
set<para> kandydaciMin[100001]; // Przechowuje zbior kandydatow na min zaczynajacych sie w danym czasie.

int poczatkiPrzedzialu[100001]; // Poczatek sesji o danym ID.

// Wstawia dana sesje do drzewa i ewentualnie poprawia drzewo idac sciezka do korzenia.
void wstaw(int poczatekSesji, bool min) { // Wstawiamy sesje do obu drzew przedzialowych.
    int indeks = LICZBA_WEZLOW / 2 + poczatekSesji - 1;
    para sesja;
    if (min) {
        auto it = kandydaciMin[poczatekSesji].begin();
        if (it != kandydaciMin[poczatekSesji].end()) { // Set kandydatow jest niepusty.
            sesja = *it;
        }
        else {
            sesja = make_pair(INT_MAX, 1);
        }
    }
    else {
        auto it = kandydaciMax[poczatekSesji].begin();
        if (it != kandydaciMax[poczatekSesji].end()) { // Set kandydatow jest niepusty.
            sesja = *it;
        }
        else {
            sesja = make_pair(INT_MIN, 1);
        }
    }

    if (min) { // Wstawiamy do drzewa min.
        drzewoMin[indeks] = sesja;
        while (indeks != 1) {
            indeks /= 2;
            if (drzewoMin[indeks * 2].first < drzewoMin[indeks * 2 + 1].first) {
                drzewoMin[indeks] = drzewoMin[indeks * 2];
            }
            else {
                drzewoMin[indeks] = drzewoMin[indeks * 2 + 1];
            }
        }
    }
    else { // Wstawiamy do drzewa max.
        drzewoMax[indeks] = sesja;
        while (indeks != 1) {
            indeks /= 2;
            if (drzewoMax[indeks * 2].first > drzewoMax[indeks * 2 + 1].first) {
                drzewoMax[indeks] = drzewoMax[indeks * 2];
            }
            else {
                drzewoMax[indeks] = drzewoMax[indeks * 2 + 1];
            }
        }
    }
}

// Nie usuwasz przedzialow z seta.
// Chcemy sprawdzic czy usuwamy w lisciu jest przedzial o id ktory usuwamy.
void aktualizuj(para sesja) { // Usuwanie konkretnego przedzialu a nie tego z liscia? Sprawdzamy w lisciu czy to jest ten przedzial.
    int poczatekUsuwanego = poczatkiPrzedzialu[sesja.second];
    int indeks = LICZBA_WEZLOW / 2 + poczatekUsuwanego - 1;

    kandydaciMax[poczatekUsuwanego].erase(sesja);
    kandydaciMin[poczatekUsuwanego].erase(sesja);

    if (drzewoMin[indeks].second == sesja.second) {
        wstaw(poczatekUsuwanego, true);
    }
    if (drzewoMax[indeks].second == sesja.second) {
        wstaw(poczatekUsuwanego, false);
    }
}

para queryMin(para przedzial) {
    int va = LICZBA_LISCI - 1 + przedzial.first;
    int vb = LICZBA_LISCI - 1 + przedzial.second;
    para wynik;
    if (drzewoMin[va].first < drzewoMin[vb].first) {
        wynik = drzewoMin[va];
    }
    else {
        wynik = drzewoMin[vb];
    }

    while (va / 2 != vb / 2) {
        if (va % 2 == 0) {
            if (drzewoMin[va + 1].first < wynik.first) {
                wynik = drzewoMin[va + 1];
            }
        }

        if (vb % 2 == 1) {
            if (drzewoMin[vb - 1].first < wynik.first) {
                wynik = drzewoMin[vb - 1];
            }
        }

        va /= 2;
        vb /= 2;
    }

    return wynik;
}

para queryMax(para przedzial) {
    int va = LICZBA_LISCI - 1 + przedzial.first;
    int vb = LICZBA_LISCI - 1 + przedzial.second;
    para wynik;

    if (drzewoMax[va].first > drzewoMax[vb].first) {
        wynik = drzewoMax[va];
    }
    else {
        wynik = drzewoMax[vb];
    }

    while (va /2 != vb / 2) {
        if (va % 2 == 0) {
            if (drzewoMax[va + 1].first > wynik.first) {
                wynik = drzewoMax[va + 1];
            }
        }

        if (vb % 2 == 1) {
            if (drzewoMax[vb - 1].first > wynik.first) {
                wynik = drzewoMax[vb - 1];
            }
        }

        va /= 2;
        vb /= 2;
    }

    return wynik;
}

int in(para sesja) {
    para query = queryMin(sesja);
    int wynik = query.second;
    if (query.first <= sesja.second) {
        assert(query.first != INT_MAX);
        aktualizuj(query);
        return wynik;
    }
    return -1;
}

int some(para sesja) {
    para query = queryMin(sesja);
    int wynik = query.second;
    if (query.first != INT_MAX) {
        aktualizuj(query);
        return wynik;
    }

    query = queryMax(make_pair(1, sesja.first));
    if (query.first >= sesja.first) {
        wynik = query.second;
        aktualizuj(query);
        return wynik;
    }
    return -1;
}

int over(para sesja) {
    para query = queryMax(make_pair(1, sesja.first));
    int wynik = query.second;
    if (query.first >= sesja.second) {
        aktualizuj(query);
        return wynik;
    }

    return -1;
}

int none(para sesja) {
    para lewy, prawy;
    if (sesja.first > 1) { // Moga byc jakies sesje na lewo.
        lewy = queryMin(make_pair(1, sesja.first - 1));
        if (lewy.first < sesja.first) {
            aktualizuj(lewy);
            return lewy.second;
        }
    }

    if (sesja.second < 100000) { // Moga byc jakies sesje na prawo.
        prawy = queryMin(make_pair(sesja.second + 1, 100000));
        if (prawy.first != INT_MAX) {
            aktualizuj(prawy);
            return prawy.second;
        }
    }
    return -1;

}

int main() {

    for (int i = 0; i < LICZBA_WEZLOW; i++) {
        drzewoMax[i] = make_pair(INT_MIN, 1); // Straznik - dowolny wstawiony element bedzie lepszy od niego.
        drzewoMin[i] = make_pair(INT_MAX, 1); // Straznik - dowolny wstawiony element bedzie lepszy od niego.
    }

    int n;
    cin >> n;

    for (int ID = 1; ID <= n; ID++) {
        int poczatekSesji, koniecSesji;
        cin >> poczatekSesji >> koniecSesji;
        para sesja = make_pair(koniecSesji, ID); // Sesję przechowujemy jako parę intów - koniec sesji i ID (zaczyna sie od 1).
        kandydaciMax[poczatekSesji].insert(sesja);
        kandydaciMin[poczatekSesji].insert(sesja);
        poczatkiPrzedzialu[ID] = poczatekSesji; // Zapamietujemy poczatek przedzialu sesji o danym ID.
    }

    // Wczytalismy wszystkie podejrzane sesje. Teraz chcemy na ich podstawie zbudowac drzewo przedzialowe.
    // Dla kazdego liscia bierzemy pierwszy element z odpowiedniego setu, wstawiamy go do liscia w drzewie i poprawiamy drzewo
    // idac sciezka w gore do korzenia.
    for (int poczatekSesji = 1; poczatekSesji <= 100000; poczatekSesji++) {
        auto it = kandydaciMin[poczatekSesji].begin();
        if (it != kandydaciMin[poczatekSesji].end()) { // Set kandydatow jest niepusty.
            wstaw(poczatekSesji, true);
        }

        it = kandydaciMax[poczatekSesji].begin();
        if (it != kandydaciMax[poczatekSesji].end()) { // Set kandydatow jest niepusty.
            wstaw(poczatekSesji, false);
        }
    }

    // Mamy zbudowane drzewo. Teraz wczytujemy zapytania.
    int liczbaZapytan;
    cin >> liczbaZapytan;

    for (int i = 0; i < liczbaZapytan; i++) {
        string polecenie;
        cin >> polecenie;

        int poczatekPrzedzialu, koniecPrzedzialu;
        cin >> poczatekPrzedzialu >> koniecPrzedzialu;
        para sesja = make_pair(poczatekPrzedzialu, koniecPrzedzialu);
        int wynik = -2;

        if (polecenie == "in") {
            wynik = in(sesja);
        }
        if (polecenie == "over") {
            wynik = over(sesja);
        }
        if (polecenie == "some") {
            wynik = some(sesja);
        }
        if (polecenie == "none") {
            wynik = none(sesja);
        }

        cout << wynik;
        if (i < liczbaZapytan - 1) {
            cout << " ";
        }
    }
    return 0;
}