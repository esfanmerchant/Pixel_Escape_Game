#ifndef CHARACTERIMAGE
#define CHARACTERIMAGE

#include "raylib.h"
#include <string>

class CharacterImage
{
public:
    Texture2D standR, standL, jumpR, jumpL, walk1R, walk1L, walk2R, walk2L;
    Vector2 gunOffset;

    void Load(const std::string &s, const std::string &j, const std::string &w1, const std::string &w2, const Vector2 &go);

    void Unload();
};

#endif