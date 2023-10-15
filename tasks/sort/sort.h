#include <functional>

template <class Iterator, class Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void Sort(Iterator begin, Iterator end, Comparator comparator = Comparator()) {
    if (end - begin == 1 || end <= begin) {
        return;
    }
    Iterator bigger_beginning = begin;
    Iterator equals_beginning = begin;
    for (Iterator i = begin; i < end; ++i) {
        if (!(comparator(*equals_beginning, *i) || comparator(*i, *equals_beginning))) {
            std::swap(*bigger_beginning, *i);
            ++bigger_beginning;
        } else if (!comparator(*equals_beginning, *i)) {
            std::swap(*equals_beginning, *i);
            std::swap(*i, *bigger_beginning);
            ++bigger_beginning;
            ++equals_beginning;
        }
    }
    sort(begin, equals_beginning, comparator);
    sort(bigger_beginning, end, comparator);
}
