#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

using coordinateAndId = pair<int, int>;
vector<coordinateAndId> xSorted;
vector<coordinateAndId> ySorted;

set<pair<int, int>> minHeap; // distance from source and id.

int main() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int numberOfIslands;
    cin >> numberOfIslands;

    long distanceFromSource[numberOfIslands];
    distanceFromSource[0] = 0;

    for (int i = 1; i < numberOfIslands; i++) {
        distanceFromSource[i] = INT_MAX;
    }

    coordinateAndId coordinates[numberOfIslands];

    for (int i = 0; i < numberOfIslands; i++) {
        int xCoordinate, yCoordinate;
        cin >> xCoordinate >> yCoordinate;

        xSorted.emplace_back(xCoordinate, i);
        ySorted.emplace_back(yCoordinate, i);

        coordinates[i] = {xCoordinate, yCoordinate};
    }

    sort(xSorted.begin(), xSorted.end());
    sort(ySorted.begin(), ySorted.end());

    set<int> neighbours[numberOfIslands]; // numery wysp sąsiadujących

    for (int i = 0; i < numberOfIslands; i++) {
        pair<int, int> island = coordinates[i]; // Wyspa, której sąsiadów szukamy.
        coordinateAndId xAndId = make_pair(island.first, i);

        auto node = lower_bound(xSorted.begin(), xSorted.end(), xAndId);
        if (node != xSorted.begin()) { // bierzemy poprzednią wyspę
            node--;
            neighbours[i].insert(node->second);
            node++;
        }

        if (node != xSorted.end()) {
            node++;
            neighbours[i].insert(node->second);
        }

        coordinateAndId yAndId = make_pair(island.second, i);
        node = lower_bound(ySorted.begin(), ySorted.end(), yAndId);

        if (node != ySorted.begin()) { // bierzemy poprzednia wyspe
            node--;
            neighbours[i].insert(node->second);
            node++;
        }

        if (node != ySorted.end()) { // bierzemy następna wyspe
            node++;
            neighbours[i].insert(node->second);
        }
    }

    minHeap.insert({0, 0}); // odleglosc, numer wyspy

    while (!minHeap.empty()) {
        pair<int, int> lowestDistanceAndId = *minHeap.begin();
        minHeap.erase(lowestDistanceAndId);

        int id = lowestDistanceAndId.second;
        pair<int, int> firstIsland = coordinates[id];

        for (auto &neighbour: neighbours[id]) { // rozpatrujemy sasiadow
            if (neighbour == numberOfIslands || neighbour < 0) {
                exit(2);
            }

            pair<int, int> secondIsland = coordinates[neighbour];

            int distanceBetweenIslands = min(abs(firstIsland.first - secondIsland.first),
                    abs(firstIsland.second - secondIsland.second));
            if (distanceFromSource[id] + distanceBetweenIslands < distanceFromSource[neighbour]) {

                minHeap.erase({distanceFromSource[neighbour], neighbour}); // usuwamy starego sasiada
                distanceFromSource[neighbour] = distanceFromSource[id] + distanceBetweenIslands; // relaksacja
                minHeap.insert({distanceFromSource[neighbour], neighbour}); // dodajemy zaktualizowanego sasiada.
            }
        }
    }

    cout << distanceFromSource[numberOfIslands - 1];
    return 0;
}