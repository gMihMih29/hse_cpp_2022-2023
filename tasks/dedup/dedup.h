#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

using std::string;

template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> result;
    result.reserve(items.size());
    for (size_t i = 0; i < items.size(); ++i) {
        result.push_back(std::make_unique<T>(*items[i]));
    }
    return result;
}

template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    std::vector<std::shared_ptr<T>> result;
    result.reserve(items.size());
    for (size_t i = 0; i < items.size(); ++i) {
        bool flag = false;
        for (size_t j = 0; j < result.size(); ++j) {
            if (*items[i] == *result[j]) {
                result.push_back(result[j]);
                flag = true;
                break;
            }
        }
        if (!flag) {
            result.push_back(std::make_shared<T>(*items[i]));
        }
    }
    return result;
}
