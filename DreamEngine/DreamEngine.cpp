#include <iostream>
#include <chrono>
#include <thread>

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
    // 从配置文件读取目标帧率
    int TargetFPS = 60;
    const std::chrono::milliseconds TargetFrameTime(1000 / TargetFPS);
    
    std::cout << "Target FPS: " << TargetFPS << std::endl;
    
    InitGame();
    
    auto LastFrameTime = std::chrono::high_resolution_clock::now();
    
    while (true)
    {
        auto FrameStartTime = std::chrono::high_resolution_clock::now();
        
        // 计算上一帧的耗时
        auto DeltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(
            FrameStartTime - LastFrameTime).count();
        LastFrameTime = FrameStartTime;
        
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
        
        // 帧率控制
        auto FrameEndTime = std::chrono::high_resolution_clock::now();
        auto FrameTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            FrameEndTime - FrameStartTime);
        
        if (FrameTime < TargetFrameTime)
        {
            auto SleepTime = TargetFrameTime - FrameTime;
            std::this_thread::sleep_for(SleepTime);
        }
        
        // 可选：打印帧率信息用于调试
        // std::cout << "FPS: " << (1000.0f / std::max(FrameTime.count(), 1ll)) << std::endl;
    }
    
    CleanupGame();
    
    return 0;
}