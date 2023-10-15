#pragma once

#include <string>

template <class T>
class ControlBlock;

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
public:
    friend ControlBlock<T>;
    friend WeakPtr<T>;

public:
    SharedPtr() : ptr_(nullptr), ctrl_block_(new ControlBlock<T>()) {
    }

    SharedPtr(const SharedPtr<T>& rhs) : ptr_(rhs.ctrl_block_->Get()), ctrl_block_(rhs.ctrl_block_) {
        ctrl_block_->AddSharedPtr();
    }

    explicit SharedPtr(const WeakPtr<T>& rhs) : ptr_(rhs.ctrl_block_->Get()), ctrl_block_(rhs.ctrl_block_) {
        ctrl_block_->AddSharedPtr();
    }

    explicit SharedPtr(ControlBlock<T>* ctrl) : ptr_(ctrl->Get()), ctrl_block_(ctrl) {
        ctrl_block_->AddSharedPtr();
    }

    explicit SharedPtr(T* ptr) : ptr_(ptr) {
        ctrl_block_ = new ControlBlock<T>(*this);
    }

    ~SharedPtr() {
        if (ctrl_block_) {
            ctrl_block_->RemoveSharedPtr();
            if (ctrl_block_->IsExpired()) {
                delete ctrl_block_;
            }
        }
    }

    SharedPtr& operator=(const SharedPtr& rhv) {
        ctrl_block_->RemoveSharedPtr();
        if (ctrl_block_->IsExpired()) {
            delete ctrl_block_;
        }
        ptr_ = rhv.ptr_;
        ctrl_block_ = rhv.ctrl_block_;
        ctrl_block_->AddSharedPtr();
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& rhv) {
        ctrl_block_->RemoveSharedPtr();
        if (ctrl_block_->IsExpired()) {
            delete ctrl_block_;
        }
        ptr_ = rhv.ptr_;
        ctrl_block_ = rhv.ctrl_block_;
        rhv.ptr_ = nullptr;
        rhv.ctrl_block_ = nullptr;
        return *this;
    }

    T* Get() {
        return ptr_;
    }

    T operator*() {
        return *ptr_;
    }

    void Reset(T* new_ptr) {
        ctrl_block_->RemoveSharedPtr();
        if (ctrl_block_->IsExpired()) {
            delete ctrl_block_;
        }
        ptr_ = new_ptr;
        ctrl_block_ = new ControlBlock(*this);
    }

private:
    T* ptr_;
    ControlBlock<T>* ctrl_block_;
};

template <class T>
class WeakPtr {
public:
    friend ControlBlock<T>;
    friend SharedPtr<T>;

public:
    WeakPtr() : ctrl_block_(nullptr) {
    }

    explicit WeakPtr(const SharedPtr<T>& rhs) : ctrl_block_(rhs.ctrl_block_) {
        ctrl_block_->AddWeakPtr();
    }

    WeakPtr(const WeakPtr& rhs) : ctrl_block_(rhs.ctrl_block_) {
    }

    WeakPtr(WeakPtr&& rhs) : ctrl_block_(rhs.ctrl_block_) {
        rhs.ctrl_block_ = nullptr;
    }

    ~WeakPtr() {
        if (ctrl_block_) {
            ctrl_block_->RemoveWeakPtr();
            if (ctrl_block_->IsExpired()) {
                delete ctrl_block_;
            }
        }
    }

    WeakPtr& operator=(const WeakPtr& rhs) {
        if (ctrl_block_) {
            ctrl_block_->RemoveWeakPtr();
            if (ctrl_block_->IsExpired()) {
                delete ctrl_block_;
            }
        }
        ctrl_block_ = rhs.ctrl_block_;
        return *this;
    }

    WeakPtr& operator=(WeakPtr&& rhs) {
        if (ctrl_block_) {
            ctrl_block_->RemoveWeakPtr();
            if (ctrl_block_->IsExpired()) {
                delete ctrl_block_;
            }
        }
        ctrl_block_ = rhs.ctrl_block_;
        ctrl_block_ = nullptr;
        return *this;
    }

    SharedPtr<T> Lock() {
        if (!ctrl_block_ || IsExpired()) {
            return SharedPtr<T>();
        }
        return SharedPtr<T>(ctrl_block_);
    }

    bool IsExpired() const {
        return !ctrl_block_ || !ctrl_block_->Get();
    }

private:
    ControlBlock<T>* ctrl_block_;
};

template <class T>
class ControlBlock {
public:
    ControlBlock() : ptr_(nullptr), cnt_shared_(1), cnt_weak_(0) {
    }

    explicit ControlBlock(const SharedPtr<T>& ptr) : ptr_(ptr.ptr_), cnt_shared_(1), cnt_weak_(0) {
    }

    explicit ControlBlock(const WeakPtr<T>& ptr) : ptr_(ptr.ptr_), cnt_shared_(0), cnt_weak_(1) {
    }

    ~ControlBlock() {
        delete ptr_;
    }

    void AddSharedPtr() {
        ++cnt_shared_;
    }

    void AddWeakPtr() {
        ++cnt_weak_;
    }

    void RemoveSharedPtr() {
        if (cnt_shared_ != 0) {
            --cnt_shared_;
        }
        if (cnt_shared_ == 0) {
            delete ptr_;
            ptr_ = nullptr;
        }
    }

    void RemoveWeakPtr() {
        if (cnt_weak_ != 0) {
            --cnt_weak_;
        }
    }

    T* Get() {
        return ptr_;
    }

    bool IsExpired() {
        return cnt_shared_ == 0 && cnt_weak_ == 0;
    }

private:
    T* ptr_;
    size_t cnt_shared_;
    size_t cnt_weak_;
};