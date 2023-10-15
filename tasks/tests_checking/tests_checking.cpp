#include "tests_checking.h"

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> papers;
    for (const auto& i : student_actions) {
        if (i.side == Side::Top) {
            papers.push_front(i.name);
        } else {
            papers.push_back(i.name);
        }
    }
    std::vector<std::string> answer;
    answer.reserve(queries.size());
    for (const auto& i : queries) {
        answer.push_back(papers.at(i - 1));
    }
    return answer;
}
