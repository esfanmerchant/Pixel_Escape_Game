#include <iostream>
#include "./includes/Bullet.h"
#include "./includes/Global.h"
#include "./includes/Game.h"
#include <raylib.h>

Bullet::Bullet(const Vector2 &p, int d, int s)
    : position(p), direction(d), size(s) {}

void Bullet::Update(float dt)
{
    position.x += direction * BULLET_SPEED * dt;
}

void Bullet::Draw() const
{   
    DrawCircleV(position, size, YELLOW);
}
