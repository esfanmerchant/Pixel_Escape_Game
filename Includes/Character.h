#ifndef CHARACTER
#define CHARACTER

#include <raylib.h>
#include <vector>
#include "Bullet.h"
#include "CharacterImage.h"
#include "Global.h"
#include "Platform.h"
#include "IceFire.h"

class Character
{
public:
    float x, y;
    int width, height;
    float velocityY;
    int direction;
    bool walking, jumping;
    float speed, jumpStrength;
    bool isAI;
    int jumpKey;
    CharacterImage image;
    std::vector<Bullet> bullets;
    int nextBullet;
    int score = 0;

    Sound *jump = nullptr;

    Character();

    void Init(float px, float py, int w, int h, float spd, float jStr, int jKey, bool ai, const CharacterImage &img);

    virtual void Shoot();

    virtual void Update(float dt, const std::vector<Platform> &plats, float winW, float worldW);

    virtual void Draw(const Camera2D &cam) const;

    virtual void Unload();

    void SetJumpSound(Sound *sfx);

    virtual ~Character(){}
};

#endif