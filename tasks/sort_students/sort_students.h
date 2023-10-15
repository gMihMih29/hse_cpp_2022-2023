#pragma once

#include <string>
#include <vector>

struct Date {
    int day = 0;
    int month = 0;
    int year = 0;
    static int Compare(const Date& d1, const Date& d2);
};

struct Student {
    std::string name;
    std::string last_name;
    Date birth_date;
};

enum class SortKind { Name, Date };

void SortStudents(std::vector<Student>& students, SortKind sort_kind);
