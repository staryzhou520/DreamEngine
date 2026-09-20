#pragma once
#include "Vector2D.h"

struct AABB2D
{
public:
    Vector2D Min;
    Vector2D Max;

    AABB2D();
    AABB2D(const Vector2D& min, const Vector2D& max) : Min(min), Max(max) {}
    AABB2D(const Vector2D& a, const Vector2D& b, const Vector2D& c);
};
