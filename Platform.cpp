#include "./includes/Platform.h"

Platform::Platform()
    : rec{0, 0, 0, 0}, type(PlatformType::PLATFORM)
{
}


Platform::Platform(Rectangle r, PlatformType t)
    : rec(r), type(t) 
{
}
