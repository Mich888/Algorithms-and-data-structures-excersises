#include <iostream>
using namespace std;

const int maks = 1000;
const int mod = 1000000000;

unsigned int ile_l[maks][maks];
unsigned int ile_r[maks][maks];


int main() {

    int n;
    cin >> n; // ile liczb wczytujemy
    int liczby[n]; // tablica reprezentująca nasz ciąg

    // wczytywanie liczb
    for (int i = 0; i < n; i++) {
        cin >> liczby[i];
    }

    // początkowe wypełnianie tablicy - jednoelementowe ciągi możemy dostać na 1 sposób
    for (int i = 0; i < n; i++) {
        ile_l[i][i] = 1;
        ile_r[i][i] = 0;
    }

    int j;
    // d - długość przedziału, i - pierwszy indeks
    for (int d = 1; d < n; d++) {
        for (int i = 0; i < n - d; i++) {
            j = i + d;
            ile_l[i][j] = (ile_l[i + 1][j] * (liczby[i] < liczby[i + 1])
                          + ile_r[i + 1][j] * (liczby[i] < liczby[j])) % mod;

            ile_r[i][j] = (ile_r[i][j - 1] * (liczby[j] > liczby[j - 1]) +
                          ile_l[i][j - 1] * (liczby[j] > liczby[i])) % mod;
        }
    }

    cout << (ile_l[0][n - 1] + ile_r[0][n - 1]) % mod << endl;
    return 0;
}
