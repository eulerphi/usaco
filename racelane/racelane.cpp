#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>

static const uint16_t LANES = 9;
static const uint16_t METERS = 500;

struct Event {
    Event(uint16_t m, uint16_t l, bool o) : meter(m), lane(l), on(o)
    { }

    uint16_t lane;
    uint16_t meter;
    bool on;
};

std::vector<Event> GetEvents(uint16_t num) {
    std::vector<Event> es;

    uint16_t s, e, l;
    for (uint16_t i = 0; i < num; ++i) {
        std::cin >> s >> e >> l;
        es.push_back(Event(s, l, false));
        es.push_back(Event(e, l, true));
    }

    return es;
}

bool HasPaintlessLane(const std::vector<bool> ls) {
    for (uint16_t i = 1; i < ls.size(); ++i) {
        if (!ls[i] && !ls[i - 1]) {
            return true;
        }
    }

    return false;
}

void RunTestCase() {
    uint16_t B = 0;
    std::cin >> B;

    auto es = GetEvents(B);
    std::sort(es.begin(), es.end(), [](const Event &a, const Event &b) {
        if (a.meter < b.meter) return true;
        if (a.meter == b.meter) return !a.on && b.on;
        return false;
    });

    std::vector<bool> ls(LANES + 1, true);

    uint16_t result = 0;

    size_t es_idx = 0;
    for (uint16_t m = 1; m <= METERS; ++m) {
        while (es_idx < es.size() && es[es_idx].meter == m && !es[es_idx].on) {
            ls[es[es_idx].lane] = es[es_idx].on;
            ++es_idx;
        }

        result += HasPaintlessLane(ls) ? 1 : 0;

        while (es_idx < es.size() && es[es_idx].meter == m) {
            ls[es[es_idx].lane] = es[es_idx].on;
            ++es_idx;
        }
    }

    std::cout << METERS - result << std::endl;
}


int main() {
    uint16_t T = 0;
    std::cin >> T;
    for (uint16_t t = 0; t < T; ++t) {
        RunTestCase();
    }

    return 0;
}
