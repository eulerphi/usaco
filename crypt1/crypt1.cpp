/*
ID: eulerphi
PROG: crypt1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_set>

bool IsValid(int c, int length, const std::unordered_set<int> &digits) {
    int max = static_cast<int>(std::pow(10, length));
    if (c >= max) {
        return false;
    }

    for (int i = 0; i < length; ++i) {
        if (digits.find(c % 10) == digits.end()) {
            return false;
        }

        c /= 10;
    }

    return true;
}

bool IsValidProduct(int c1, int c2, const std::unordered_set<int> &digits) {
    if (!IsValid(c1 * c2, 4, digits)) {
        return false;
    }

    do {
        if (!IsValid(c1 * (c2 % 10), 3, digits)) {
            return false;
        }

        c2 /= 10;
    } while (c2 > 0);

    return true;
}

std::vector<int> GetCandidates(int length, const std::unordered_set<int> &digits) {
    std::vector<int> cs;

    int max = static_cast<int>(std::pow(10, length));
    for (int c = 1; c < max; ++c) {
        if (IsValid(c, length, digits)) {
            cs.push_back(c);
        }
    }

    return cs;
}

int main() {
    std::ofstream fout("crypt1.out");
    std::ifstream fin("crypt1.in");

    int N = 0;
    fin >> N;

    int d = 0;
    std::unordered_set<int> digits;
    for (int i = 0; i < N; ++i) {
        fin >> d;
        digits.insert(d);
    }

    auto cs1 = GetCandidates(3, digits);
    auto cs2 = GetCandidates(2, digits);

    int solutions = 0;
    for (auto c1 : cs1) {
        for (auto c2 : cs2) {
            if (IsValidProduct(c1, c2, digits)) {
                ++solutions;
            }
        }
    }

    fout << solutions << std::endl;

    return 0;
}
