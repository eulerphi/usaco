/*
ID: eulerphi
PROG: palsquare
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <unordered_map>

static const std::string digits = "0123456789ABCDEFGHIJK";

std::string Convert(int x, int B) {
    std::string s;
    while (x > 0) {
        int c = x % B;
        s += digits[c];
        x /= B;
    }

    // NOTE : s is in reverse order, but that
    // is ok for checking palindromes
    return s;
}

bool IsPalindrome(const std::string &str) {
    size_t j = str.size() - 1;
    for (size_t i = 0; i < j; ++i, --j) {
        if (str[i] != str[j]) {
            return false;
        }
    }

    return true;
}

int main() {
    std::ofstream fout("palsquare.out");
    std::ifstream fin("palsquare.in");

    int B;
    fin >> B;

    for (int i = 1; i <= 300; ++i) {
        int square = i * i;
        std::string str = Convert(square, B);

        if (IsPalindrome(str)) {
            std::string val = Convert(i, B);
            std::reverse(val.begin(), val.end());
            fout << val << " " << str << std::endl;
        }
    }

    return 0;
}
