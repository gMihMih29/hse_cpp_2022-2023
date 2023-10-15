#include "sort_students.h"

#include <algorithm>

int Date::Compare(const Date& d1, const Date& d2) {
    if (d1.year < d2.year) {
        return 1;
    } else if (d1.year > d2.year) {
        return -1;
    }
    if (d1.month < d2.month) {
        return 1;
    } else if (d1.month > d2.month) {
        return -1;
    }
    if (d1.day < d2.day) {
        return 1;
    } else if (d1.day > d2.day) {
        return -1;
    }
    return 0;
}

bool CmpDate(Student s1, Student s2) {
    int cmp_result = Date::Compare(s1.birth_date, s2.birth_date);
    if (cmp_result != 0) {
        return cmp_result > 0;
    }
    if (s1.last_name < s2.last_name) {
        return true;
    } else if (s1.last_name > s2.last_name) {
        return false;
    }
    return s1.name < s2.name;
}

bool CmpName(Student s1, Student s2) {
    if (s1.last_name != s2.last_name || s1.name != s2.name) {
        if (s1.last_name < s2.last_name) {
            return true;
        } else if (s1.last_name > s2.last_name) {
            return false;
        }
    }
    int cmp_result = Date::Compare(s1.birth_date, s2.birth_date);
    return cmp_result > 0;
}

void SortStudents(std::vector<Student>& students, SortKind sort_kind) {
    if (sort_kind == SortKind::Date) {
        std::sort(students.begin(), students.end(), CmpDate);
    } else {
        std::sort(students.begin(), students.end(), CmpName);
    }
}
