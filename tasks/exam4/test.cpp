#include <algorithm>
#include <catch.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

TEST_CASE("Empty", "[Enumerate]") {
    std::map<std::string, size_t> dict;
    std::string input;
    while (std::cin >> input) {
        std::string buffer;
        for (char el : input) {
            if (el == ' ') {
                dict[buffer] += 1;
                buffer.clear();
            } else {
                buffer.push_back(el);
            }
        }
        if (!buffer.empty()) {
            dict[buffer] += 1;
        }
    }
    std::vector<std::pair<std::string, size_t>> v;
    v.reserve(dict.size());
    for (const auto& el : dict) {
        v.emplace_back(el);
    }
    sort(v.begin(), v.end(),
         [](const std::pair<std::string, size_t>& first, const std::pair<std::string, size_t>& second) {
             if (first.second < second.second) {
                 return true;
             }
             if (first.second > second.second) {
                 return false;
             }
             return first.first > second.first;
         });
    reverse(v.begin(), v.end());
    for (const auto& el : v) {
        std::cout << el.first << std::endl;
    }
    REQUIRE(true);
}