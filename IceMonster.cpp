#include "./includes/IceMonster.h"
#include <raylib.h>
#include <iostream>
using namespace std;

IceMonster::IceMonster(CharacterImage img)
{
    Init(1300.f, 200.f, 406, 339, 200.f, 1000.f, KEY_F, true, img);
    iceFires.resize(MAX_BULLETS);
}

void IceMonster::Shoot()
{
    Texture2D fireTexture = LoadTexture("img/level2/IceFire.png");
    Vector2 spawn = {
    x + (direction == 1 ? image.gunOffset.x : width - image.gunOffset.x),
        y + image.gunOffset.y};
    iceFires[nextBullet] = IceFire(spawn, direction,15,fireTexture);
    nextBullet = (nextBullet + 1) % MAX_BULLETS;
}

void IceMonster::Update(float dt, const vector<Platform> &plats, float winW, float worldW)
{
    // 1) Input (player) or AI walk flag
    if (!isAI)
    {
        walking = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT);
        if (IsKeyDown(KEY_LEFT))
        {
            direction = -1;
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            score++;
            direction = 1;
        }
        // manual jump/dive
        if (IsKeyPressed(KEY_UP) && !jumping)
        {
            velocityY = -jumpStrength * SCALE_FACTOR;
            jumping = true;
            PlaySound(*jump);
        }
        if (IsKeyPressed(KEY_DOWN) && !jumping)
        {
            velocityY = jumpStrength * SCALE_FACTOR;
            jumping = true;
        }
    }

    // 2) Horizontal obstacle detection (mid-body)
    if (walking)
    {
        float checkDist = 5.f;
        float topY = y + height * 0.2f;
        float hgt = height * 0.6f;
        Rectangle bodyCheck = {
            x + (direction == 1 ? checkDist : -width - checkDist),
            topY,
            width + 2 * checkDist,
            hgt};
        bool blocked = false;
        for (size_t i = 0; i < plats.size(); ++i)
        {
            if (CheckCollisionRecs(bodyCheck, plats[i].rec))
            {
                blocked = true;
                break;
            }
        }
        if (blocked)
        {
            walking = false;
            if (isAI && !jumping)
            {
                velocityY = -jumpStrength * SCALE_FACTOR;
                jumping = true;
            }
        }
    }

    // 3) Move horizontally
    if (walking)
    {
        x += direction * speed * dt * SCALE_FACTOR;
    }

    // 4) Gravity
    y += velocityY * dt;
    velocityY += 3000.f * SCALE_FACTOR * dt;

    // 5) Landing & player jump on land
    for (size_t i = 0; i < plats.size(); ++i)
    {
        Rectangle feet = {
            x + 10.f,
            y + height - height * 0.2f,
            width - 20.f,
            height * 0.2f + 2.f};
        if ((plats[i].type == PlatformType::PLATFORM || plats[i].type == PlatformType::FLOOR) &&
            CheckCollisionRecs(feet, plats[i].rec) && velocityY > 0)
        {
            y = plats[i].rec.y - height;
            velocityY = 0;
            jumping = false;
            if (!isAI && IsKeyPressed(jumpKey))
            {
                velocityY = -jumpStrength * SCALE_FACTOR;
                jumping = true;
            }
            break;
        }
    }

    // 6) World bounds
    x = clampf(x, 0.f, worldW - width);

    // 7) IceFires update
    for (auto &b : iceFires)
        b.Update(dt);
}

void IceMonster::Draw(const Camera2D &cam) const
{
    Texture2D tex;
    if (jumping)
        tex = (direction < 0 ? image.jumpL : image.jumpR);
    else if (walking)
    {
        int f = int(GetTime() * 10) % 2;
        if (direction < 0)
            tex = (f ? image.walk2L : image.walk1L);
        else
            tex = (f ? image.walk2R : image.walk1R);
    }
    else
    {
        tex = (direction < 0 ? image.standL : image.standR);
    }
    DrawTexture(tex, int(x), int(y), WHITE);
    for (auto &b : iceFires)
        b.Draw();
}

void IceMonster::Unload() { image.Unload(); }