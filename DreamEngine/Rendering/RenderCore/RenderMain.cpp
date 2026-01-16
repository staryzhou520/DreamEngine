#include "RenderMain.h"

#include "RenderBase.h"
#include "../OpenGL/RenderOpenGL.h"


void RenderMain::Init()
{
    Render = new RenderOpenGL();
    Render->Init();
}

void RenderMain::Tick()
{
    Object::Tick();

    if(Render)
    {
        Render->Draw();
    }
}

