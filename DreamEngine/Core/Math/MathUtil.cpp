#include "MathUtil.h"


// 2D叉积：v1 × v2 = v1.X * v2.Y - v1.Y * v2.X
// 符号表示v2相对v1的转向：>0 逆时针一侧，<0 顺时针一侧，=0 共线
static float Cross2D(const Vector2D& v1, const Vector2D& v2)
{
    return v1.X * v2.Y - v1.Y * v2.X;
}

bool MathUtil::IsPointInTriangle(const Vector2D& point, const Triangle2D& tri)
{
    // 点在三角形内 <=> 点在三条边AB、BC、CA的同一侧
    // 即三个叉积同号（全>=0或全<=0，兼容顺/逆时针绕序）
    Vector2D ab(tri.p1.X - tri.p0.X, tri.p1.Y - tri.p0.Y);
    Vector2D ap(point.X - tri.p0.X, point.Y - tri.p0.Y);
    float crossAB = Cross2D(ab, ap);

    Vector2D bc(tri.p2.X - tri.p1.X, tri.p2.Y - tri.p1.Y);
    Vector2D bp(point.X - tri.p1.X, point.Y - tri.p1.Y);
    float crossBC = Cross2D(bc, bp);

    Vector2D ca(tri.p0.X - tri.p2.X, tri.p0.Y - tri.p2.Y);
    Vector2D cp(point.X - tri.p2.X, point.Y - tri.p2.Y);
    float crossCA = Cross2D(ca, cp);

    return (crossAB >= 0 && crossBC >= 0 && crossCA >= 0)
        || (crossAB <= 0 && crossBC <= 0 && crossCA <= 0);
}

float MathUtil::Area2D(const Vector2D& a, const Vector2D& b, const Vector2D& c)
{
    // 叉乘求面积
    const float area = ((b.X - a.X) * (c.Y - a.Y) - (c.X - a.X) * (b.Y - a.Y)) * 0.5f;
    return std::abs(area);
}
