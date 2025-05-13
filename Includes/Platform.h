#ifndef PLATFORM_H
#define PLATFORM_H

#include <raylib.h> 


enum class PlatformType
{
    PLATFORM, 
    FLOOR     
};


struct Platform
{
    Rectangle rec;     
    PlatformType type; 

    Platform();

    
    Platform(Rectangle r, PlatformType t);
};

#endif 
