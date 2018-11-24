#include <iostream>
#include <bitset>
#include <unordered_set>

using namespace std;

int main() {

    int liczbaGraczy;
    cin >> liczbaGraczy;

    int liczbaMeczow;
    cin >> liczbaMeczow;

    using gracz = bitset<64>;
    gracz historiaGraczy[liczbaGraczy];

    int sklady[liczbaMeczow][liczbaGraczy];

    for (int numerMeczu = 0; numerMeczu < liczbaMeczow; numerMeczu++) {
            for (int i = 0; i < liczbaGraczy; i++) {
                int numerZawodnika;
                cin >> numerZawodnika;
                sklady[numerMeczu][i] = numerZawodnika;
            }
    }

    for (int numerMeczu = 0; numerMeczu < liczbaMeczow; numerMeczu++) {

        // gracze z pierwszej drużyny
        for (int i = 0; i < liczbaGraczy / 2; i++) {
            int numer = sklady[numerMeczu][i];
            historiaGraczy[numer - 1][numerMeczu] = 0;
        }
        // gracze z drugiej drużyny
        for (int i = liczbaGraczy / 2; i < liczbaGraczy; i++) {
            int numer = sklady[numerMeczu][i];
            historiaGraczy[numer - 1][numerMeczu] = 1;
        }
    }

    unordered_set<unsigned long long> historie;

    for (int i = 0; i < liczbaGraczy; i++) {
        gracz g = historiaGraczy[i];
        unsigned long long identyfikator = g.to_ullong();
        historie.insert(identyfikator);
    }

    if (historie.size() == liczbaGraczy) {
        cout << "TAK";
    }
    else {
        cout << "NIE";
    }

    return 0;

}
