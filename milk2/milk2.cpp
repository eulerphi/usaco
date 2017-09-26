/*
ID: eulerphi
PROG: milk2
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>

struct Event {
    static Event Start(uint32_t time)
    {
        Event e;
        e.time = time;
        e.start = true;
        return e;
    }

    static Event Stop(uint32_t time)
    {
        Event e;
        e.time = time;
        e.start = false;
        return e;
    }

    uint32_t time;
    bool start;
};

void LoadInput(std::vector<Event> &out_es) {
    std::ifstream fin("milk2.in");

    uint32_t num_lines = 0;
    fin >> num_lines;

    uint32_t start, stop;
    for (uint32_t i = 0; i < num_lines; ++i) {
        fin >> start;
        fin >> stop;
        out_es.push_back(Event::Start(start));
        out_es.push_back(Event::Stop(stop));
    }

    std::sort(out_es.begin(), out_es.end(), [](const Event &a, const Event &b) {
        return a.time != b.time
            ? a.time < b.time
            : a.start && !b.start;
    });
}

int main() {
    std::ofstream fout("milk2.out");

    std::vector<Event> es;
    LoadInput(es);

    uint32_t max = 0;
    uint32_t max_not = 0;

    uint32_t cnt = 0;
    uint32_t start = 0;
    uint32_t start_not = 0;
    for (const auto &e : es) {
        cnt += e.start ? 1 : -1;

        if (cnt == 1 && e.start) {
            start = e.time;
            if (start_not > 0) {
                max_not = std::max(max_not, e.time - start_not);
            }
        }

        if (cnt == 0 && !e.start) {
            start_not = e.time;
            max = std::max(max, e.time - start);
        }
    }

    fout << max << " " << max_not << std::endl;
    return 0;
}
