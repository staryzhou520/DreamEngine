#include "WindowsInputProcessor.h"
#include <iostream>
#include <windows.h>

void WindowsInputProcessor::ProcessInput()
{
    // 处理键盘输入
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        // ESC键按下处理
        std::cout << "ESC pressed (Windows)" << std::endl;
    }
    
    // 处理鼠标输入
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        // 左键点击处理
        std::cout << "Left mouse clicked at: " << cursorPos.x << ", " << cursorPos.y << " (Windows)" << std::endl;
    }
    
    if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
        // 右键点击处理
        std::cout << "Right mouse clicked (Windows)" << std::endl;
    }
    
    // 处理WASD移动输入
    if (GetAsyncKeyState('W') & 0x8000) {
        // 向前移动
        std::cout << "Move forward (Windows)" << std::endl;
    }
    if (GetAsyncKeyState('A') & 0x8000) {
        // 向左移动
        std::cout << "Move left (Windows)" << std::endl;
    }
    if (GetAsyncKeyState('S') & 0x8000) {
        // 向后移动
        std::cout << "Move backward (Windows)" << std::endl;
    }
    if (GetAsyncKeyState('D') & 0x8000) {
        // 向右移动
        std::cout << "Move right (Windows)" << std::endl;
    }
}

bool WindowsInputProcessor::ShouldExit()
{
    // 检查是否按下ESC键
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        return true;
    }
    return false;
}