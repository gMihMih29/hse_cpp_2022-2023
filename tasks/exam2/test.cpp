#include <catch.hpp>
#include <iostream>

TEST_CASE("Empty", "[Enumerate]") {
    std::string input;
    std::cin >> input;
    int day = (input[9] - '0') * 10 + (input[8] - '0');
    int month = (input[7] - '0') * 10 + (input[6] - '0');
    int year = (input[4] - '0') * 1000 + (input[3] - '0') * 100 + (input[1] - '0') * 10 + (input[0] - '0');
    if (day > 31 || day == 0 || month > 12 || month == 0) {
        std::cout << "NO";
        return;
    }
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        std::cout << "YES";
        return;
    }
    if (month == 2) {
        if (year % 4 == 0) {
            if (day > 29) {
                std::cout << "NO";
                return;
            }
        } else {
            if (day > 28) {
                std::cout << "NO";
                return;
            }
        }
        std::cout << "YES";
        return;
    }
    if (day > 30) {
        std::cout << "NO";
        return;
    }
    std::cout << "YES";
    REQUIRE(true);
}