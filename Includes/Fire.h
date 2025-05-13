#ifndef FIRE
#define FIRE

#include <raylib.h>

class Fire
{
public:
    Vector2 position;
    int direction;
    float size;
    Color color;
    Texture2D texture;

    Fire();
    Fire(Vector2 startPosition, int d, float s = 15, Texture2D tex = Texture2D());

    void Update(float dt);

    void Draw() const;
};

#endif