#include "AABB2D.h"

#include <algorithm>

AABB2D::AABB2D() : Min(0.0f, 0.0f), Max(0.0f, 0.0f) {}

AABB2D::AABB2D(const Vector2D& a, const Vector2D& b, const Vector2D& c)
    : Min(std::min(std::min(a.X, b.X), c.X), std::min(std::min(a.Y, b.Y), c.Y))
    , Max(std::max(std::max(a.X, b.X), c.X), std::max(std::max(a.Y, b.Y), c.Y))
{
}
