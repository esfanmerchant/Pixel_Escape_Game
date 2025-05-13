#include "./includes/CharacterImage.h"
using namespace std;

void CharacterImage::Load(const string &s, const string &j, const string &w1, const string &w2,  const Vector2 &go)
{
    gunOffset = go;
    auto LP = [&](const string &path, Texture2D &R, Texture2D &L)
    {
        Image img = LoadImage(path.c_str());
        R = LoadTextureFromImage(img);
        ImageFlipHorizontal(&img);
        L = LoadTextureFromImage(img);
        UnloadImage(img);
    };
    LP(s, standR, standL);
    LP(j, jumpR, jumpL);
    LP(w1, walk1R, walk1L);
    LP(w2, walk2R, walk2L);
}

void CharacterImage::Unload()
{
    UnloadTexture(standR);
    UnloadTexture(standL);
    UnloadTexture(jumpR);
    UnloadTexture(jumpL);
    UnloadTexture(walk1R);
    UnloadTexture(walk1L);
    UnloadTexture(walk2R);
    UnloadTexture(walk2L);
}
