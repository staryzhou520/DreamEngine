#pragma once

class RenderBase
{
public:
    virtual void Init() = 0;
    
    virtual void Draw() = 0;

    virtual void End();
};
