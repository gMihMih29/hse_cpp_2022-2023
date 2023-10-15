#pragma once
#include "i_shape.h"
#include "point.h"
#include "vector.h"

namespace geometry {
class Line : public IShape {
private:
    Point start_;
    Point end_;

public:
    Line();

    Line(Point start, Point end);

    int64_t GetA() const;

    int64_t GetB() const;

    int64_t GetC() const;

    double Distance(Point) const;

    Line& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& segment) const override;

    Line* Clone() const override;
};
}  // namespace geometry
