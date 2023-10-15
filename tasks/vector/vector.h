#pragma once

#include <iterator>
#include <utility>

template <class T>
class Vector {
public:
    Vector() : ptr_(nullptr), size_(0), capacity_(0) {
    }

    explicit Vector(size_t size) : size_(size), capacity_(2 * size) {  // NOLINT
        if (size == 0) {
            ptr_ = nullptr;
            return;
        }
        ptr_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            ptr_[i] = 0;
        }
    }

    Vector(std::initializer_list<T> list) : size_(list.size()), capacity_(list.size()) {
        if (size_ == 0) {
            ptr_ = nullptr;
            return;
        }
        ptr_ = new T[capacity_];
        const T* data = list.begin();
        for (size_t i = 0; i < size_; ++i) {
            ptr_[i] = data[i];
        }
    }

    Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
        if (size_ == 0) {
            ptr_ = nullptr;
            return;
        }
        ptr_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            ptr_[i] = other[i];
        }
    }

    Vector(Vector&& other) : size_(other.size_), capacity_(other.capacity_) {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    void Swap(Vector& other) {
        std::swap(ptr_, other.ptr_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    Vector& operator=(const Vector& rhv) {
        delete[] ptr_;
        Vector tmp = rhv;
        tmp.Swap(*this);
        return *this;
    }

    Vector& operator=(Vector&& rhv) {
        delete[] ptr_;
        ptr_ = rhv.ptr_;
        size_ = rhv.size_;
        capacity_ = rhv.capacity_;
        rhv.ptr_ = nullptr;
        return *this;
    }

    ~Vector() {
        delete[] ptr_;
        size_ = 0;
        capacity_ = 0;
    }

    T& operator[](size_t index) {
        return ptr_[index];
    }

    const T& operator[](size_t index) const {
        return ptr_[index];
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(T elem) {
        if (size_ == capacity_) {
            capacity_ = size_ == 0 ? 1 : 2 * size_;
            T* tmp = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                tmp[i] = ptr_[i];
            }
            delete[] ptr_;
            ptr_ = tmp;
        }
        ptr_[size_] = elem;
        ++size_;
    }

    void PopBack() {
        if (size_ != 0) {
            --size_;
        }
    }

    void Clear() {
        size_ = 0;
    }

    void Reserve(size_t new_capacity) {
        if (capacity_ >= new_capacity) {
            return;
        }
        capacity_ = new_capacity;
        T* tmp = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            tmp[i] = ptr_[i];
        }
        delete[] ptr_;
        ptr_ = tmp;
    }

    class Iterator {
    public:
        using IteratorCategory = std::random_access_iterator_tag;
        using ValueType = T;
        using DifferenceType = int;
        using Pointer = T*;
        using Reference = T&;

    public:
        Iterator() : ptr_(nullptr) {
        }

        explicit Iterator(Pointer ptr) : ptr_(ptr) {  // NOLINT
        }

        Iterator& operator+=(DifferenceType n) {
            ptr_ += n;
            return *this;
        }

        Iterator operator+(DifferenceType n) {
            Iterator res(ptr_);
            return res += n;
        }

        Iterator& operator++() {
            ++ptr_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator copy(ptr_);
            ++ptr_;
            return copy;
        }

        Iterator& operator-=(DifferenceType n) {
            ptr_ -= n;
            return *this;
        }

        Iterator operator-(DifferenceType n) {
            Iterator res(ptr_);
            return res -= n;
        }

        Iterator& operator--() {
            --ptr_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator copy(ptr_);
            --ptr_;
            return copy;
        }

        DifferenceType operator-(const Iterator& rhv) {
            return ptr_ - rhv.ptr_;
        }

        bool operator<(const Iterator& rhv) const {
            return *this - rhv > 0;
        }

        bool operator>(const Iterator& rhv) const {
            return rhv < *this;
        }

        bool operator>=(const Iterator& rhv) const {
            return !(*this < rhv);
        }

        bool operator<=(const Iterator& rhv) const {
            return !(*this > rhv);
        }

        bool operator==(const Iterator& rhv) const {
            return ptr_ == rhv.ptr_;
        }

        bool operator!=(const Iterator& rhv) const {
            return !(*this == rhv);
        }

        Reference operator*() {
            return *ptr_;
        }

        Pointer operator->() {
            return ptr_;
        }

    private:
        Pointer ptr_;
    };

    Iterator Begin() {
        return Iterator(ptr_);
    }

    Iterator End() {
        return Iterator(ptr_ + size_);
    }

    Iterator begin() {  // NOLINT
        return Begin();
    }

    Iterator end() {  // NOLINT
        return End();
    }

private:
    T* ptr_;
    size_t size_;
    size_t capacity_;
};
