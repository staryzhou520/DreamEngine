#pragma once

#include "IInputProcessor.h"

// 移动端输入处理器
class MobileInputProcessor : public IInputProcessor
{
public:
    void ProcessInput() override;
    bool ShouldExit() override;
};