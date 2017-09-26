/*
ID: eulerphi
PROG: namenum
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>

std::unordered_set<std::string> dictionary;

std::unordered_map<char, std::vector<char>> num_to_char = {
    { '2', { 'A', 'B', 'C' } },
    { '3', { 'D', 'E', 'F' } },
    { '4', { 'G', 'H', 'I' } },
    { '5', { 'J', 'K', 'L' } },
    { '6', { 'M', 'N', 'O' } },
    { '7', { 'P', 'R', 'S' } },
    { '8', { 'T', 'U', 'V' } },
    { '9', { 'W', 'X', 'Y' } }
};

void combinations(
    const std::string &id,
    std::string &word,
    size_t idx,
    std::vector<std::string> &out_words) {

    if (idx >= id.size()) {
        if (dictionary.count(word) > 0) {
            out_words.push_back(word);
        }
        return;
    }

    for (int i = 0; i < 3; ++i) {
        word[idx] = num_to_char[id[idx]][i];
        combinations(id, word, idx + 1, out_words);
    }
}

void combinations(
    const std::string &id,
    std::vector<std::string> &out_words) {
    std::string word(id.size(), ' ');
    combinations(id, word, 0, out_words);
}

int main() {
    std::ofstream fout("namenum.out");
    std::ifstream fin("namenum.in");
    std::ifstream din("dict.txt");

    std::string name;
    while (din >> name) {
        dictionary.insert(name);
    }

    std::string id;
    fin >> id;

    std::vector<std::string> names;
    combinations(id, names);

    for (const auto &n : names) {
        fout << n << std::endl;
    }

    if (names.empty()) {
        fout << "NONE" << std::endl;
    }


    return 0;
}
