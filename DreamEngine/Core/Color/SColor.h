#pragma once

#include <cstdint>

// 颜色结构体，包含 ARGB 四个通道
struct SColor
{
    uint8_t A;  // Alpha 透明度
    uint8_t R;  // Red 红色
    uint8_t G;  // Green 绿色
    uint8_t B;  // Blue 蓝色

    // 默认构造函数，初始化为不透明黑色
    SColor() : A(255), R(0), G(0), B(0) {}

    // 带参数构造函数
    SColor(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
        : A(a), R(r), G(g), B(b) {}

    // 从 uint32_t 构造 (格式: 0xAARRGGBB)
    explicit SColor(uint32_t argb)
        : A((argb >> 24) & 0xFF)
        , R((argb >> 16) & 0xFF)
        , G((argb >> 8) & 0xFF)
        , B(argb & 0xFF) {}

    // 转换为 uint32_t (格式: 0xAARRGGBB)
    uint32_t ToUInt32() const
    {
        return (static_cast<uint32_t>(A) << 24) |
               (static_cast<uint32_t>(R) << 16) |
               (static_cast<uint32_t>(G) << 8) |
               static_cast<uint32_t>(B);
    }

    // 预定义常用颜色
    static SColor Red()   { return SColor(255, 255, 0, 0); }
    static SColor Green() { return SColor(255, 0, 255, 0); }
    static SColor Blue()  { return SColor(255, 0, 0, 255); }
    static SColor White() { return SColor(255, 255, 255, 255); }
    static SColor Black() { return SColor(255, 0, 0, 0); }
};
