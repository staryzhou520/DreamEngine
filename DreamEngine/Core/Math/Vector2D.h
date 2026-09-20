#pragma once

// 这里面要支持 int + int  float+flaot int + float 等多种组合，
struct Vector2D
{
public:
    float X;
    float Y;
    
    Vector2D(float x, float y)
    {
        X = x;
        Y = y;
    }
};
