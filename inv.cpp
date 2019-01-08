#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int liczbaWierzcholkow;
    cin >> liczbaWierzcholkow;

    int max = 0;
    vector<int> konceSkladowych;
    konceSkladowych.push_back(0);

    int wierzcholki[liczbaWierzcholkow];

    for (int i = 0; i < liczbaWierzcholkow; i++) {
        cin >> wierzcholki[i];
    }

    for (int  i = 0; i < liczbaWierzcholkow; i++) {
        if (wierzcholki[i] > max) {
            max = wierzcholki[i];
        }

        if (max == i + 1) { // odcinamy spojna skladowa
            konceSkladowych.push_back(i + 1);
        }
    }

    cout << konceSkladowych.size() - 1 << "\n";

    for (int i = 1; i < konceSkladowych.size(); i++) {

        int poprzedni = konceSkladowych[i - 1];
        int aktualny = konceSkladowych[i];
        cout << aktualny - poprzedni << " ";

        for (int i = poprzedni + 1; i <= aktualny; i++) {
            cout << i;

            if (i == aktualny) {
                cout << "\n";
            }
            else {
                cout << " ";
            }
        }
    }
}
