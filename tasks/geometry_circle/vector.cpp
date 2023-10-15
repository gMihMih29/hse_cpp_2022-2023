#include "vector.h"

namespace geometry {
Vector::Vector() : x_coord_(0), y_coord_(0) {
}

Vector::Vector(int64_t x, int64_t y) : x_coord_(x), y_coord_(y) {
}

int64_t Vector::GetX() const {
    return x_coord_;
}

int64_t Vector::GetY() const {
    return y_coord_;
}

Vector Vector::operator+(const Vector& other) const {
    Vector mem = *this;
    return mem += other;
}

Vector Vector::operator-(const Vector& other) const {
    geometry::Vector mem = *this;
    return mem -= other;
}

Vector Vector::operator+() const {
    return *this;
}

Vector Vector::operator-() const {
    return Vector(-GetX(), -GetY());
}

Vector Vector::operator*(int64_t number) const {
    Vector mem = *this;
    return mem *= number;
}

Vector Vector::operator/(int64_t number) const {
    Vector mem = *this;
    return mem /= number;
}

Vector& Vector::operator+=(const Vector& other) {
    x_coord_ += other.GetX();
    y_coord_ += other.GetY();
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    return (*this) += -other;
}

Vector& Vector::operator*=(int64_t number) {
    x_coord_ *= number;
    y_coord_ *= number;
    return *this;
}

Vector& Vector::operator/=(int64_t number) {
    x_coord_ /= number;
    y_coord_ /= number;
    return *this;
}

bool Vector::operator==(const Vector& other) const {
    return GetX() == other.GetX() && GetY() == other.GetY();
}
}  // namespace geometry