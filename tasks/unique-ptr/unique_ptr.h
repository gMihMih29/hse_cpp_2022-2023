#pragma once

template <class T>
class UniquePtr {
public:
    // put all required methods and operators here

    // see http://en.cppreference.com/w/cpp/memory/unique_ptr
    // and test.cpp
    constexpr UniquePtr() noexcept : ptr_(nullptr) {
    }

    constexpr UniquePtr(const UniquePtr&) = delete;

    explicit UniquePtr(T* p) noexcept : ptr_(p) {
    }

    UniquePtr(UniquePtr&& rhv) noexcept {
        ptr_ = rhv.ptr_;
        rhv.ptr_ = nullptr;
    }

    ~UniquePtr() {
        delete ptr_;
    }

    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr& operator=(UniquePtr&& rhv) {
        delete ptr_;
        ptr_ = rhv.ptr_;
        rhv.ptr_ = nullptr;
        return *this;
    }

    T* operator->() {
        return ptr_;
    }

    void Reset(T* ptr) noexcept {
        delete ptr_;
        ptr_ = ptr;
    }

    void Reset() noexcept {
        delete ptr_;
        ptr_ = nullptr;
    }

private:
    T* ptr_;
};
