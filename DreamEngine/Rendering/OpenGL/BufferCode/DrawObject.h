#pragma once
#include <glad/glad.h>

class DrawObject
{
public:
    virtual void InitDrwBuffer();
    virtual void DrawBuffer();
};
