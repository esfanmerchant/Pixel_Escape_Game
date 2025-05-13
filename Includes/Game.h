#ifndef GAME
#define GAME

#include <vector>
#include <raylib.h>
#include <string>
#include "Character.h"
#include "CharacterImage.h"
#include "Bullet.h"
#include "Platform.h"
#include "Global.h"
#include "Toast.h"
#include "User.h"
#include "IceMonster.h"
#include "FireMonster.h"

enum class GameState
{
    LOGIN,
    MENU,
    LEVEL_SELECTION,
    PLAYING,
    GAME_OVER
};

enum FormState
{
    LOGIN,
    REGISTER
};

enum class Levels
{
    LEVEL1,
    LEVEL2,
    LEVEL3
};

enum class InputField
{
    NONE,
    USERNAME,
    PASSWORD,
    CONFIRM_PASSWORD
};


class Game
{
public:
    int winW, winH;
    float worldW;
    Camera2D camera;
    GameState state;
    int score = 0;
    Levels currentLevel;

    Texture2D background;
    float bgRatio;

    Texture2D floorTex, plat1Tex, plat2Tex;
    int plat1White = 45, plat2White = 20;

    std::vector<Platform> platforms;
    Character player, *monster = nullptr;
    float monsterTimer;
    bool exitGame;
    
    Sound jump,death;
    Rectangle btnStart, btnRestart, btnQuit, btnLevel1, btnLevel2, btnLevel3;

    Rectangle loginButton;
    Rectangle usernameField;
    Rectangle passwordField;
    Rectangle confirmPasswordField;
    FormState currentForm = LOGIN;
    std::string username;
    std::string password;
    std::string confirmPassword;
    User user;
    Toast toast;

    InputField currentInput = InputField::NONE;

    Game();

    void Init();

    void CreatePlatforms();

    void Reset();

    std::string GetButtonText();

    void Run();

    void Update(float dt);

    void Draw();

    void Cleanup();

    void SwitchLevel(Levels newLevel);

};

#endif
