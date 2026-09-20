#pragma once

#include <cstdint>

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

    // 转换为 uint32_t (格式: 0xAARRGGBB)
    uint32_t ToUInt32() const
    {
        return (static_cast<uint32_t>(A) << 24) |
               (static_cast<uint32_t>(R) << 16) |
               (static_cast<uint32_t>(G) << 8) |
               static_cast<uint32_t>(B);
    }

    // 预定义常用颜色（顺序 r,g,b,a）
    static SColor Red()   { return SColor(255, 0, 0, 255); }
    static SColor Green() { return SColor(0, 255, 0, 255); }
    static SColor Blue()  { return SColor(0, 0, 255, 255); }
    static SColor Yellow() { return SColor(255, 255, 0, 255); }
    static SColor White() { return SColor(255, 255, 255, 255); }
    static SColor Black() { return SColor(0, 0, 0, 255); }
};

// 保证结构体紧密排列为 4 字节，这样才能直接把缓冲区交给图像库
static_assert(sizeof(SColor) == 4, "SColor must be tightly packed to 4 bytes");
