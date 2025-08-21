#include <iostream>

#include "Core/Object.h"
#include "Core/Input/IInputProcessor.h"
#include "Game/GameMain.h"
#include "Rendering/RenderCore/RenderMain.h"
#include "Core/Input/InputFactory.h"

GameMain* _GameMain;
RenderMain* _RenderMain;
IInputProcessor* _InputProcessor;

void InitGame()
{
     _GameMain = new GameMain();
     _RenderMain = new RenderMain();
    
    _GameMain->Init();
    _RenderMain->Init();
    
    // 创建输入处理器
    _InputProcessor = InputFactory::CreateInputProcessor();
}

// 清理资源
void CleanupGame()
{
    if (_InputProcessor)
    {
        InputFactory::DestroyInputProcessor(_InputProcessor);
        _InputProcessor = nullptr;
    }
    
    if (_RenderMain)
    {
        delete _RenderMain;
        _RenderMain = nullptr;
    }
    
    if (_GameMain)
    {
        delete _GameMain;
        _GameMain = nullptr;
    }
}

int main(int argc, char* argv[])
{
    
    InitGame();
    
    while (true)
    {
        // 获取用户输入
        _InputProcessor->ProcessInput();

        // 是否退出游戏
        if(_InputProcessor->ShouldExit())
        {
            break;
        }

        // Tick可以使用一个优先队列，不同模块的优先级可配置，这样方便后期调整
        
        // 游戏主循环
        _GameMain->Tick();

        // 渲染主循环
        _RenderMain->Tick();
        
    }
    
    CleanupGame();
    
    return 0;
}