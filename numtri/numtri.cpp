/*
ID: eulerphi
PROG: numtri
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>

std::ofstream fout("numtri.out");
std::ifstream fin("numtri.in");

int R, result;
std::vector<int> data;

void Load() {
    int value;
    for (int r = 1; r <= R; ++r) {
        for (int i = 0; i < r; ++i) {
            fin >> value;
            data.push_back(value);
        }
    }
}

int GetMaxParent(int i, int r, int parent) {
    if (i == 0) return data[parent + i];
    if (i == r - 1) return data[parent + i - 1];
    return std::max(data[parent + i], data[parent + i - 1]);
}

void Solve() {
    result = data[0];

    int index = 1, parent = 0;
    for (int r = 2; r <= R; ++r) {
        //std::cout << "--------------" << r << std::endl;
        for (int i = 0; i < r; ++i) {
            int max = GetMaxParent(i, r, parent);

            //std::cout << i << ": " << data[index + i];
            data[index + i] += max;
            //std::cout << " -> " << data[index + i] << std::endl;

            result = std::max(result, data[index + i]);
        }
        
        index += r;
        parent += r - 1;
    }
}

int main() {
    fin >> R;

    Load();
    Solve();

    fout << result << std::endl;

    return 0;
}
