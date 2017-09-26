/*
ID: eulerphi
PROG: dualpal
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>

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
    std::ofstream fout("dualpal.out");
    std::ifstream fin("dualpal.in");

    int N, S;
    fin >> N >> S;

    for (int i = S + 1; N > 0; ++i) {
        int count = 0;
        for (int B = 2; B <= 10 && count < 2; ++B) {
            std::string s = Convert(i, B);
            count += IsPalindrome(s) ? 1 : 0;
        }

        if (count >= 2) {
            fout << i << std::endl;
            --N;
        }
    }

    return 0;
}
