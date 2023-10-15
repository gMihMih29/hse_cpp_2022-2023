#include "point.h"

#include "segment.h"

namespace geometry {
Point::Point(int64_t x, int64_t y) : x_coord_(x), y_coord_(y) {
}

int64_t Point::GetX() const {
    return x_coord_;
}

int64_t Point::GetY() const {
    return y_coord_;
}

void Point::SetX(int64_t value) {
    x_coord_ = value;
}

void Point::SetY(int64_t value) {
    y_coord_ = value;
}

Point& Point::Move(const Vector& v) {
    SetX(x_coord_ + v.GetX());
    SetY(y_coord_ + v.GetY());
    return *this;
}

bool Point::ContainsPoint(const Point& p) const {
    return *this == p;
}

bool Point::CrossesSegment(const Segment& seg) const {
    if (seg.GetStart() == *this || seg.GetEnd() == *this) {
        return true;
    }
    Vector guiding_vector = seg.GetEnd() - seg.GetStart();
    Vector difference1 = *this - seg.GetStart();
    Vector difference2 = *this - seg.GetEnd();
    int64_t res1 = VectorMult(guiding_vector, difference1);
    int64_t res2 = VectorMult(-guiding_vector, difference2);
    return res1 == 0 && res2 == 0 && Length(guiding_vector) > Length(difference1) &&
           Length(guiding_vector) > Length(difference2);
}

Point* Point::Clone() const {
    return new Point(*this);
}

Vector Point::operator-(Point other) const {
    return Vector(GetX() - other.GetX(), GetY() - other.GetY());
}

bool Point::operator==(const Point& other) const {
    return x_coord_ == other.GetX() && y_coord_ == other.GetY();
}
}  // namespace geometry
