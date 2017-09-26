/*
ID: eulerphi
PROG: milk
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>

struct FarmInfo {
    /*
    Farmer(int price, int amount) :
        price(price), amount(amount)
    {
        // empty
    }
    */

    static std::vector<FarmInfo> LoadSorted(std::ifstream &in, int count) {
        std::vector<FarmInfo> fs;

        FarmInfo f;
        for (int i = 0; i < count; ++i) {
            in >> f;
            fs.push_back(f);
        }

        std::sort(fs.begin(), fs.end(), [](const FarmInfo &x, const FarmInfo &y) {
            return x.price < y.price;
        });

        return fs;
    }

    friend std::ifstream& operator>>(std::ifstream &in, FarmInfo &info)  
    {  
        in >> info.price >> info.amount;  
        return in;  
    }

    int price;
    int amount;
};

int main() {
    std::ofstream fout("milk.out");
    std::ifstream fin("milk.in");

    int N, M;
    fin >> N >> M;

    std::vector<FarmInfo> fs = FarmInfo::LoadSorted(fin, M);

    int cost = 0;
    for (const auto &f : fs) {
        if (N == 0) { break; }

        int amount = std::min(N, f.amount);
        N -= amount;
        cost += f.price * amount;
    }

    fout << cost << std::endl;

    return 0;
}
