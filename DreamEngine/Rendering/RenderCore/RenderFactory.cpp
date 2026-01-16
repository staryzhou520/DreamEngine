#include "RenderFactory.h"
#include "RenderBase.h"
#include "../OpenGL/RenderOpenGL.h"
#include "../Software/RenderSoftWare.h"

RenderBase* RenderFactory::CreateRenderer(RenderType type)
{
    switch (type)
    {
        case RenderType::OpenGL:
            return new RenderOpenGL();
        case RenderType::Software:
            return new RenderSoftWare();
        default:
            return nullptr;
    }
}
