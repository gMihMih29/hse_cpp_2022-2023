#pragma once

#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <utility>
#include <vector>

template <typename KeyT>
class UnorderedSet {
public:
    UnorderedSet() : n_elements_(0) {
    }

    explicit UnorderedSet(size_t count) : UnorderedSet() {
        Reserve(count);
    }

    template <typename IteratorType,
              typename = std::enable_if_t<std::is_base_of_v<
                  std::forward_iterator_tag, typename std::iterator_traits<IteratorType>::iterator_category>>>
    UnorderedSet(IteratorType first, IteratorType last) : UnorderedSet(std::distance(first, last)) {
        while (first != last) {
            data_[Bucket(*first)].push_back(*first);
            ++first;
            ++n_elements_;
        }
    }

    UnorderedSet(const UnorderedSet& other) {
        n_elements_ = other.Size();
        Reserve(other.BucketCount());
        for (size_t i = 0; i < other.BucketCount(); ++i) {
            data_[i] = other.data_[i];
        }
    }

    UnorderedSet(UnorderedSet&& other) : n_elements_(0) {
        std::swap(n_elements_, other.n_elements_);
        data_ = std::move(other.data_);
    }

    ~UnorderedSet() = default;

    UnorderedSet& operator=(const UnorderedSet& other) {
        UnorderedSet tmp(other);
        Swap(tmp);
        return *this;
    }

    UnorderedSet& operator=(UnorderedSet&& other) {
        n_elements_ = other.n_elements_;
        data_ = std::move(other.data_);
        other.n_elements_ = 0;
        return *this;
    }

    size_t Size() const {
        return n_elements_;
    }

    bool Empty() const {
        return n_elements_ == 0;
    }

    void Clear() {
        UnorderedSet tmp;
        Swap(tmp);
    }

    void Insert(const KeyT& key) {
        if (n_elements_ == data_.size()) {
            Rehash(2 * n_elements_);
        }
        ++n_elements_;
        data_[Bucket(key)].push_back(key);
    }

    void Insert(KeyT&& key) {
        if (n_elements_ == data_.size()) {
            Rehash(2 * n_elements_);
        }
        ++n_elements_;
        data_[Bucket(key)].emplace_back(key);
    }

    void Erase(const KeyT& key) {
        auto it_to_delete = data_[Bucket(key)].begin();
        for (const KeyT& elem : data_[Bucket(key)]) {
            if (elem == key) {
                break;
            }
            ++it_to_delete;
        }
        if (it_to_delete != data_[Bucket(key)].end()) {
            data_[Bucket(key)].erase(it_to_delete);
            --n_elements_;
        }
    }

    bool Find(const KeyT& key) const {
        if (data_.empty()) {
            return false;
        }
        for (const KeyT& elem : data_[Bucket(key)]) {
            if (elem == key) {
                return true;
            }
        }
        return false;
    }

    void Rehash(size_t new_bucket_count) {
        if (new_bucket_count == 0) {
            new_bucket_count = 1;
        }
        if (data_.size() == new_bucket_count) {
            return;
        }
        if (new_bucket_count < Size()) {
            new_bucket_count = BucketCount();
        }
        std::vector<std::list<KeyT>> tmp(new_bucket_count);
        for (const std::list<KeyT>& bucket : data_) {
            for (const KeyT& elem : bucket) {
                tmp[std::hash<KeyT>{}(elem) % new_bucket_count].push_back(elem);
            }
        }
        data_ = std::move(tmp);
    }

    void Reserve(size_t new_bucket_count) {
        if (data_.size() >= new_bucket_count) {
            return;
        }
        Rehash(new_bucket_count);
    }

    size_t BucketCount() const {
        return data_.size();
    }

    size_t BucketSize(size_t id) const {
        if (id >= data_.size()) {
            return 0;
        }
        return data_[id].size();
    }

    size_t Bucket(const KeyT& key) const {
        return std::hash<KeyT>{}(key) % data_.size();
    }

    double LoadFactor() const {
        if (n_elements_ == 0) {
            return 0;
        }
        return static_cast<double>(n_elements_) / data_.size();
    }

    void Swap(UnorderedSet& other) {
        std::vector<std::list<KeyT>> tmp = std::move(other.data_);
        other.data_ = std::move(data_);
        data_ = std::move(tmp);
        std::swap(n_elements_, other.n_elements_);
    }

private:
    size_t n_elements_;
    std::vector<std::list<KeyT>> data_;
};
