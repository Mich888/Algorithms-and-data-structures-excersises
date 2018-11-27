#include <iostream>
#include <queue>
#include <vector>
using namespace std;

constexpr int MAX_N = 100000;

int liczbaProjektow;
int liczbaZaleznosci;
int minimalnaLiczbaProjektow;

vector<int> nb[MAX_N];
int stopnieWierzcholkow[MAX_N];
int wagiWierzcholkow[MAX_N];

using wierzcholek = pair<int, int>;

int wynik = 0;
int ileZrealizowanych = 0;

int comp(int a, int b) { return wagiWierzcholkow[a] > wagiWierzcholkow[b]; }

priority_queue<int, vector<int>, decltype(&comp)> kolejka(comp);

void wczytajWagi() {
    for (int i = 0; i < liczbaProjektow; i++) {
        int wagaProjektu;
        cin >> wagaProjektu;
        wagiWierzcholkow[i] = wagaProjektu;
    }
}

void stworzGraf() {
    for (int i = 0; i < liczbaZaleznosci; i++) {
        int pierwszy;
        int drugi;
        cin >> pierwszy >> drugi;
        stopnieWierzcholkow[pierwszy - 1]++;
        nb[drugi - 1].push_back(pierwszy - 1);
    }
}

void zrealizujProjekt(int indeksWierzcholka) {
    if (wagiWierzcholkow[indeksWierzcholka] > wynik) {
        wynik = wagiWierzcholkow[indeksWierzcholka];
    }

    for (int w: nb[indeksWierzcholka]) {
        stopnieWierzcholkow[w]--;
        if (stopnieWierzcholkow[w] == 0) {
            kolejka.push(w);
        }
    }
    stopnieWierzcholkow[indeksWierzcholka] = -1;
    nb[indeksWierzcholka].clear();
    ileZrealizowanych++;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> liczbaProjektow;
    cin >> liczbaZaleznosci;
    cin >> minimalnaLiczbaProjektow;

    for (int i = 0; i < liczbaProjektow; i++) {
        stopnieWierzcholkow[i] = 0;
    }

    wczytajWagi();
    stworzGraf();

    for (int i = 0; i < liczbaProjektow; i++) {
        if (stopnieWierzcholkow[i] == 0) {
            kolejka.push(i);
            stopnieWierzcholkow[i] = -1;
        }
    }
    while (ileZrealizowanych < minimalnaLiczbaProjektow) {
        int indeks = kolejka.top();
        kolejka.pop();
        zrealizujProjekt(indeks);
    }

    cout << wynik;
    return 0;
}

