#pragma once

#include <cstdint>
#include <algorithm>
#include <cmath>

// 颜色结构体，内存字节序为 R,G,B,A
// 说明：内存布局与 stb_image / stb_image_write / OpenGL GL_RGBA 一致，可直接输出
//       但用整数表示时仍沿用 0xAARRGGBB 的写法（见 ToUInt32）
struct SColor
{
    uint8_t R;  // Red 红色
    uint8_t G;  // Green 绿色
    uint8_t B;  // Blue 蓝色
    uint8_t A;  // Alpha 透明度

    // 默认构造函数，初始化为不透明黑色
    SColor() : R(0), G(0), B(0), A(255) {}

    // 带参数构造函数，参数顺序与内存布局一致：r,g,b,a
    SColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : R(r), G(g), B(b), A(a) {}

    // 从 uint32_t 构造 (格式: 0xAARRGGBB)
    explicit SColor(uint32_t argb)
        : R((argb >> 16) & 0xFF)
        , G((argb >> 8) & 0xFF)
        , B(argb & 0xFF)
        , A((argb >> 24) & 0xFF) {}

    // 预定义常用颜色（顺序 r,g,b,a）
    static SColor Red()   { return SColor(255, 0, 0, 255); }
    static SColor Green() { return SColor(0, 255, 0, 255); }
    static SColor Blue()  { return SColor(0, 0, 255, 255); }
    static SColor Yellow() { return SColor(255, 255, 0, 255); }
    static SColor White() { return SColor(255, 255, 255, 255); }
    static SColor Black() { return SColor(0, 0, 0, 255); }

    // 按权重线性插值：result = wR*R + wG*G + wB*B（wR/wG/wB 为重心坐标，和为1）
    // 用于三角形内每个像素的颜色插值，结果四舍五入到最近的整数通道值
    static SColor Lerp(float wR, const SColor& cR,
                       float wG, const SColor& cG,
                       float wB, const SColor& cB)
    {
        const auto toByte = [](float v) -> uint8_t
        {
            v = std::min(std::max(v, 0.0f), 255.0f);
            return static_cast<uint8_t>(std::round(v));
        };
        
        const float r = wR * cR.R + wG * cG.R + wB * cB.R;
        const float g = wR * cR.G + wG * cG.G + wB * cB.G;
        const float b = wR * cR.B + wG * cG.B + wB * cB.B;
        const float a = wR * cR.A + wG * cG.A + wB * cB.A;
        return SColor(toByte(r),toByte(g),toByte(b),toByte(a));
    }
};
