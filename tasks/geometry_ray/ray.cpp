#include "ray.h"

#include "segment.h"
#include "vector.h"

namespace geometry {
Ray::Ray() : start_(Point(0, 0)), end_(Point(0, 0)) {
}

Ray::Ray(Point first, Point second) : start_(first), end_(second) {
}

Ray& Ray::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool Ray::ContainsPoint(const Point& point) const {
    if (start_ == point) {
        return true;
    }
    Vector diff = point - start_;
    Vector guiding = end_ - start_;
    return ScalarMult(diff, guiding) > 0 && VectorMult(diff, guiding) == 0;
}

bool Ray::CrossesSegment(const Segment& segment) const {
    if (segment.ContainsPoint(start_) || ContainsPoint(segment.GetStart()) || ContainsPoint(segment.GetEnd())) {
        return true;
    }
    Vector guiding = end_ - start_;
    Vector diff1 = segment.GetStart() - start_;
    Vector diff2 = segment.GetEnd() - start_;
    return ScalarMult(guiding, diff1) >= 0 && ScalarMult(guiding, diff2) >= 0 &&
           ((VectorMult(diff1, guiding) >= 0 && VectorMult(diff2, guiding) <= 0) ||
            (VectorMult(diff1, guiding) <= 0 && VectorMult(diff2, guiding) >= 0));
}

Ray* Ray::Clone() const {
    return new Ray(*this);
}

Point Ray::GetStart() const {
    return start_;
}

Point Ray::GetEnd() const {
    return end_;
}
}  // namespace geometry