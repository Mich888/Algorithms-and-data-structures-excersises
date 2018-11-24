#include <iostream>
#include <limits>
#include <string.h>
using namespace std;


const int maxLiczbaPol = 100000;
int teleportacja;
int utrudnienie;
char Tor[maxLiczbaPol];
long long Czas[maxLiczbaPol][17]; // Czas[i][s] - najkrótszy czas dojścia na pole n z pola i mając na nim skok s
// -1 - niewyliczona wartość, -2 - niewyliczona wartość ale już w tym stanie byliśmy
int PotegiDwojki[17];
int liczbaPol;

int infinity = numeric_limits<int>::max();

void rekurencja(int i, int s) {

    if (i == liczbaPol - 1) { // dotarliśmy na ostatnie pole, czas dojścia z ostatniego pola na ostatnie pole to 0.
        Czas[i][s] = 0;
        return;
    }

    long long pierwszaWartosc = -1;
    int nastepnePole = i + PotegiDwojki[s]; // pole na które skoczymy
    int czasPrzejscia = 1;
    int skok = s;
    bool czyGwiazdka = false;


    if (nastepnePole <= liczbaPol - 1) { // sprawdzamy, czy możemy wykonać skok

        switch (Tor[nastepnePole]) { // wywołujemy rekurencję dla skoku
            case '#':
                Czas[nastepnePole][skok] = infinity;
                break;
            case '*':
                if (skok < 16) {
                    skok++;
                    czyGwiazdka = true;
                }
                break;
            case '>':
                nastepnePole += teleportacja;
                break;
            case '<':
                nastepnePole -= teleportacja;
                break;
            case 'U':
                czasPrzejscia += utrudnienie;
                break;
        }
        if (Czas[nastepnePole][skok] == -1) {
            if (czyGwiazdka)
                Czas[i][skok - 1] = -2;
            else
                Czas[i][skok] = -2;

            rekurencja(nastepnePole, skok);
        }
        if (Czas[nastepnePole][skok] == -2 || Czas[nastepnePole][skok] == infinity) {  // już byliśmy na tym polu więc ta droga nie jest dobra
            pierwszaWartosc = infinity;
        }
        else {
            pierwszaWartosc = Czas[nastepnePole][skok] + czasPrzejscia; // przepełnienie gdy Czas[nastepnePole] to inf
        }
    }
    else {
        pierwszaWartosc = infinity;
    }

    nastepnePole = i + 1;
    long long drugaWartosc = -1;
    czasPrzejscia = 1;
    skok = s;
    czyGwiazdka = false;

    switch (Tor[nastepnePole]) { // wywołujemy rekurencję dla skoku
        case '#':
            Czas[nastepnePole][s] = infinity;
            break;
        case '*':
            if (skok < 16) {
                skok++;
                czyGwiazdka = true;
            }
            break;
        case '>':
            nastepnePole += teleportacja;
            break;
        case '<':
            nastepnePole -= teleportacja;
            break;
        case 'U':
            czasPrzejscia += utrudnienie;
            break;
    }

    if (Czas[nastepnePole][skok] == -1) {

        if (czyGwiazdka)
            Czas[i][skok - 1] = -2;
        else
            Czas[i][skok] = -2;

        rekurencja(nastepnePole, skok);
    }
    if (Czas[nastepnePole][skok] == -2 || Czas[nastepnePole][skok] == infinity) {  // już byliśmy na tym polu więc ta droga nie jest dobra
        drugaWartosc = infinity;
    }
    else {
        drugaWartosc = Czas[nastepnePole][skok] + czasPrzejscia; // przepełnienie gdy Czas[nastepnePole] to inf
    }

    Czas[i][s] = min(pierwszaWartosc, drugaWartosc);
}

int main() {

    cin >> liczbaPol;
    cin >> teleportacja;
    cin >> utrudnienie;

    for (int i = 0; i < liczbaPol; i++) {
        cin >> Tor[i];
    }

    for (int i = 0; i < 17; i++) {
        if (i == 0) {
            PotegiDwojki[i] = 2;
        }
        else {
            PotegiDwojki[i] = PotegiDwojki[i - 1] * 2;
        }
    }

    memset(Czas, -1, sizeof(Czas)); // początkowe wypełnienie tablicy
    rekurencja(0, 0);
    if (Czas[0][0] == infinity) {
        cout << -1;
    }
    else {
        cout << Czas[0][0];
    }

    return 0;
}
