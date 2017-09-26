/*
ID: eulerphi
PROG: barn1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>

int main() {
    std::ofstream fout("barn1.out");
    std::ifstream fin("barn1.in");

    int M, S, C;
    fin >> M >> S >> C;

    std::vector<int> stalls;
    int current = 0;
    for (int i = 0; i < C; ++i) {
        fin >> current;
        stalls.push_back(current);
    }
    std::sort(stalls.begin(), stalls.end());


    std::vector<int> segments;
    for (size_t i = 1; i < stalls.size(); ++i) {
        int length = stalls[i] - stalls[i - 1] - 1;
        if (length > 0) {
            segments.push_back(length);
        }
    }
    std::sort(segments.begin(), segments.end(), [](int x, int y) {
        return x > y;
    });

    int total_blocked = stalls.back() - stalls.front() + 1;

    size_t max = std::min(M - 1, static_cast<int>(segments.size()));
    for (size_t i = 0; i < max; ++i) {
        total_blocked -= segments[i];
    }

    fout << total_blocked << std::endl;

    return 0;
}
