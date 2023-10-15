#pragma once

#include <memory>

class Any {
public:
    struct InnerBase {
        using Ptr = std::unique_ptr<InnerBase>;
        virtual InnerBase* Clone() const = 0;
        virtual ~InnerBase() {
        }
    };

    template <class T>
    struct Inner : public InnerBase {
        explicit Inner(T value) : value_(value) {
        }

        InnerBase* Clone() const override {
            return new Inner(value_);
        }

        T value_;
    };

    Any() : value_ptr_(nullptr) {
    }

    template <class T>
    explicit Any(const T& value) {
        value_ptr_ = std::make_unique<Inner<const T>>(std::forward<const T>(value));
    }

    template <class T>
    Any& operator=(const T& value) {
        value_ptr_.reset();
        value_ptr_ = std::make_unique<Inner<const T>>(std::forward<const T>(value));
        return *this;
    }

    Any(const Any& rhs);
    Any& operator=(Any rhs);
    ~Any();

    bool Empty() const;

    void Clear();
    void Swap(Any& rhs);

    template <class T>
    const T& GetValue() const {
        return (dynamic_cast<Inner<const T>&>(*value_ptr_)).value_;
    }

private:
    typename InnerBase::Ptr value_ptr_;
};