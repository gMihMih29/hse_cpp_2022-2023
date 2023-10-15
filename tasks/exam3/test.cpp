#include <algorithm>
#include <catch.hpp>
#include <iostream>
#include <vector>

TEST_CASE("Empty", "[Enumerate]") {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> v;
    v.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        int x = 0;
        int y = 0;
        std::cin >> x >> y;
        v.emplace_back(x, y);
    }
    sort(v.begin(), v.end(), [](std::pair<int, int> first, std::pair<int, int> second) {
        return first.first * second.second - second.first * first.second < 0;
    });
    for (const auto& el : v) {
        std::cout << el.first << ' ' << el.second << std::endl;
    }
    REQUIRE(true);
}