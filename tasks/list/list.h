#pragma once

#include <cstdint>
#include <utility>

template <typename T>
class List {
public:
    class ListNode {
    public:
        friend class List;
        friend class Iterator;

    public:
        ListNode() {
            value_ptr_ = nullptr;
            next_ = this;
            prev_ = this;
        }

        explicit ListNode(T* value_ptr) : value_ptr_(value_ptr), next_(nullptr), prev_(nullptr) {
        }

        T& GetValue() {
            return *value_ptr_;
        }

        ~ListNode() {
            delete value_ptr_;
        }

    private:
        T* value_ptr_;
        ListNode* next_;
        ListNode* prev_;
    };

    class Iterator {
    public:
        explicit Iterator(ListNode* ptr) : ptr_(ptr) {
        }

        Iterator& operator++() {
            ptr_ = ptr_->next_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp(ptr_);
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            ptr_ = ptr_->prev_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp(ptr_);
            --(*this);
            return tmp;
        }

        T& operator*() const {
            return ptr_->GetValue();
        }

        T* operator->() const {
            return ptr_->value_ptr_;
        }

        bool operator==(const Iterator& rhs) const {
            return ptr_->value_ptr_ == rhs.ptr_->value_ptr_;
        }

        bool operator!=(const Iterator& rhs) const {
            return !(*this == rhs);
        }

    private:
        ListNode* ptr_;
    };

private:
    ListNode* linkage_;

    void UnLink(ListNode* node) {
        if (node == linkage_) {
            return;
        }
        ListNode* prev = node->prev_;
        ListNode* next = node->next_;
        prev->next_ = next;
        next->prev_ = prev;
        node->prev_ = nullptr;
        node->next_ = nullptr;
        delete node;
    }

    void LinkAfter(ListNode* target, ListNode* after) {
        after->next_->prev_ = target;
        target->next_ = after->next_;
        after->next_ = target;
        target->prev_ = after;
    }

public:
    List() : linkage_(nullptr) {
        linkage_ = new ListNode();
    }

    List(const List& other) : List() {
        for (const T& value : other) {
            T* new_value = new T(value);
            ListNode* new_node = new ListNode(new_value);
            LinkAfter(new_node, linkage_->prev_);
        }
    }

    List(List&& other) : List() {
        std::swap(linkage_, other.linkage_);
    }

    ~List() {
        while (!IsEmpty()) {
            PopBack();
        }
        delete linkage_;
    }

    List& operator=(const List& rhv) {
        List tmp(rhv);
        Swap(*this, tmp);
        return *this;
    }

    List& operator=(List&& rhv) {
        Swap(*this, rhv);
        return *this;
    }

    bool IsEmpty() const {
        return linkage_->prev_ == linkage_ && linkage_->next_ == linkage_;
    }

    std::size_t Size() const {
        std::size_t size = 0;
        ListNode* current = linkage_->next_;
        while (current != linkage_) {
            ++size;
            current = current->next_;
        }
        return size;
    }

    void PushBack(const T& elem) {
        T* new_elem = new T(elem);
        ListNode* new_node = new ListNode(new_elem);
        LinkAfter(new_node, linkage_->prev_);
    }

    void PushBack(T&& elem) {
        T* new_elem = new T(std::move(elem));
        ListNode* new_node = new ListNode(new_elem);
        LinkAfter(new_node, linkage_->prev_);
    }

    void PushFront(const T& elem) {
        T* new_elem = new T(elem);
        ListNode* new_node = new ListNode(new_elem);
        LinkAfter(new_node, linkage_);
    }

    void PushFront(T&& elem) {
        T* new_elem = new T(std::move(elem));
        ListNode* new_node = new ListNode(new_elem);
        LinkAfter(new_node, linkage_);
    }

    T& Front() {
        return linkage_->next_->GetValue();
    }

    const T& Front() const {
        return linkage_->next_->GetValue();
    }

    T& Back() {
        return linkage_->prev_->GetValue();
    }

    const T& Back() const {
        return linkage_->prev_->GetValue();
    }

    void PopBack() {
        UnLink(linkage_->prev_);
    }

    void PopFront() {
        UnLink(linkage_->next_);
    }

    void Swap(List& lhv, List& rhv) {
        std::swap(lhv.linkage_, rhv.linkage_);
    }

    Iterator Begin() {
        return Iterator(linkage_->next_);
    }

    Iterator End() {
        return Iterator(linkage_);
    }

    Iterator Begin() const {
        return Iterator(linkage_->next_);
    }

    Iterator End() const {
        return Iterator(linkage_);
    }

    Iterator begin() {  // NOLINT
        return Begin();
    }

    Iterator end() {  // NOLINT
        return End();
    }

    Iterator begin() const {  // NOLINT
        return Begin();
    }

    Iterator end() const {  // NOLINT
        return End();
    }
};

template <typename T>
typename List<T>::Iterator begin(List<T>& list) {  // NOLINT
    return list.Begin();
}

template <typename T>
typename List<T>::Iterator end(List<T>& list) {  // NOLINT
    return list.End();
}
