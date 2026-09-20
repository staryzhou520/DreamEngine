#include "RenderSoftWare.h"

#include <algorithm>
#include <chrono>
#include <cmath>

#include "../../Core/Color/SColor.h"
#include "../../Core/Image/ImageUtil.h"
#include "../../Core/Math/MathUtil.h"
#include "../../Core/Math/AABB2D.h"

// CPU版软光栅器

void RenderSoftWare::Init()
{
    frame_buffer = FrameBuffer(Width,Height);
}

void RenderSoftWare::Draw()
{
    
    // 清屏幕
    frame_buffer.Clear(SColor::Black());
    //DrawHouse();

    //DrawFilledTriangle({100,100},{200,100},{200,200},SColor::White());
    DrawColoredTriangle({100,100},{200,100},{200,200},SColor::Blue(),SColor::Red(),SColor::Green());
    Present();
}

// 用一个统一的小房子场景覆盖 Bresenham 的各种边界情况。
// 判定标准：所有线段都必须是「干净的单像素直线」，不能出现断点、锯齿块或整段偏移。
void RenderSoftWare::DrawHouse()
{
    // 颜色常量（SColor 没有预定义 Orange/Magenta/Cyan，这里直接写 r,g,b,a）
    const SColor wallColor    = SColor::White();          // 墙体：矩形四条边
    const SColor roofColor    = SColor::Red();            // 屋顶：等腰三角形（两条普通斜边）
    const SColor doorColor    = SColor(255, 128, 0, 255); // 门：橙色矩形
    const SColor windowColor  = SColor(0, 255, 255, 255); // 窗：青色正方形
    const SColor groundColor  = SColor(0, 255, 0, 255);   // 地面：绿色水平线
    const SColor chimneyColor = SColor(255, 0, 255, 255); // 烟囱：品红矩形

    // ---- 关键坐标（画之前先在纸上推一遍，能立刻发现偏移）----
    const int wallLeft   = 200;
    const int wallRight  = 600;
    const int wallTop    = 250;
    const int wallBottom = 550;

    const int roofApexX = 400;
    const int roofApexY = 110;

    const int doorLeft   = 360;
    const int doorRight  = 440;
    const int doorTop    = 420;
    const int doorBottom = wallBottom;

    const int winLeft   = 240;
    const int winRight  = 330;
    const int winTop    = 300;
    const int winBottom = 390;

    const int chimLeft   = 500;
    const int chimRight  = 560;
    const int chimTop    = 140;
    const int chimBottom = 250;

    // ===================== 1. 墙体（矩形）=====================
    // 水平线：验证 dy == 0，线必须是平的，不能因误差累积出现 ±1 抖动
    DrawLine(Vector2D(wallLeft,  wallTop),    Vector2D(wallRight, wallTop),    wallColor);
    DrawLine(Vector2D(wallLeft,  wallBottom), Vector2D(wallRight, wallBottom), wallColor);
    // 垂直线：验证 dx == 0，线必须是直的，不能有左右错位
    DrawLine(Vector2D(wallLeft,  wallTop),    Vector2D(wallLeft,  wallBottom), wallColor);
    DrawLine(Vector2D(wallRight, wallTop),    Vector2D(wallRight, wallBottom), wallColor);

    // ===================== 2. 屋顶（等腰三角形，两条普通斜边）=====================
    // 左斜边：|dx| = 200、|dy| = 140，验证 sx == 1、sy == -1 的缓斜线
    DrawLine(Vector2D(wallLeft, wallTop),   Vector2D(roofApexX, roofApexY), roofColor);
    // 右斜边：|dx| = 200、|dy| = 140，验证 sx == 1、sy == 1 的缓斜线
    DrawLine(Vector2D(roofApexX, roofApexY), Vector2D(wallRight, wallTop),  roofColor);

    // ===================== 3. 门（矩形）=====================
    DrawLine(Vector2D(doorLeft,  doorTop), Vector2D(doorRight, doorTop),    doorColor); // 水平
    DrawLine(Vector2D(doorLeft,  doorTop), Vector2D(doorLeft,  doorBottom), doorColor); // 垂直
    DrawLine(Vector2D(doorRight, doorTop), Vector2D(doorRight, doorBottom), doorColor); // 垂直

    // ===================== 4. 窗（正方形，四条边等长）=====================
    DrawLine(Vector2D(winLeft,  winTop),    Vector2D(winRight, winTop),    windowColor);
    DrawLine(Vector2D(winLeft,  winBottom), Vector2D(winRight, winBottom), windowColor);
    DrawLine(Vector2D(winLeft,  winTop),    Vector2D(winLeft,  winBottom), windowColor);
    DrawLine(Vector2D(winRight, winTop),    Vector2D(winRight, winBottom), windowColor);

    // ===================== 5. 烟囱（矩形，验证长垂直线 + 特殊方向）=====================
    // 注意这两条是从「下往上」画（y 递减），验证 sy == -1 的处理
    DrawLine(Vector2D(chimLeft,  chimBottom), Vector2D(chimLeft,  chimTop), chimneyColor);
    DrawLine(Vector2D(chimRight, chimBottom), Vector2D(chimRight, chimTop), chimneyColor);
    DrawLine(Vector2D(chimLeft,  chimTop),    Vector2D(chimRight, chimTop), chimneyColor);

    // ===================== 6. 地面（长水平线，起点在右下）=====================
    // 从右往左画，验证 sx == -1 且 dy == 0 的退化情况
    DrawLine(Vector2D(700, 575), Vector2D(50, 575), groundColor);

    // ===================== 7. 退化情况（放在屋外空白处，不干扰主体）=====================
    // 单点：起终点重合，MaxDel == 0，正确实现应只画出一个橙色像素
    DrawLine(Vector2D(80, 80), Vector2D(80, 80), doorColor);
}

void RenderSoftWare::DrawLine(Vector2D start, Vector2D end,SColor color)
{

    // 1. 使用DDA方法， SetPixel
    //DrawLineDDA(start,end,color);
    //
    
    // 2. 使用Bresenham方法， SetPixel
    DrawLineBresenham(start,end,color);
    
}


void RenderSoftWare::DrawLineDDA(Vector2D start, Vector2D end,SColor color)
{
    int x1 = start.X;
    int x2 = end.X;
    int deltaX = x2 - x1;

    int y1 = start.Y;
    int y2 = end.Y;
    int deltaY = y2 - y1;

    int MaxDel = std::max(std::abs(deltaX),std::abs(deltaY));
    if(MaxDel == 0)
    {
        frame_buffer.SetPixel(start.X,start.Y,color);
        return;
    }

    for (int i = 0; i <= MaxDel; ++i)
    {
        int x = x1 + i * deltaX / MaxDel;
        int y = y1 + i * deltaY / MaxDel;
        frame_buffer.SetPixel(x, y, color);
    }
}

// Bresenham 算法 第一版，X 大或Y大，分别处理，以DDA为基础，去除掉浮点数，换成整数
void RenderSoftWare::DrawLineBresenham_1(Vector2D start, Vector2D end,SColor color)
{
    int x1 = start.X;
    int x2 = end.X;
    int deltaX = std::abs(x1 - x2);

    int y1 = start.Y;
    int y2 = end.Y;
    int deltaY = std::abs(y1 - y2);

    int MaxDel = std::max(deltaX,deltaY);

    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;

    int error = 0;
    int y = y1;
    int x = x1;

    int y3 = y1;
    int x3 = x1;
    // 假设往X的方向偏
    for (int i = 0; i <= MaxDel; ++i)
    {
        if(deltaX > deltaY)
        {
            x = x1 + i*sx;
            error += deltaY;
            if(error > MaxDel)
            {
                y3 += sy;
                error -= MaxDel;
            }

            if(2 * error > MaxDel)
            {
                y = y3 + sy;
            }
        }
        else
        {
            y = y1 + i*sy;
            error += deltaX;
            if(error > MaxDel)
            {
                x3 += sx;
                error -= MaxDel;
            }

            if(2 * error > MaxDel)
            {
                x = x3 + sx;
            }
        }

        frame_buffer.SetPixel(x, y, color);
    }

}

// 思路迭代演进，以递进的思路，较大的一定+1，小的看是否+1 就可以了，不用在乎很多中间状态
void RenderSoftWare::DrawLineBresenham_2(Vector2D start, Vector2D end,SColor color)
{
    int x1 = start.X;
    int x2 = end.X;
    int deltaX = std::abs(x1 - x2);

    int y1 = start.Y;
    int y2 = end.Y;
    int deltaY = std::abs(y1 - y2);

    int MaxDel = std::max(deltaX,deltaY);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;

    int error = 0;
    int x = x1;
    int y = y1;
    // 假设往X的方向偏
    for (int i = 0; i <= MaxDel; ++i)
    {
        // 如果 X 是主轴，允许 error 出现负数；当 2 * error >= MaxDel 时让 Y 前进一步
        if(deltaX > deltaY)
        {
            x = x1 + i*sx;
            frame_buffer.SetPixel(x, y, color);

            error += deltaY;
            if (2 * error >= MaxDel)
            {
                y += sy;
                error -= MaxDel;
            }

        }
        else
        {
            y = y1 + i*sy;
            frame_buffer.SetPixel(x, y, color);

            error += deltaX;
            if (2 * error >= MaxDel)
            {
                x += sx;
                error -= MaxDel;
            }
        }

    }
}

// Bresenham 第三版：使用 X/Y 两个独立的整数累加器，去除主轴分类分支。
// - 当前 (x,y) 永远是本轮要绘制的像素。
// - px/py 分别累计 X/Y 方向的前进量，超过半格时对应坐标前进一步。
// - deltaX、deltaY 中至少一个等于 MaxDel，因此至少有一个坐标每轮必定前进。
// - 当前版本仍由 MaxDel 控制循环次数，还不是经典的“单个有符号误差 + 到达终点结束”版本。

void RenderSoftWare::DrawLineBresenham_3(Vector2D start, Vector2D end, SColor color)
{
    int x1 = start.X;
    int x2 = end.X;
    int deltaX = std::abs(x1 - x2);

    int y1 = start.Y;
    int y2 = end.Y;
    int deltaY = std::abs(y1 - y2);

    int MaxDel = std::max(deltaX,deltaY);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;

    int px =0;
    int py =0;
    int x = x1;
    int y = y1;

    for (int i = 0; i <= MaxDel; ++i)
    {
        frame_buffer.SetPixel(x, y, color);

        px+=deltaX;
        py+=deltaY;

        if(px *2 > MaxDel)
        {
            px -= MaxDel;
            x += sx;
        }

        if(py *2 > MaxDel)
        {
            py -= MaxDel;
            y += sy;
        }
    }
}

// 替换为while形式，根据误差值，判断是否需要在另一轴+1
void RenderSoftWare::DrawLineBresenham_4(Vector2D start, Vector2D end, SColor color)
{
    int x = start.X;
    int x2 = end.X;

    int y = start.Y;
    int y2 = end.Y;

    int deltaX = std::abs(x - x2);
    int deltaY = std::abs(y - y2);

    int sx = x < x2 ? 1 : -1;
    int sy = y < y2 ? 1 : -1;

    int error = 0;
    while (true)
    {
        frame_buffer.SetPixel(x, y, color);

        if(x == x2 && y == y2)
        {
            break;
        }
        if( deltaX > deltaY)
        {
            // 如果X变化大相当于X是必走，每次都要走X
            x += sx;
            error += deltaY;
            if(error *2 > deltaX)
            {
                y += sy;
                error -= deltaX;
            }
        }
        else
        {
            y += sy;
            error += deltaX;
            if(error *2 > deltaY)
            {
                x += sx;
                error -= deltaY;
            }
        }
    }
}

// 去掉主轴if else 版本，没有理解，将其理解为经典版本，暂时先这样
void RenderSoftWare::DrawLineBresenham_5(Vector2D start, Vector2D end, SColor color)
{
    int x = start.X;
    int x2 = end.X;

    int y = start.Y;
    int y2 = end.Y;

    int deltaX = std::abs(x - x2);
    int deltaY = -std::abs(y - y2);

    int sx = x < x2 ? 1 : -1;
    int sy = y < y2 ? 1 : -1;

    int error = deltaX + deltaY;
    while (true)
    {
        frame_buffer.SetPixel(x, y, color);

        if(x == x2 && y == y2)
        {
            break;
        }
        const int error2 = 2 * error;

        if(error2 >= deltaY)
        {
            x += sx;
            error += deltaY;
        }

        if(error2 <= deltaX)
        {
            y += sy;
            error += deltaX;
        }
    }
}

void RenderSoftWare::DrawTriangle(Vector2D a, Vector2D b, Vector2D c)
{
    
}

void RenderSoftWare::DrawFilledTriangle(Vector2D A, Vector2D B, Vector2D C, SColor color)
{
    // 面积为0的三角形不画，直接return 掉
    const float are2 = MathUtil::Area2D(A, B, C);
    if (are2 == 0.0f)
    {
        return;
    }
    
    // 历一下周围像素，在三角形内的，点亮，三角形外的，不处理 可以使用AABB包围盒减少遍历范围
    // 如果像素中点在三角形内，则该像素点亮
    const int width  = frame_buffer.GetWidth();
    const int height = frame_buffer.GetHeight();

    const AABB2D aabb(A, B, C);

    const int min_x = std::max(0, static_cast<int>(std::floor(aabb.Min.X)));
    const int max_x = std::min(width  - 1, static_cast<int>(std::ceil(aabb.Max.X)));
    const int min_y = std::max(0, static_cast<int>(std::floor(aabb.Min.Y)));
    const int max_y = std::min(height - 1, static_cast<int>(std::ceil(aabb.Max.Y)));

    const Triangle2D triangle(A, B, C);
    for (int x = min_x; x <= max_x; ++x)
    {
        for (int y = min_y; y <= max_y; ++y)
        {
            // 判断每个像素中点是否在像素中
            const Vector2D point(static_cast<float>(x)+0.5f, static_cast<float>(y)+0.5f);
            
            if (MathUtil::IsPointInTriangle(point, triangle))
            {
                frame_buffer.SetPixel(x, y, color);
            }
        }
    }
    

}

void RenderSoftWare::DrawColoredTriangle(Vector2D A, Vector2D B, Vector2D C, SColor colorA, SColor colorB,SColor colorC)
{
    // 面积为0的三角形不画，直接return 掉
    const float are2 = MathUtil::Area2D(A, B, C);
    if (are2 == 0.0f)
    {
        return;
    }
    
    // 历一下周围像素，在三角形内的，点亮，三角形外的，不处理 可以使用AABB包围盒减少遍历范围
    // 如果像素中点在三角形内，则该像素点亮
    const int width  = frame_buffer.GetWidth();
    const int height = frame_buffer.GetHeight();

    const AABB2D aabb(A, B, C);

    const int min_x = std::max(0, static_cast<int>(std::floor(aabb.Min.X)));
    const int max_x = std::min(width  - 1, static_cast<int>(std::ceil(aabb.Max.X)));
    const int min_y = std::max(0, static_cast<int>(std::floor(aabb.Min.Y)));
    const int max_y = std::min(height - 1, static_cast<int>(std::ceil(aabb.Max.Y)));

    const Triangle2D triangle(A, B, C);
    for (int x = min_x; x <= max_x; ++x)
    {
        for (int y = min_y; y <= max_y; ++y)
        {
            // 判断每个像素中点是否在像素中
            const Vector2D point(static_cast<float>(x)+0.5f, static_cast<float>(y)+0.5f);
            
            if (MathUtil::IsPointInTriangle(point, triangle))
            {
                float w0 = MathUtil::Area2D(B, C, point) / are2;
                float w1 = MathUtil::Area2D(C, A, point) / are2;
                float w2 = MathUtil::Area2D(A, B, point) / are2;
                // 获得插值后的color
                const SColor color = SColor::Lerp(w0, colorA, w1, colorB, w2, colorC);
                
                frame_buffer.SetPixel(x, y, color);
            }
        }
    }
}

void RenderSoftWare::Present()
{
    // frame_buffer 转化为PNG
    const int width  = frame_buffer.GetWidth();
    const int height = frame_buffer.GetHeight();
    const SColor* src = frame_buffer.GetData();

    if (!src || width <= 0 || height <= 0)
    {
        return;
    }

    // SColor 的内存布局就是 R,G,B,A，与 stb 要求的字节序完全一致，可直接输出无需转换
    ImageUtil::SaveImage("Saved/Software/Frame.png", src, width, height, 4);
}
