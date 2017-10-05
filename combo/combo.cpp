/*
ID: eulerphi
PROG: combo
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <unordered_set>

int N;

struct Combo {
    static const int LENGTH = 3;

    uint8_t d1;
    uint8_t d2;
    uint8_t d3;

    Combo(uint32_t value) :
        d1(0x00FF0000 & value),
        d2(0x0000FF00 & value),
        d3(0x000000FF & value)
    {
        // empty
    }

    Combo(std::ifstream &fin) {
        int x = 0;;
        for (int i = 0; i < LENGTH; ++i) {
            fin >> x;
            Set(x, i);
        }
    }

    int Get(int index) const {
        if (index == 0) {
            return d1;
        }
        else if (index == 1) {
            return d2;
        }
        else {
            return d3;
        }
    }

    void Set(int value, int index) {
        if (value < 1) value += N;
        value = value % N;
        value = value > 0 ? value : N;

        uint8_t v = static_cast<uint8_t>(value);
        if (index == 0) {
            d1 = v;
        }
        else if (index == 1) {
            d2 = v;
        }
        else {
            d3 = v;
        }
    }

    void Print() {
        std::cout << "{ " << static_cast<int>(d1)
                  << ", " << static_cast<int>(d2)
                  << ", " << static_cast<int>(d3)
                  << " }" << std::endl;
    }

    operator uint32_t() const {
        return (d1 << 16) + (d2 << 8) + d3;
    }
};

void GetCombos(
    const Combo &input,
    Combo &temp,
    int index,
    std::unordered_set<uint32_t> &out)
{
    if (index >= Combo::LENGTH) {
        out.insert(temp);
        return;
    }

    const std::vector<int> modifiers = { -2, -1, 0, 1, 2 };
    for (auto m : modifiers) {
        temp.Set(input.Get(index) + m, index);
        GetCombos(input, temp, index + 1, out);
    }
}

void GetCombos(
    const Combo &input,
    std::unordered_set<uint32_t> &out)
{
    auto temp = input;
    GetCombos(input, temp, 0, out);
}

int main() {
    std::ofstream fout("combo.out");
    std::ifstream fin("combo.in");

    fin >> N;

    std::unordered_set<uint32_t> cs;
    for (int num = 0; num < 2; ++num) {
        GetCombos(fin, cs);
    }

    fout << cs.size() << std::endl;

    return 0;
}
