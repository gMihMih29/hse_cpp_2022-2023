#include "provinces.h"

int64_t CountPassports(const std::vector<int>& provinces) {
    std::multiset<int64_t> mergable_provinces;
    for (const int& population : provinces) {
        mergable_provinces.insert(population);
    }
    int64_t val1 = 0;
    int64_t val2 = 0;
    int64_t answer = 0;
    while (mergable_provinces.size() > 1) {
        val1 = *mergable_provinces.begin();
        mergable_provinces.erase(mergable_provinces.begin());
        val2 = *mergable_provinces.begin();
        mergable_provinces.erase(mergable_provinces.begin());
        answer += val1 + val2;
        mergable_provinces.insert(val1 + val2);
    }
    return answer;
}
