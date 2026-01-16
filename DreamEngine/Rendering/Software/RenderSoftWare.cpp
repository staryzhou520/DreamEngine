#include "RenderSoftWare.h"

#include <cstdint>
#include <vector>

#include "../../Core/Image/ImageUtil.h"

// CPU版软光栅器

void RenderSoftWare::Init()
{
    const int width = 800;
    const int height = 600;

    // uint32 ## AA RR GG NN
    std::vector<uint32_t> framebuffer(width * height);

    for (uint32_t& value : framebuffer) 
        value = 0xFFFF0000;
    

    ImageUtil::SaveImageFromFramebuffer("Saved/Software/Software.png", framebuffer.data(), width, height);
}

void RenderSoftWare::Draw()
{
    
}

