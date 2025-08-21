#include "InputFactory.h"
#include "IInputProcessor.h"
#include "WindowsInputProcessor.h"
#include "MobileInputProcessor.h"

#ifdef _WIN32
    #define PLATFORM_WINDOWS
#elif defined(__ANDROID__) || defined(__IOS__)
    #define PLATFORM_MOBILE
#endif

// 工厂方法实现
IInputProcessor* InputFactory::CreateInputProcessor()
{
#ifdef PLATFORM_WINDOWS
    return new WindowsInputProcessor();
#elif defined(PLATFORM_MOBILE)
    return new MobileInputProcessor();
#else
    return nullptr;
#endif
}

void InputFactory::DestroyInputProcessor(IInputProcessor* processor)
{
    if (processor)
    {
        delete processor;
        processor = nullptr;
    }
}