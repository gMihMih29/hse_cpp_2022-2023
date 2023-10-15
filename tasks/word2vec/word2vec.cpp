#include "word2vec.h"

#include <cmath>
#include <vector>

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    if (vectors.empty()) {
        return std::vector<std::string>();
    }
    size_t dimensions = vectors[0].size();
    int64_t current_result = 0;
    std::vector<int64_t> scalar_prods;
    scalar_prods.reserve(vectors.size());
    for (size_t i = 0; i < vectors.size(); ++i) {
        current_result = 0;
        for (size_t j = 0; j < dimensions; ++j) {
            current_result += static_cast<int64_t>(vectors[i][j]) * vectors[0][j];
        }
        scalar_prods.push_back(current_result);
    }
    int64_t max = 0;
    int count_max = 0;
    bool is_first = true;
    for (size_t i = 1; i < vectors.size(); ++i) {
        if (max == scalar_prods[i]) {
            ++count_max;
        } else if (max < scalar_prods[i] || is_first) {
            max = scalar_prods[i];
            count_max = 1;
            is_first = false;
        }
    }
    std::vector<std::string> answer;
    answer.reserve(count_max);
    for (size_t i = 1; i < vectors.size(); ++i) {
        if (max == scalar_prods[i]) {
            answer.push_back(words[i]);
        }
    }
    return answer;
}
