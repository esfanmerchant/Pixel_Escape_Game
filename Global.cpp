#include "./includes/Global.h"

float SCALE_FACTOR = 1.9f;
float BULLET_SPEED = 900.f;
int MAX_BULLETS = 40;
float MONSTER_SHOOT_INTERVAL = 1.0f; // seconds

float clampf(float v, float lo, float hi)
{
    return (v < lo ? lo : (v > hi ? hi : v));
}