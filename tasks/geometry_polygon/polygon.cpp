#include "polygon.h"

#include <cmath>
#include <vector>

#include "segment.h"

const double EPS = 1e-9;

namespace geometry {
Polygon::Polygon() : points_(std::vector<Point>(0)), num_points_(0) {
}

Polygon& Polygon::Move(const Vector& vector) {
    for (Point& p : points_) {
        p.Move(vector);
    }
    return *this;
}

bool Polygon::ContainsPoint(const Point& point) const {
    double angle = 0;
    for (size_t i = 0; i < points_.size(); ++i) {
        Segment side(points_[i], points_[(i + 1) % points_.size()]);
        if (point == points_[i] || side.ContainsPoint(point)) {
            return true;
        }
        angle += std::atan2(VectorMult(points_[i] - point, points_[(i + 1) % points_.size()] - point),
                            ScalarMult(points_[i] - point, points_[(i + 1) % points_.size()] - point));
    }
    if (std::abs(angle) < EPS) {
        return false;
    }
    return true;
}

bool Polygon::CrossesSegment(const Segment& segment) const {
    for (size_t i = 0; i < points_.size(); ++i) {
        Segment side(points_[i], points_[(i + 1) % points_.size()]);
        if (side.CrossesSegment(segment)) {
            return true;
        }
    }
    return false;
}

Polygon* Polygon::Clone() const {
    return new Polygon(*this);
}
}  // namespace geometry