#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    if (path.empty()) {
        return static_cast<std::string>(current_working_dir);
    }
    size_t left_index = 0;
    size_t right_index = 0;
    std::deque<std::string_view> s;
    if (path[0] != '/') {
        left_index = 1;
        right_index = 1;
        while (right_index < current_working_dir.length()) {
            while (right_index < current_working_dir.length() && current_working_dir[right_index] != '/') {
                ++right_index;
            }
            s.push_back(current_working_dir.substr(left_index, right_index - left_index));
            while (right_index < current_working_dir.length() && current_working_dir[right_index] == '/') {
                ++right_index;
            }
            left_index = right_index;
        }
    }
    left_index = 0;
    right_index = 0;
    while (right_index < path.length()) {
        while (right_index < path.length() && path[right_index] != '/') {
            ++right_index;
        }
        if (left_index != right_index) {
            if (path.substr(left_index, right_index - left_index) == "..") {
                if (!s.empty()) {
                    s.pop_back();
                }
            } else if (path.substr(left_index, right_index - left_index) != ".") {
                s.push_back(path.substr(left_index, right_index - left_index));
            }
        }
        while (right_index < path.length() && path[right_index] == '/') {
            ++right_index;
        }
        left_index = right_index;
    }
    std::string answer;
    if (s.empty()) {
        answer = "/";
    } else {
        while (!s.empty()) {
            answer += "/";
            answer += s.front();
            s.pop_front();
        }
    }
    return answer;
}
