#pragma once

class IInputProcessor;

// 输入工厂类
class InputFactory
{
public:
    static IInputProcessor* CreateInputProcessor();
    static void DestroyInputProcessor(IInputProcessor* processor);
};