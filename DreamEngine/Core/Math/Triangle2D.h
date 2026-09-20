#pragma once
#include "Vector2D.h"

struct Triangle2D
{
    Vector2D p0, p1, p2;

    Triangle2D();
    Triangle2D(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2) : p0(p0), p1(p1), p2(p2) {}
};
