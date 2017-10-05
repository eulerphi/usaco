/*
ID: eulerphi
PROG: wormhole
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

int N;

struct Hole {
    int x;
    int y;
    int index;

    static std::vector<Hole> GetAll(std::ifstream &fin) {
        std::vector<Hole> hs;
        for (int i = 0; i < N; ++i) {
            hs.emplace_back();
            hs.back().index = i;
            fin >> hs.back().x;
            fin >> hs.back().y;
        }

        return hs;
    }
};

struct Map {
    static const int UNMAPPED = 15;

    std::unordered_map<int, int> map;

    void Clear(int index) {
        map[index] = UNMAPPED;
    }

    void ClearAll() {
        for (int i = 0; i < N; ++i) Clear(i);
    }

    int Get(int index) const {
        auto it = map.find(index);
        return it != map.end() ? it->second : UNMAPPED;
    }

    bool IsSet(int index) const {
        return Get(index) != UNMAPPED;
    }

    void Set(int from, int to) {
        map[from] = to;
    }

    void Print(const std::vector<Hole> &hs) const {
        std::cout << "------------------" << std::endl;
        for (int i = 0; i < N; ++i) {
            int j = Get(i);
            std::cout
                << "(" << hs[i].x << "," << hs[i].y << ") ->"
                << "(" << hs[j].x << "," << hs[j].y << "),"
                << std::endl;
        }
        std::cout << "------------------" << std::endl;
    }

    static std::vector<Map> GetAll() {
        Map m;
        std::vector<Map> ms;
        GetAll(0, m, ms);

        return ms;
    }


private:
    static void GetAll(
        int index, Map m, std::vector<Map> &out_ms) {

        if (index == N) {
            out_ms.push_back(m);
            return;
        }

        if (m.IsSet(index)) {
            GetAll(index + 1, m, out_ms);
        }
        else {
            for (int i = index + 1; i < N; ++i) {
                if (!m.IsSet(i)) {
                    m.Set(index, i);
                    m.Set(i, index);
                    GetAll(index + 1, m, out_ms);
                    m.Clear(i);
                }
            }

            m.Clear(index);
        }
    }
};

Map GetConnected(std::vector<Hole> hs) {
    std::sort(hs.begin(), hs.end(), [](Hole h1, Hole h2) {
        if (h1.y == h2.y) return h1.x < h2.x;
        return h1.y < h2.y;
    });

    //std::cout << hs[0].index << ": " << hs[0].x << " " << hs[0].y << std::endl;
    Map c;
    for (int i = 1; i < N; ++i) {
        Hole pre = hs[i - 1];
        Hole cur = hs[i];
        //std::cout << cur.index << ": " << cur.x << " " << cur.y << std::endl;

        if (cur.y == pre.y) {
            c.Set(pre.index, cur.index);
        }
    }

    return c;
}

bool IsSafe(
    const Hole &h,
    const std::vector<Hole> &hs,
    const Map &m,
    const Map &c) {

    std::unordered_set<int> seen;
    int prev_warp = Map::UNMAPPED;

    int cur = h.index;
    do {
        int next_warp = m.Get(cur);
        if (next_warp != prev_warp) {
            if (seen.find(cur) != seen.end()) {
                return false;
            }

            seen.insert(cur);
            prev_warp = cur;
            cur = next_warp;
        }
        else if (c.IsSet(cur)) {
            prev_warp = Map::UNMAPPED;
            cur = c.Get(cur);
        }
        else {
            return true;
        }
    } while (true);
}

bool IsSafe(
    const std::vector<Hole> &hs,
    const Map &m,
    const Map &c) {

    for (const auto &h : hs) {
        if (!IsSafe(h, hs, m, c)) return false;
    }

    return true;
}

int main() {
    std::ofstream fout("wormhole.out");
    std::ifstream fin("wormhole.in");

    fin >> N;

    auto hs = Hole::GetAll(fin);
    auto c = GetConnected(hs);
    auto ms = Map::GetAll();

    int total_bad = 0;
    for (const auto m : ms) {
        if (!IsSafe(hs, m, c)) ++total_bad;
    }

    fout << total_bad << std::endl;

    return 0;
}
