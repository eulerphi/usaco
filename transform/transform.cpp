/*
ID: eulerphi
PROG: transform
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>

void ReadArray(std::ifstream &fin, bool (&arr)[10][10], int n) {
    char c;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> c;
            arr[i][j] = c == '@';
        }
    }
}

bool Compare(bool (&x)[10][10], bool (&y)[10][10], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (x[i][j] != y[i][j]) {
                return false;
            }
        }
    }

    return true;
}

void Rotate90(bool (&xs)[10][10], int n) {
    std::vector<bool> values;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            values.push_back(xs[n - j - 1][i]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            xs[i][j] = values[n * i + j];
        }
    }
}

void Rotate180(bool (&xs)[10][10], int n) {
    std::vector<bool> values;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            values.push_back(xs[n - i - 1][n - j - 1]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            xs[i][j] = values[n * i + j];
        }
    }
}

void Rotate270(bool (&xs)[10][10], int n) {
    std::vector<bool> values;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            values.push_back(xs[j][n - i - 1]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            xs[i][j] = values[n * i + j];
        }
    }
}

void Reflect(bool (&xs)[10][10], int n) {
    bool temp;

    const int mid = n / 2;
    for (int c = 0; c < mid; ++c) {
        for (int r = 0; r < n; ++r) {
            temp = xs[r][c];
            xs[r][c] = xs[r][n - c - 1];
            xs[r][n - c - 1] = temp;
        }
    }
}

int FindTransformation(
    bool (&xs)[10][10],
    bool (&ys)[10][10],
    int n)
{
    for (int r = 90; r < 360; r += 90) {
        Rotate90(xs, n);
        if (Compare(xs, ys, n)) {
            return r == 90  ? 1
                 : r == 180 ? 2
                 : 3;
        }
    }

    Rotate90(xs, n);
    Reflect(xs, n);
    for (int r = 0; r < 360; r += 90) {
        if (Compare(xs, ys, n)) {
            return r == 0 ? 4 : 5;
        }

        Rotate90(xs, n);
    }

    Reflect(xs, n);
    return Compare(xs, ys, n) ? 6 : 7;
}

int main() {
    std::ofstream fout("transform.out");
    std::ifstream fin("transform.in");

    int N;
    fin >> N;

    bool xs[10][10];
    bool ys[10][10];
    ReadArray(fin, xs, N);
    ReadArray(fin, ys, N);

    fout << FindTransformation(xs, ys, N) << std::endl;
    return 0;
}
