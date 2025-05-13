#include "./includes/Fire.h"
#include "./Includes/Global.h"

Fire::Fire() {}

Fire::Fire(Vector2 startPosition, int d, float s, Texture2D tex)
{
    position = startPosition;
    direction = d;
    size = s;
    color = RED;
    texture = tex;
}

void Fire::Update(float dt)
{
    position.x += direction * BULLET_SPEED * dt;
}

void Fire::Draw() const
{
    if (texture.width > 0 && texture.height > 0)
    {
        DrawTexture(texture, position.x, position.y, WHITE);
    }
    else
    {
        DrawCircleV(position, size, color);
    }
}
