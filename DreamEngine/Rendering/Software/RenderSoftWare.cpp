#include "RenderSoftWare.h"

#include <cstdint>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <shellapi.h>

#include "../../Core/Image/ImageUtil.h"
#include "../../Core/FileSystem/FileUtil.h"

// CPU版软光栅器

void RenderSoftWare::Init()
{
    const int width = 800;
    const int height = 600;

    // uint32 ## AA RR GG NN
    std::vector<uint32_t> framebuffer(width * height);

    for (uint32_t& value : framebuffer) 
        value = 0xFFFF0000;
    

    const std::string imagePath = "Saved/Software/Software.png";
    bool success = ImageUtil::SaveImageFromFramebuffer(imagePath, framebuffer.data(), width, height);

    // 保存成功后自动打开图片
    if (success)
    {
        // 获取绝对路径
        std::string absolutePath = FileUtil::ConvertToAbsolutePath(imagePath.c_str());
        
        HINSTANCE result = ShellExecuteA(NULL, "open", absolutePath.c_str(), NULL, NULL, SW_SHOWNORMAL);
        if ((INT_PTR)result <= 32)
        {
            std::cout << "Failed to open image: " << absolutePath << " (Error code: " << (INT_PTR)result << ")" << std::endl;
        }
    }
    else
    {
        std::cout << "Failed to save image: " << imagePath << std::endl;
    }

    
}

void RenderSoftWare::Draw()
{
    
}

