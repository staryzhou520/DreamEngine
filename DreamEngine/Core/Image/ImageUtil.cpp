#define _CRT_SECURE_NO_WARNINGS

#include "ImageUtil.h"
#include <iostream>
#include <vector>
#include <direct.h>    // _mkdir
#include <sys/stat.h>  // _stat

#define STB_IMAGE_IMPLEMENTATION
#include "../Plugin/stb_Image/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../Plugin/stb_Image/stb_image_write.h"

unsigned char* ImageUtil::LoadImage(std::string ImagePath, int &width, int &height, int &nrChannels)
{
    unsigned char *data = stbi_load(ImagePath.c_str(), &width, &height, &nrChannels, 0);
    if(!data)
    {
        std::cout<<"ImageUtil::LoadImage error ImagePath:"<< ImagePath << std::endl;
    }
    return data;
}

void ImageUtil::ReleaseImageData(unsigned char* ImageData)
{
    stbi_image_free(ImageData);
}

bool ImageUtil::SaveImage(const std::string& ImagePath, const void* data, int width, int height, int channels)
{
    if (!data || width <= 0 || height <= 0)
    {
        std::cout << "ImageUtil::SaveImage error: invalid parameters" << std::endl;
        return false;
    }

    // 自动创建目录（如果不存在）
    size_t lastSlash = ImagePath.find_last_of("/\\");
    if (lastSlash != std::string::npos)
    {
        std::string dirPath = ImagePath.substr(0, lastSlash);
        std::string currentPath;
        for (size_t i = 0; i < dirPath.size(); ++i)
        {
            if (dirPath[i] == '/' || dirPath[i] == '\\')
            {
                if (!currentPath.empty())
                {
                    _mkdir(currentPath.c_str());
                }
            }
            currentPath += dirPath[i];
        }
        if (!currentPath.empty())
        {
            _mkdir(currentPath.c_str());
        }
    }

    int result = 0;
    
    // 根据文件扩展名选择保存格式
    size_t dotPos = ImagePath.rfind('.');
    if (dotPos != std::string::npos)
    {
        std::string ext = ImagePath.substr(dotPos);
        
        if (ext == ".png" || ext == ".PNG")
        {
            result = stbi_write_png(ImagePath.c_str(), width, height, channels, data, width * channels);
        }
        else if (ext == ".jpg" || ext == ".jpeg" || ext == ".JPG" || ext == ".JPEG")
        {
            result = stbi_write_jpg(ImagePath.c_str(), width, height, channels, data, 90); // 90 是质量参数
        }
        else if (ext == ".bmp" || ext == ".BMP")
        {
            result = stbi_write_bmp(ImagePath.c_str(), width, height, channels, data);
        }
        else if (ext == ".tga" || ext == ".TGA")
        {
            result = stbi_write_tga(ImagePath.c_str(), width, height, channels, data);
        }
        else
        {
            // 默认保存为 PNG
            result = stbi_write_png(ImagePath.c_str(), width, height, channels, data, width * channels);
        }
    }
    else
    {
        // 没有扩展名，默认保存为 PNG
        result = stbi_write_png(ImagePath.c_str(), width, height, channels, data, width * channels);
    }

    if (!result)
    {
        std::cout << "ImageUtil::SaveImage error ImagePath:" << ImagePath << std::endl;
        return false;
    }

    return true;
}

bool ImageUtil::SaveImageFromFramebuffer(const std::string& ImagePath, const uint32_t* framebuffer, int width, int height)
{
    if (!framebuffer || width <= 0 || height <= 0)
    {
        std::cout << "ImageUtil::SaveImageFromFramebuffer error: invalid parameters" << std::endl;
        return false;
    }

    // 将 uint32_t framebuffer 转换为 RGBA 字节数组
    // 假设 framebuffer 中每个 uint32_t 的格式为 0xAARRGGBB（小端序下内存布局为 BB GG RR AA）
    std::vector<unsigned char> imageData(width * height * 4);
    
    for (int i = 0; i < width * height; ++i)
    {
        uint32_t pixel = framebuffer[i];
        // 从 0xAARRGGBB 格式提取各通道
        imageData[i * 4 + 0] = (pixel >> 16) & 0xFF; // R
        imageData[i * 4 + 1] = (pixel >> 8) & 0xFF;  // G
        imageData[i * 4 + 2] = pixel & 0xFF;         // B
        imageData[i * 4 + 3] = (pixel >> 24) & 0xFF; // A
    }

    return SaveImage(ImagePath, imageData.data(), width, height, 4);
}