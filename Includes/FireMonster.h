#ifndef Fire_MONSTER
#define Fire_MONSTER

#include <raylib.h>
#include <vector>
#include "Bullet.h"
#include "CharacterImage.h"
#include "Character.h"
#include "Global.h"
#include "Platform.h"
#include "Fire.h"

class FireMonster : public Character
{
public:
    std::vector<Fire> FFires;

    FireMonster(CharacterImage img);
    void Shoot() override;
    void Update(float dt, const std::vector<Platform> &plats, float winW, float worldW) override;
    void Draw(const Camera2D &cam) const override;
    void Unload() override;
};

#endif