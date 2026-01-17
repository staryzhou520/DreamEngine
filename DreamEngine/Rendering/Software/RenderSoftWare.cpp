#include "RenderSoftWare.h"

#include <cstdint>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <shellapi.h>

#include "../../Core/Image/ImageUtil.h"
#include "../../Core/FileSystem/FileUtil.h"
#include "../../Core/Color/SColor.h"

// CPU版软光栅器

void RenderSoftWare::Init()
{
    // 使用 SColor 结构体存储颜色
    std::vector<SColor> framebuffer(Width * Height);

    for (SColor& color : framebuffer) 
        color = SColor::Red();
    

    const std::string imagePath = "Saved/Software/Software.png";
    bool success = ImageUtil::SaveImageFromFramebuffer(imagePath, reinterpret_cast<uint32_t*>(framebuffer.data()), Width, Height);

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

