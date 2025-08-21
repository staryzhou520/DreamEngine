#pragma once

// 抽象输入处理器接口
class IInputProcessor
{
public:
    virtual ~IInputProcessor() = default;
    virtual void ProcessInput() = 0;
    virtual bool ShouldExit() = 0;
};