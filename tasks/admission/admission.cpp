#include "admission.h"

#include <algorithm>
#include <map>

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> sorted_applicants;
    sorted_applicants.reserve(applicants.size());
    for (const auto& i : applicants) {
        sorted_applicants.push_back(&i);
    }
    std::sort(sorted_applicants.begin(), sorted_applicants.end(), [](const Applicant* a1, const Applicant* a2) {
        if (a1->points != a2->points) {
            return a1->points > a2->points;
        }
        if (a1->student.birth_date.year != a2->student.birth_date.year) {
            return a1->student.birth_date.year < a2->student.birth_date.year;
        }
        if (a1->student.birth_date.month != a2->student.birth_date.month) {
            return a1->student.birth_date.month < a2->student.birth_date.month;
        }
        if (a1->student.birth_date.day != a2->student.birth_date.day) {
            return a1->student.birth_date.day < a2->student.birth_date.day;
        }
        return a1->student.name < a2->student.name;
    });
    AdmissionTable answer;
    std::map<std::string, size_t> left_places;
    for (const auto& u : universities) {
        left_places[u.name] = u.max_students;
    }
    for (const auto& a : sorted_applicants) {
        for (const auto& u : a->wish_list) {
            if (left_places[u] != 0) {
                answer[u].push_back(&a->student);
                --left_places[u];
                break;
            }
        }
    }
    return answer;
}
