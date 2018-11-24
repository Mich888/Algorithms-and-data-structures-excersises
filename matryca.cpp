#include <iostream>
using namespace std;

int main() {

    string napis;
    cin >> napis;
    int odleglosc = 0;
    int rozmiar = napis.size();
    int ileLiter = 0;

    int koncowyIndeks = rozmiar - 1; // indeks ostatniej litery w napisie
    while (napis[koncowyIndeks] == '*' && koncowyIndeks > 0) {
        koncowyIndeks--;
    }

    int poczatkowyIndeks = 0; // indeks pierwszej litery w napisie
    while (poczatkowyIndeks < rozmiar && napis[poczatkowyIndeks] == '*') {
        poczatkowyIndeks++;
    }
    if (poczatkowyIndeks > koncowyIndeks) {
        rozmiar = 1;
    }
    int minodleglosc = rozmiar;
    // same gwiazdki
    char ostatniaWczytanaLitera = napis[poczatkowyIndeks];
    char ostatniWczytanyZnak = ostatniaWczytanaLitera;
    ileLiter++;
    //cout << "znak: " << ostatniaWczytanaLitera << endl;

    if (poczatkowyIndeks == napis.size() || poczatkowyIndeks == koncowyIndeks) {
        cout << 1;
        return 0;
    }
    else {

        for (int i = poczatkowyIndeks + 1; i <= koncowyIndeks; i++) {
            if (napis[i] == '*' || napis[i] == ostatniaWczytanaLitera) {

                odleglosc++;
                //cout << "odl: " << odleglosc << endl;


            }
            // Wczytaliśmy inną literę
            else {
                if (ostatniWczytanyZnak != '*') {
                    //cout << "koniec" << endl;
                    cout << rozmiar;
                    return 0;
                }
                ostatniaWczytanaLitera = napis[i];
                ileLiter++;
                minodleglosc = min(odleglosc, minodleglosc);
                //cout << "min: " << minodleglosc << endl;
                odleglosc = 0;
            }

            ostatniWczytanyZnak = napis[i];
        }
    }

    //cout << "poczat: " << poczatkowyIndeks << endl;
    //cout << "kon: " << koncowyIndeks << endl;
    //cout << "rozmiar: " << rozmiar << endl;
    //cout << "mindoleglosc: " << minodleglosc << endl;



    if (ileLiter == 1) {
        cout << 1;
        return 0;
    }
    cout << rozmiar - minodleglosc;
    return 0;
}