#ifndef BULLET
#define BULLET

#include <raylib.h>

class Bullet
{
public:
    Vector2 position;
    int direction;
    int size;

    Bullet(const Vector2 &p = {0, 0}, int d = 1, int s = 15);

    void Update(float dt);
    void Draw() const;
};

#endif