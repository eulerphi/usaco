/*
ID: eulerphi
PROG: skidesign
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>

int N;
const int MAX_DIFF = 17;

int Cost(const std::vector<int> &xs, int lo, int hi) {
    int total = 0;
    for (const auto &x : xs) {
        if (x < lo) {
            total += (lo - x) * (lo - x);
        }
        else if (x > hi) {
            total += (x - hi) * (x - hi);
        }
    }

    return total;
}

int main() {
    std::ofstream fout("skidesign.out");
    std::ifstream fin("skidesign.in");

    fin >> N;

    std::vector<int> xs;
    for (int i = 0; i < N; ++i) {
        xs.emplace_back();
        fin >> xs.back();
    }

    int min_cost = std::numeric_limits<int>::max();
    for (int i = 0; i < 100 - MAX_DIFF; ++i) {
        int cost = Cost(xs, i, i + MAX_DIFF);
        min_cost = std::min(min_cost, cost);
    }

    fout << min_cost << std::endl;
    return 0;
}
