#include "./includes/IceFire.h"
#include "./Includes/Global.h"

IceFire::IceFire(){}

IceFire::IceFire(Vector2 startPosition,int d, float s,  Texture2D tex)
{
    position = startPosition;
    direction = d;
    size = s;
    color = SKYBLUE;  
    texture = tex; 
}

void IceFire::Update(float dt)
{
    position.x += direction *BULLET_SPEED *dt;
}

void IceFire::Draw() const
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
