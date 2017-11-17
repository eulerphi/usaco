/*
ID: eulerphi
PROG: pprime
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <bitset>
#include <ctime>
#include <cmath>
#include <unordered_map>

const int MAX_B = 100000000;
const int MAX_N = MAX_B / 2;

int64_t a, b;
std::vector<int64_t> result;
std::bitset<MAX_N + 1> sieve;

bool IsPalindrome(int64_t x) {
    int64_t forward = x;

    int64_t reverse = 0;
    while (x > 0) {
        reverse *= 10;
        reverse += x % 10;
        x /= 10;
    }

    while (forward > 0 || reverse > 0) {
        int64_t f = forward > 0 ? forward % 10 : 0;
        int64_t r = reverse > 0 ? reverse % 10 : 0;
        if (f != r) return false;

        forward /= 10;
        reverse /= 10;
    }

    return true;
}

void Sieve() {
    const int64_t MAX = b / 2;

    for (int64_t i = 1; i <= MAX; ++i) {
        for (int64_t j = i; (i + j + 2 * i * j) <= MAX; ++j) {
            int64_t k = i + j + 2 * i * j;
            sieve[k] = true;
        }
    }

    for (int64_t i = a / 2; i <= MAX; ++i) {
        int64_t k = 2 * i + 1;
        if (sieve[i] == false && IsPalindrome(k)) {
            result.push_back(k);
        }
    }
}

std::unordered_map<int, std::vector<int>> _cached;

std::vector<int> GetCandidates(int width) {
    if (_cached.find(width) != _cached.end()) {
        return _cached[width];
    }


    std::vector<int> prior = { 0 };
    if (width > 2) {
        prior = GetCandidates(width - 1);
    }

    std::vector<int> candidates;
    int hi_coefficient = static_cast<int>(std::pow(10, width - 1));
    for (int i = 1; i <= 9; ++i) {
        for (auto p : prior) {
            candidates.push_back((hi_coefficient * i) + (10 * p) + i);
        }
    }

    _cached[width] = candidates;
    return _cached[width];
}

bool IsPrime(int candidate) {
    int square_root = static_cast<int>(std::sqrt(candidate));
    for (int i = 2; i <= square_root; ++i) {
        if (candidate % i == 0) {
            return false;
        }
    }

    return true;
}

void Solve() {
    int max_width = static_cast<int>(std::ceil(std::log10(b)));
    for (int w = 2; w <= max_width; ++w) {
        auto cs = GetCandidates(w);
        for (auto c : cs) {
            if (c > b) break;

            if (IsPrime(c)) {
                result.push_back(c);
            }
        }
    }
}

int main() {
    std::ofstream fout("pprime.out");
    std::ifstream fin("pprime.in");

    fin >> a >> b;

    //Sieve();
    Solve();
    
    for (auto &r : result)
        fout << r << std::endl;

    return 0;
}
