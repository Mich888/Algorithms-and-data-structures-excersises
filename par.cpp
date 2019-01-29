#include <iostream>
#include <math.h>
#include <cassert>

constexpr int MAX_N = 500001;

int n;
int parent[MAX_N];
int left[MAX_N];
int right[MAX_N];
int depth[MAX_N];
int links[19][MAX_N];

std::pair<int, int> farDown[MAX_N];
std::pair<int, int> farUp[MAX_N];
std::pair<int, int> far[MAX_N];

int liczbaZapytan;

int fllog;

void countDepth(int index, int currentDepth) {
    int leftSon = left[index];
    int rightSon = right[index];
    depth[left[index]] = depth[right[index]] = currentDepth;
    currentDepth++;

    if (left[index] != -1) {
        countDepth(left[index], currentDepth);
    }
    if (right[index] != -1) {
        countDepth(right[index], currentDepth);
    }
}

void countLinks() {

    for (int v = 1; v <= n; v++) {
        links[0][v] = parent[v];
    }

    for (int i = 1; i <= fllog; i++) {
        for (int v = 1; v <= n; v++) {
            if (links[i - 1][v] == -1) {
                links[i][v] = -1;
            }
            else {
                links[i][v] = links[i - 1][links[i - 1][v]];
            }
        }
    }
}

int ancestor(int v, int h) {
    int res = v;
    int i = (int)(log2(n));
    int p = 2 << (i - 1);

    while (h > 0) {
        if (p > h) {
            p /= 2;
            i--;
        }
        else {
            res = links[i][res];
            h = h - p;
        }
    }

    return res;
}

int lca(int u, int v) {
    int du = depth[u];
    int dv = depth[v];

    if (du < dv) {
        v = ancestor(v, dv - du);
        dv = depth[v];
    }
    else if (du > dv) {
        u = ancestor(u, du - dv);
        du = depth[u];
    }

    if (u == v) {
        return u;
    }

    int i = fllog;

    while (i >= 0) {
        if (links[i][u] != links[i][v]) {
            u = links[i][u];
            v = links[i][v];
        }
        i--;
    }

    return parent[u];
}

void countFarDown(int u) {
    int leftSon = left[u];
    int rightSon = right[u];

    // Post-order
    if (leftSon != -1) {
        countFarDown(leftSon);
    }
    if (rightSon != -1) {
        countFarDown(rightSon);
    }

    std::pair<int, int> c1 = std::make_pair(0, u);
    std::pair<int, int> c2;
    std::pair<int, int> c3;

    if (left[u] == -1) {
        c2 = std::make_pair(-1, -1);
    }
    else {
        std::pair<int, int> p = farDown[leftSon];
        int d = p.first;
        int v = p.second;
        c2 = std::make_pair(d + 1, v);
    }

    if (right[u] == -1) {
        c3 = std::make_pair(-1, -1);
    }
    else {
        std::pair<int, int> p = farDown[rightSon];
        int d = p.first;
        int v = p.second;
        c3 = std::make_pair(d + 1, v);
    }

    if (c2.first > c3.first) {
        if (c2.first > 0) {
            farDown[u] = c2;
        }
        else {
            farDown[u] = c1;
        }
    }
    else {
        if (c3.first > 0) {
            farDown[u] = c3;
        } else {
            farDown[u] = c1;
        }
    }
}

void countFarUp(int u) {

    std::pair<int, int> c1 = std::make_pair(0, u);
    std::pair<int, int> c2;
    std::pair<int, int> c3;

    if (parent[u] == -1) {
        c2 = std::make_pair(-1, -1);
        c3 = std::make_pair(-1, -1);
    }
    else {
        int par = parent[u];
        std::pair<int, int> p = farUp[par];
        int d = p.first;
        int v = p.second;
        c2 = std::make_pair(d + 1, v);
        int lson = left[par];
        int rson = right[par];

        if (lson == u) {
            if (rson == -1) { // sibling.
                c3 = std::make_pair(-1, -1);
            }
            else {
                p = farDown[rson];
                d = p.first;
                v = p.second;
                c3 = std::make_pair(d + 2, v);
            }
        }
        else { // right[par] == u
            if (lson == -1) {
                c3 = std::make_pair(-1, -1);
            }
            else {
                p = farDown[lson];
                d = p.first;
                v = p.second;
                c3 = std::make_pair(d + 2, v);
            }
        }
    }

    if (c2.first > c3.first) {
        if (c2.first > 0) {
            farUp[u] = c2;
        }
        else {
            farUp[u] = c1;
        }
    }
    else {
        if (c3.first > 0) {
            farUp[u] = c3;
        }
        else {
            farUp[u] = c1;
        }
    }

    if (left[u] != -1) {
        countFarUp(left[u]);
    }
    if (right[u] != -1) {
        countFarUp(right[u]);
    }
}

void countFar() {
    for (int u = 1; u <= n; u++) {
        std::pair<int, int>first = farDown[u];
        std::pair<int, int>second = farUp[u];

        if (first.first > second.first)  {
            far[u] = first;
        }
        else {
            far[u] = second;
        }
    }
}

int dist(int u, int d) {
    std::pair<int, int> p = far[u];
    int dMax = p.first;
    int v = p.second;

    if (d > dMax) {
        return -1;
    }

    int l = lca(u, v);
    int d1 = depth[u] - depth[l];
    int d2 = depth[v] - depth[l];

    if (d <= d1) {
        return ancestor(u, d);
    }
    else {
        return ancestor(v, dMax - d);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    fllog = (int)log2(n);
    parent[1] = -1;

    for (int i = 1; i <= n; i++) { // Budowanie drzewa.
        int l, p;
        std::cin >> l >> p;
        left[i] = l;
        right[i] = p;
        parent[l] = parent[p] = i;
    }

    depth[1] = 0;
    countDepth(1, 1);
    countLinks();
    countFarDown(1);
    countFarUp(1);
    countFar();

    std::cin >> liczbaZapytan;
    for (int i = 0; i < liczbaZapytan; i++) {
        int a, d;
        std::cin >> a >> d;
        std::cout << dist(a, d) << "\n";
    }

    return 0;
}