#include "any.h"

#include <utility>

void Any::Swap(Any& rhv) {
    std::swap(value_ptr_, rhv.value_ptr_);
}

Any::Any(const Any& rhs) : value_ptr_(rhs.value_ptr_->Clone()) {
}

Any& Any::operator=(Any rhs) {
    value_ptr_.reset();
    Any tmp(rhs);
    tmp.Swap(*this);
    return *this;
}

Any::~Any() {
    value_ptr_.reset();
}

bool Any::Empty() const {
    return value_ptr_ == nullptr;
}

void Any::Clear() {
    value_ptr_.reset();
}