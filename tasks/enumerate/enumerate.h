#pragma once

#include <iterator>
#include <utility>

template <class Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {
    }

    Iterator begin() const {  // NOLINT
        return begin_;
    }

    Iterator end() const {  // NOLINT
        return end_;
    }

private:
    Iterator begin_, end_;
};

template <class Iterator>
class EnumerateIterator {
public:
    using Reference = typename std::iterator_traits<Iterator>::reference;

    explicit EnumerateIterator(Iterator current) : it_(current), index_(0) {
    }

    EnumerateIterator& operator++() {
        ++it_;
        ++index_;
        return *this;
    }

    std::pair<size_t, Reference> operator*() {
        return std::pair<size_t, Reference>(index_, *it_);
    }

    bool operator!=(const EnumerateIterator& other) const {
        return it_ != other.it_;
    }

private:
    Iterator it_;
    size_t index_;
};

template <class Container>
auto Enumerate(Container& c) {
    return IteratorRange(EnumerateIterator(c.begin()), EnumerateIterator(c.end()));
}