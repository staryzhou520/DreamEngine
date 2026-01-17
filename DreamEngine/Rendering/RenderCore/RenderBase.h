﻿#pragma once

class RenderBase
{
public:
    virtual void Init() = 0;
    
    virtual void Draw() = 0;

    virtual void End();

protected:
    // 渲染尺寸，子类共用
    int Width = 800;
    int Height = 600;
};
