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

    // 画三角形
    void DrawTriangle(Vector2D A, Vector2D B, Vector2D C);

    // 画实心三角形
    void DrawFilledTriangle(Vector2D A, Vector2D B, Vector2D C, SColor color);
    
    void Present();

private:
    FrameBuffer frame_buffer;

    // 综合测试场景：小房子，用于肉眼验证画线的各种边界情况
    void DrawHouse();
    
    // DDA 画线法，相当于以最小像素点为单位，取长边一步一步迭代，四舍五入取对应点。
    void DrawLineDDA(Vector2D start, Vector2D end, SColor color);

    void DrawLineBresenham(Vector2D start, Vector2D end, SColor color)
    {
        DrawLineBresenham_5(start,end,color);
    }
    
    // —— 以下 5 个版本为 Bresenham 算法的迭代实现，耗时为实测数据 ——
    // 测试条件：DrawHouse 场景 20 条线段（水平/垂直/斜线/单点 + 两条跨屏长斜线），
    // 每版本绘制 30000 轮、重复 5 次取最优；MSVC 2022 x64，分别测 Release /O2 与 Debug /Od。
    // 下表为单次 DrawLine 调用的平均耗时（约多少 ns）：Release | Debug
    void DrawLineBresenham_1(Vector2D start, Vector2D end, SColor color); // 341 | 901
    void DrawLineBresenham_2(Vector2D start, Vector2D end, SColor color); // 280 | 857（最快）
    void DrawLineBresenham_3(Vector2D start, Vector2D end, SColor color); // 342 | 932
    void DrawLineBresenham_4(Vector2D start, Vector2D end, SColor color); // 330 | 902
    void DrawLineBresenham_5(Vector2D start, Vector2D end, SColor color); // 336 | 967（最慢）
    // 结论：5 版都已无乘除，差距来自分支数与循环结构（SetPixel 占大头且 5 版相同）。
    // _2 最快：主轴走归纳变量，每像素分支最少；_5 最慢：while(true) 每像素多 2 次终点比较，
    // 且两个分支共享 error 串行依赖。“理论经典版”≠“实测最快”，以测量为准。
};
