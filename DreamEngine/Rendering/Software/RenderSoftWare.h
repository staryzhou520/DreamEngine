#pragma once
#include "FrameBuffer.h"
#include "../../Core/Math/Vector2D.h"
#include "../RenderCore/RenderBase.h"

class RenderSoftWare: public RenderBase
{
public:
    void Init() override;
    void Draw() override;
    
    // 画线
    void DrawLine(Vector2D start, Vector2D end,SColor color);
    // DDA 画线法，相当于以最小像素点为单位，取长边一步一步迭代，四舍五入取对应点。
    void DrawLineDDA(Vector2D start, Vector2D end, SColor color);

    void DrawLineBresenham(Vector2D start, Vector2D end, SColor color)
    {
        DrawLineBresenham_5(start,end,color);
    }

    // 画三角形
    void DrawTriangle(Vector2D A, Vector2D B, Vector2D C);

    // 综合测试场景：小房子，用于肉眼验证画线的各种边界情况
    void DrawHouse();

    void Present();

private:
    FrameBuffer frame_buffer;

    void DrawLineBresenham_1(Vector2D start, Vector2D end, SColor color);
    void DrawLineBresenham_2(Vector2D start, Vector2D end, SColor color);
    void DrawLineBresenham_3(Vector2D start, Vector2D end, SColor color);
    void DrawLineBresenham_4(Vector2D start, Vector2D end, SColor color);
    void DrawLineBresenham_5(Vector2D start, Vector2D end, SColor color);
};
