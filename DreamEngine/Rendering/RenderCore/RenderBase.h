#pragma once

class RenderBase
{
public:
    virtual void Draw() = 0;

    virtual void Init() = 0;

    virtual void End();
};
