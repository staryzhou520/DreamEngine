#pragma once

class RenderBase;

// 渲染器类型枚举
enum class RenderType
{
    OpenGL,
    Software,
    // 未来可以添加更多：Vulkan, DirectX 等
};

// 渲染器工厂类
class RenderFactory
{
public:
    // 根据类型创建对应的渲染器
    static RenderBase* CreateRenderer(RenderType type);
};
