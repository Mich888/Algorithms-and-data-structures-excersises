#include <iostream>
#include <climits>
#include <cmath>
#include <vector>
#include <cassert>

using namespace std;

int main() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int numberOfProducts;
    cin >> numberOfProducts;

    long long prefixSum[numberOfProducts + 1]; // Z prawej strony.
    int lowestOdd[numberOfProducts + 1]; // Z prawej strony.
    int lowestEven[numberOfProducts + 1]; // Z prawej strony.
    int highestOdd[numberOfProducts + 1]; // Z lewej.
    int highestEven[numberOfProducts + 1]; // Z lewej.

    int productPrice[numberOfProducts + 1];

    for (int i = 1; i <= numberOfProducts; i++) {
        cin >> productPrice[i];
    }

    // Preprocessing.
    highestEven[0] = -1;
    highestOdd[0] = -1;

    for (int i = 1; i <= numberOfProducts; i++) {
        int price = productPrice[i];
        if (price % 2 == 0) {
            highestEven[i] = max(price, highestEven[i - 1]);
            highestOdd[i] = highestOdd[i - 1];
        }
        else {
            highestOdd[i] = max(price, highestOdd[i - 1]);
            highestEven[i] = highestEven[i - 1];
        }
    }

    lowestOdd[0] = INT_MAX;
    lowestEven[0] = INT_MAX;
    prefixSum[0] = 0;

    for (int i = numberOfProducts; i >= 0; i--) {
        int reversedIndex = numberOfProducts - i + 1;
        int price = productPrice[i];

        prefixSum[reversedIndex] = prefixSum[reversedIndex - 1] + price;

        if (price % 2 == 0) {
            lowestEven[reversedIndex] = min(lowestEven[reversedIndex - 1], price);
            lowestOdd[reversedIndex] = lowestOdd[reversedIndex - 1];
        }
        else {
            lowestOdd[reversedIndex] = min(lowestOdd[reversedIndex - 1], price);
            lowestEven[reversedIndex] = lowestEven[reversedIndex - 1];
        }
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        int howManyProducts;
        cin >> howManyProducts;

        long long sum = prefixSum[howManyProducts];

        if (sum % 2 == 1) {
            cout << sum << "\n";
        }
        else {
            int lowEven = lowestEven[howManyProducts];
            assert(lowEven == INT_MAX || lowEven % 2 == 0);
            int lowOdd = lowestOdd[howManyProducts];
            assert(lowOdd == INT_MAX || lowOdd % 2 == 1);

            int highEven = highestEven[numberOfProducts - howManyProducts];
            int highOdd = highestOdd[numberOfProducts - howManyProducts];

            long long res = -1;

            if (lowEven != INT_MAX && highOdd != -1) {
                res = max(res, sum - lowEven + highOdd);
            }

            if (lowOdd != INT_MAX && highEven != -1) {
                res = max(res, sum - lowOdd + highEven);
            }

            cout << res << "\n";
        }
    }

    return 0;
}