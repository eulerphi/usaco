/*
ID: eulerphi
PROG: ariprog
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <bitset>
#include <unordered_set>

int N, M, MAX_SQUARE;
const int MAX_M = 250;
std::bitset<2 * MAX_M * MAX_M + 1> bisquares;

struct Match {
    int a;
    int b;
};

void CalculateBisquares() {
    for (int p = 0; p <= M; ++p) {
        for (int q = 0; q <= M; ++q) {
            bisquares.set(p * p + q * q);
        }
    }
}

void Find(int a, int b, std::vector<Match> &matches) {
    //std::cout << "====== { a: " << a << ", b: " << b << " }" << std::endl;

    const int max_b = (N - 1) * b;
    int len = 0;
    for (int i = a; a + max_b <= MAX_SQUARE; i += b) {
        if (len  == N) {
            matches.emplace_back();
            matches.back().a = a;
            matches.back().b = b;

            a += b;
            --len;
        }

        /*
        std::cout
            << "a: " << a << ", "
            << "i: " << i << ", "
            << "l: " << len << ", "
            << "t: " << bisquares.test(i) << std::endl;
        */

        if (bisquares.test(i)) {
            ++len;
        }
        else {
            a = i + b;
            len = 0;
        }
    }
}

int main() {
    std::ofstream fout("ariprog.out");
    std::ifstream fin("ariprog.in");

    fin >> N >> M;
    MAX_SQUARE = 2 * M * M;

    CalculateBisquares();

    /*
    std::cout << "Bisquares: ";
    for (int i = 0; i <= MAX_SQUARE; ++i) {
        std::cout << i << "=" << bisquares.test(i) << " ";
    }
    std::cout << std::endl;
    */

    std::vector<Match> matches;
    for (int b = 1; (N - 1) * b <= MAX_SQUARE; ++b) {
        for (int a = 0; a < b; ++a) {
            Find(a, b, matches);
        }
    }

    std::sort(matches.begin(), matches.end(), [](Match x, Match y) {
        return x.b < y.b || (x.b == y.b && x.a < y.a);
    });

    for (const auto &m : matches) {
        fout << m.a << " " << m.b << std::endl;
    }

    if (matches.size() == 0) {
        fout << "NONE" << std::endl;
    }

    return 0;
}
