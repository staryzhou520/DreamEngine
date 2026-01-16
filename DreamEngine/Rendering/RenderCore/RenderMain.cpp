#include "RenderMain.h"

#include "RenderBase.h"
#include "RenderFactory.h"


void RenderMain::Init()
{
    Render = RenderFactory::CreateRenderer(RenderType::Software);
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

