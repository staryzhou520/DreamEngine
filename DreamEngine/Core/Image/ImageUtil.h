#pragma once
#include <string>
#include <cstdint>

class ImageUtil
{
public:
    // IamgePath: RelativePath /Save/Iamge.png
    // 与ReleaseImageData成对调用，ImageData需要手动释放
    static unsigned char* LoadImage(std::string ImagePath, int &width, int &height, int &nrChannels);

    static void ReleaseImageData(unsigned char* ImageData);

    /**
     * 将 framebuffer 保存为图片文件
     * @param ImagePath 保存路径，支持 .png, .jpg, .bmp, .tga 格式
     * @param data framebuffer 数据（RGBA 格式，每像素 4 字节）
     * @param width 图片宽度
     * @param height 图片高度
     * @param channels 通道数（3=RGB, 4=RGBA）
     * @return 成功返回 true，失败返回 false
     */
    static bool SaveImage(const std::string& ImagePath, const void* data, int width, int height, int channels = 4);

    /**
     * 将 uint32_t 格式的 framebuffer 保存为图片文件
     * @param ImagePath 保存路径
     * @param framebuffer uint32_t 数组（每个元素表示一个像素，格式为 0xAABBGGRR 或 0xRRGGBBAA）
     * @param width 图片宽度
     * @param height 图片高度
     * @return 成功返回 true，失败返回 false
     */
    static bool SaveImageFromFramebuffer(const std::string& ImagePath, const uint32_t* framebuffer, int width, int height);
};
