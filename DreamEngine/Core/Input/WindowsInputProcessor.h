#pragma once

#include "IInputProcessor.h"

// Windows输入处理器
class WindowsInputProcessor : public IInputProcessor
{
public:
    void ProcessInput() override;
    bool ShouldExit() override;
};