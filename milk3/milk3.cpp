/*
ID: eulerphi
PROG: milk3
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <unordered_set>

uint8_t A, B, C;
std::vector<uint8_t> result;
std::unordered_set<uint32_t> seen;

struct Combo {
    uint8_t a;
    uint8_t b;
    uint8_t c;

    operator uint32_t() const {
        return (a << 16) + (b << 8) + c;
    }
};

void Solve(Combo &c);

void Transfer(Combo &c, uint8_t &from, uint8_t &to, uint8_t to_max) {
    if (from == 0) return;

    uint8_t diff = to_max - to;
    diff = std::min(diff, from);
    from -= diff;
    to += diff;

    Solve(c);

    from += diff;
    to -= diff;
}

void Solve(Combo &c) {
    if (seen.find(c) != seen.end()) {
        return;
    }

    if (c.a == 0) {
        result.push_back(c.c);
    }

    seen.insert(c);

    Transfer(c, c.a, c.b, B);
    Transfer(c, c.a, c.c, C);
    Transfer(c, c.b, c.a, A);
    Transfer(c, c.b, c.c, C);
    Transfer(c, c.c, c.a, A);
    Transfer(c, c.c, c.b, B);
}

int main() {
    std::ofstream fout("milk3.out");
    std::ifstream fin("milk3.in");

    {
        int a, b, c;
        fin >> a >> b >> c;
        A = static_cast<uint8_t>(a);
        B = static_cast<uint8_t>(b);
        C = static_cast<uint8_t>(c);
    }

    Combo c;
    c.a = 0;
    c.b = 0;
    c.c = C;

    Solve(c);

    std::sort(result.begin(), result.end());

    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) fout << " ";
        fout << static_cast<int>(result[i]);
    }

    fout << std::endl;

    return 0;
}
