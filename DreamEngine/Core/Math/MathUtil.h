#pragma once
#include "Triangle2D.h"
#include "Vector2D.h"
#include <cmath>

class MathUtil
{
public:
    static bool IsPointInTriangle(const Vector2D& point, const Triangle2D& tri);
    static float Area2D(const Vector2D& a, const Vector2D& b, const Vector2D& c);
};
