#include "circle.h"

#include "line.h"
#include "point.h"
#include "segment.h"

const double EPS = 1e-9;

namespace geometry {
Circle::Circle() : centre_(Point(0, 0)), radius_(0) {
}

Circle::Circle(Point p, int64_t rad) : centre_(p), radius_(rad) {
}

Circle& Circle::Move(const Vector& vector) {
    centre_.Move(vector);
    return *this;
}

bool Circle::ContainsPoint(const Point& point) const {
    return static_cast<double>(radius_) >= Length(point - centre_);
}

bool Circle::CrossesSegment(const Segment& segment) const {
    if (static_cast<double>(radius_) > Length(segment.GetStart() - centre_) &&
        static_cast<double>(radius_) > Length(segment.GetEnd() - centre_)) {
        return false;
    }
    if (ContainsPoint(segment.GetStart()) || ContainsPoint(segment.GetEnd())) {
        return true;
    }
    Line l(segment.GetStart(), segment.GetEnd());
    Line perped_l(centre_, Point(l.GetA() + centre_.GetX(), l.GetB() + centre_.GetY()));
    return static_cast<double>(radius_) - l.Distance(centre_) > -EPS && perped_l.CrossesSegment(segment);
}

Circle* Circle::Clone() const {
    return new Circle(*this);
}

int64_t Circle::GetRadius() const {
    return radius_;
}

Point Circle::GetCenter() const {
    return centre_;
}
}  // namespace geometry
