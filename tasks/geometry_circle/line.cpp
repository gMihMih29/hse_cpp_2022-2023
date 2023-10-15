#include "line.h"

#include <cmath>

#include "segment.h"
#include "vector.h"

namespace geometry {
Line::Line() : start_(Point(0, 0)), end_(Point(0, 0)) {
}

Line::Line(Point start, Point end) : start_(start), end_(end) {
}

int64_t Line::GetA() const {
    return end_.GetY() - start_.GetY();
}

int64_t Line::GetB() const {
    return start_.GetX() - end_.GetX();
}

int64_t Line::GetC() const {
    return end_.GetX() * start_.GetY() - start_.GetX() * end_.GetY();
}

double Line::Distance(Point p) const {
    return static_cast<double>(std::abs(GetA() * p.GetX() + GetB() * p.GetY() + GetC())) /
           std::sqrt(static_cast<double>(GetA() * GetA() + GetB() * GetB()));
}

Line& Line::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool Line::ContainsPoint(const Point& point) const {
    Vector diff = start_ - point;
    Vector guiding = end_ - start_;
    return VectorMult(diff, guiding) == 0;
}

bool Line::CrossesSegment(const Segment& segment) const {
    Vector diff1 = segment.GetStart() - start_;
    Vector diff2 = segment.GetEnd() - start_;
    Vector guiding = end_ - start_;
    return (VectorMult(diff1, guiding) >= 0 && VectorMult(diff2, guiding) <= 0) ||
           (VectorMult(diff1, guiding) <= 0 && VectorMult(diff2, guiding) >= 0);
}

Line* Line::Clone() const {
    return new Line(*this);
}
}  // namespace geometry