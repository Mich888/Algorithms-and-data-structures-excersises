#include <iostream>
#include <set>

using namespace std;
using interv = pair<int, int>;
int sumaPomalowanych = 0;
set<interv> autostrada;

int dlugoscOdcinka(int poczatek, int koniec) {
    return koniec - poczatek + 1;
}

void zmodyfikujPrzedzialy(interv in, bool czyUsunac) {
    if (autostrada.empty()) {
        if (!czyUsunac) {
            autostrada.insert(in); // Wstawiamy przedzial w calosci.
            sumaPomalowanych += dlugoscOdcinka(in.first, in.second);
        }
    }
    else { // Jest jakis przedzial w secie, mozemy zmniejszyc iterator i dostaniemy jakis przedzial.
        auto it = autostrada.lower_bound(make_pair(in.first, 1));
        int poczatekPrzedzialu = in.first;
        int koniecPrzedzialu = in.second;

        if (it != autostrada.begin()) {
            it--; // Dostajemy przedzial ktory jest mniejszy od szukanego, nie zrobilismy previous od begin.
            // Rozpatrujemy przedzial, ktory jest na lewo od wstawianego.

            interv odcinek = *it; // Odcinek na lewo od wstawianego.

            if (odcinek.second < poczatekPrzedzialu) { // Przedzial na lewo nie pokrywa sie z naszym.
                it++;
            }
            else {
                if (!czyUsunac) { //
                    poczatekPrzedzialu = odcinek.first; // dodajemy szerszy przedzial;
                    if (odcinek.second >= in.second) {
                        return;
                    }
                    it++; // Usuwamy przedzial i dostajemy iterator na nastepny element.
                    autostrada.erase(odcinek);
                    sumaPomalowanych -= dlugoscOdcinka(odcinek.first, odcinek.second); // musimy zwiekszyc it jesli nie usuwamy
                }
                else {
                    int nowyKoniec = in.first; // Koniec pomniejszonego przedzialu.
                    it++;
                    autostrada.erase(odcinek);
                    sumaPomalowanych -= dlugoscOdcinka(odcinek.first, odcinek.second);
                    if (odcinek.first < in.first) {
                        interv newInterv = make_pair(odcinek.first, nowyKoniec - 1);
                        autostrada.insert(newInterv);
                        sumaPomalowanych += dlugoscOdcinka(newInterv.first, newInterv.second);
                    }
                    if (odcinek.second > in.second) {
                        interv newInterv = make_pair(in.second + 1, odcinek.second);
                        autostrada.insert(newInterv);
                        sumaPomalowanych += dlugoscOdcinka(newInterv.first, newInterv.second);
                    }
                }
            }
        }
        // Na pewno mozemy dodac początek przedzialu, mozliwe że pokrywa się gdzies w srodku z innym.
        // Iterator jest na nastepnym elemencie.
        while (it != autostrada.end() && it->first <= koniecPrzedzialu) {
            if (it->second <= koniecPrzedzialu) {
                sumaPomalowanych -= dlugoscOdcinka(it->first, it->second);
                it = autostrada.erase(it);
            }
            else {
                if (!czyUsunac) {
                    koniecPrzedzialu = it->second;
                    sumaPomalowanych -= dlugoscOdcinka(it->first, it->second);
                    it = autostrada.erase(it);
                }
                else {
                    interv odcinek = *it;
                    it++;
                    sumaPomalowanych -= dlugoscOdcinka(odcinek.first, odcinek.second);
                    autostrada.erase(odcinek);
                    interv wstaw = make_pair(in.second + 1, odcinek.second);
                    autostrada.insert(wstaw);
                    sumaPomalowanych += dlugoscOdcinka(wstaw.first, wstaw.second);
                }
            }
        }
        if (!czyUsunac) {
            sumaPomalowanych += dlugoscOdcinka(poczatekPrzedzialu, koniecPrzedzialu);
            autostrada.insert(make_pair(poczatekPrzedzialu, koniecPrzedzialu));
        }
    }
}

int main() {
    int dlAutostrady;
    int liczbaNocy;

    cin >> dlAutostrady;
    cin >> liczbaNocy;

    for (int i = 0; i < liczbaNocy; i++) {
        int begin;
        cin >> begin;

        int end;
        cin >> end;

        interv przedzial(begin, end);
        char akcja;
        cin >> akcja;

        if (akcja == 'B') {
            zmodyfikujPrzedzialy(przedzial, false);
        }
        else {
            zmodyfikujPrzedzialy(przedzial, true);
        }
        cout << sumaPomalowanych << "\n";
    }
    return 0;
}