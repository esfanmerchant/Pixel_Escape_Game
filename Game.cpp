#include "./includes/Game.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace std;

Game::Game()
    : state(GameState::MENU), monsterTimer(0), exitGame(false)
{
    camera = {{0, 0}, {0, 0}, 0, 1.f};
}

void Game::SwitchLevel(Levels newLevel) {
    // Clean previous monster
    if (monster) {
        delete monster;
        monster = nullptr;
    }

    // Load monster textures
    CharacterImage monsterImg;
    
    switch (newLevel) {
        case Levels::LEVEL1:
            background = LoadTexture("img/background.png");
            floorTex = LoadTexture("img/floor.png");
            plat1Tex = LoadTexture("img/platform1.png"); 
            plat2Tex = LoadTexture("img/platform2.png");
            monsterImg.Load("img/monster_right_1.png", "img/monster_right_1.png","img/monster_right_1.png", "img/monster_right_2.png", {400, 170});
            monster = new Character();
            if (monster) {
                monster->Init(winW + 500.f, winH / 2.f, 406, 339, 200.f, 1000.f, KEY_F, true, monsterImg);
                std::cout << "Monster initialized at: " << monster->x << "," << monster->y << std::endl;
            } else {
                std::cerr << "FAILED TO CREATE MONSTER!" << std::endl;
            }
            break;
            
        case Levels::LEVEL2:
            background = LoadTexture("img/Ice_Background.jpg");
            floorTex = LoadTexture("img/IceFloor.png");
            plat1Tex = LoadTexture("img/IcePlat1.png"); 
            plat2Tex = LoadTexture("img/IcePlat2.png");
            monsterImg.Load("img/FlyingRight.png", "img/FlyingRight.png","img/FlyingRight.png", "img/Fire_right.png", {400, 170});
            monster = new IceMonster(monsterImg);
            if (monster) {
                monster->Init(winW + 500.f, winH / 2.f, 406, 339, 200.f, 1000.f, KEY_F, true, monsterImg);
                std::cout << "Monster initialized at: " << monster->x << "," << monster->y << std::endl;
            } else {
                std::cerr << "FAILED TO CREATE MONSTER!" << std::endl;
            }
            break;
        
        case Levels::LEVEL3:
            background = LoadTexture("img/Flamebackground.jpg");
            floorTex = LoadTexture("img/IceFloor.png");
            plat1Tex = LoadTexture("img/Flameplatform1.png");
            plat2Tex = LoadTexture("img/Flameplatform2.png");
            monsterImg.Load("img/wizard.png", "img/wizard.png", "img/wizard.png", "img/wizardShoot.png", {400, 170});
            monster = new FireMonster(monsterImg);
            if (monster)
            {
                monster->Init(winW + 500.f, winH / 2.f, 406, 339, 200.f, 1000.f, KEY_F, true, monsterImg);
                std::cout << "Monster initialized at: " << monster->x << "," << monster->y << std::endl;
            }
            else
            {
                std::cerr << "FAILED TO CREATE MONSTER!" << std::endl;
            }
        break;
    }
}
void Game::Init()
{
    srand((unsigned)time(NULL));
    winW = int(800 * SCALE_FACTOR);
    winH = int(500 * SCALE_FACTOR);
    worldW = winW * 10.f;

    InitWindow(winW, winH, "Pixel Escape");
    SetTargetFPS(60);

    CharacterImage pImg;
    bgRatio = 1.f / ((worldW - winW) / float(background.width - winW));

    InitAudioDevice();

    // load character images
    pImg.Load("img/standing.png", "img/jumping.png", "img/walk1.png", "img/walk2.png", {0, 0});

    // placeholder init
    player.Init(winW / 2.f, winH / 2.f, 101, 260, 250.f, 1000.f, KEY_SPACE, false, pImg);
    player.SetJumpSound(&jump);
    SwitchLevel(Levels::LEVEL1);

    CreatePlatforms();

    int bw = 200, bh = 60;
    btnStart = {(float)winW / 2 - bw / 2, (float)winH / 2 - bh / 2, float(bw), float(bh)};
    btnRestart = btnStart;
    btnQuit = {(float)winW / 2 - bw / 2, (float)winH / 2 + bh, float(bw), float(bh)};
    btnLevel1 = {(float)winW / 2 - bw / 2 - 50, (float)winH / 2 - 30, float(bw), float(bh)};
    btnLevel2 = {(float)winW / 2 - bw / 2 - 50, (float)winH / 2 + 35, float(bw), float(bh)};
    btnLevel3 = {(float)winW / 2 - bw / 2 - 50, (float)winH / 2 + 100, float(bw), float(bh)};

    jump = LoadSound("./music/jump.mp3");
    death = LoadSound("./music/death.mp3");
}

void Game::CreatePlatforms()
{
    platforms.clear();
    int fpw = 490, fph = 190, x = 0;
    int cnt = int(ceil(worldW / fpw));
    for (int i = 0; i < cnt; ++i)
    {
        platforms.push_back({{float(x), float(winH - fph + 33), float(fpw), float(fph)}, PlatformType::FLOOR});
        x += fpw;
    }
    int pw = 180, ph = 50;
    float minY = winH * 0.2f, maxY = winH - fph - ph - minY;
    x = int(winW * 0.1f);
    while (float(x) < worldW)
    {
        platforms.push_back({{float(x), float(GetRandomValue(int(minY), int(minY + maxY))), float(pw), float(ph)}, PlatformType::PLATFORM});
        x += pw + int(winW * 0.01f);
    }
}

string Game::GetButtonText()
{
    if (currentForm == LOGIN)
        return "Switch to Register";
    else
        return "Switch to Login";
}

void Game::Reset()
{
    monsterTimer = 0;
    state = GameState::PLAYING;
    player.velocityY = 0;
    player.walking = false;
    player.jumping = false;
    player.x = winW / 2.f;
    player.y = winH / 2.f;
    monster->velocityY = 0;
    monster->walking = false;
    monster->jumping = false;
    monster->x = winW + 500.f;
    monster->y = winH / 2.f;
    player.score = 0;
    CreatePlatforms();
}

void Game::Run()
{
    while (!WindowShouldClose() && !exitGame)
    {
        float dt = GetFrameTime();
        Update(dt);
        Draw();
    }
    Cleanup();
}

void Game::Update(float dt)
{
    toast.Update(GetFrameTime());
    Vector2 mp = GetMousePosition();
    switch (state)
    {
    case GameState::MENU:
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mp, btnStart))
                state = GameState::LOGIN;
            else if (CheckCollisionPointRec(mp, btnQuit))
                exitGame = true;
        }
        break;

    case GameState::LEVEL_SELECTION:
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mp, btnLevel1)) {
                SwitchLevel(Levels::LEVEL1);
                state = GameState::PLAYING;
            }
            else if (CheckCollisionPointRec(mp, btnLevel2)) {
                SwitchLevel(Levels::LEVEL2);
                state = GameState::PLAYING;
            }
            else if (CheckCollisionPointRec(mp, btnLevel3)) {
                SwitchLevel(Levels::LEVEL3);
                state = GameState::PLAYING;
            }
        }
    break;

    case GameState::LOGIN:
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mp, usernameField))
                currentInput = InputField::USERNAME;
            else if (CheckCollisionPointRec(mp, passwordField))
                currentInput = InputField::PASSWORD;
            else if (currentForm == REGISTER && CheckCollisionPointRec(mp, confirmPasswordField))
                currentInput = InputField::CONFIRM_PASSWORD;
            else
                currentInput = InputField::NONE;
        }

        int key = GetCharPressed();
        while (key > 0)
        {
            if (currentInput == InputField::USERNAME && username.length() < 20)
                username += (char)key;
            else if (currentInput == InputField::PASSWORD && password.length() < 20)
                password += (char)key;
            else if (currentInput == InputField::CONFIRM_PASSWORD && confirmPassword.length() < 20)
                confirmPassword += (char)key;
            key = GetCharPressed();
        }

        // Backspace support
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if (currentInput == InputField::USERNAME && !username.empty())
                username.pop_back();
            else if (currentInput == InputField::PASSWORD && !password.empty())
                password.pop_back();
            else if (currentInput == InputField::CONFIRM_PASSWORD && !confirmPassword.empty())
                confirmPassword.pop_back();
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            if (currentForm == REGISTER)
            {
                user.username = username;
                user.password = password;
                user.confirmPassword = confirmPassword;
                if (user.ValidateRegistration())
                {
                    user.SaveToFile();
                    toast.Show("Registration Successful!", 3.0f);
                    currentForm = LOGIN;
                }
                else
                {
                    toast.Show("Passwords do not match!", 3.0f);
                }
            }
            else if (currentForm == LOGIN)
            {
                user.username = username;
                user.password = password;
                if (user.LoadFromFile(username))
                {
                    if (user.ValidateLogin(username, password))
                    {
                        toast.Show("Login Successful!", 3.0f);
                        state = GameState::LEVEL_SELECTION;
                    }
                    else
                    {
                        toast.Show("Invalid Username or Password!", 3.0f);
                    }
                }
                else
                {
                    toast.Show("User not found!", 3.0f); 
                }
            }
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mp, loginButton))
            {
                currentForm = (currentForm == LOGIN) ? REGISTER : LOGIN;
                username = password = confirmPassword = "";
            }
        }
    }

    break;

    case GameState::PLAYING:
            // camera follow
            if (player.x > winW * 0.1f)
                camera.offset.x = -(player.x - winW * 0.1f);
            else if (player.x < winW * 0.05f)
                camera.offset.x = -(player.x - winW * 0.05f);
            camera.offset.x = clampf(camera.offset.x, -(worldW - winW), 0.f);
            camera.offset.y = 0.f;

            // update characters
            player.Update(dt, platforms, winW, worldW);
            score = player.score;
            monster->walking = true;
            monster->direction = (player.x < monster->x ? -1 : 1);
            monster->Update(dt, platforms, winW, worldW);

            // direct body collision → KNOCKBACK monster
            {
                Rectangle pr = {player.x, player.y, float(player.width), float(player.height)};
                Rectangle mr = {monster->x, monster->y, float(monster->width), float(monster->height)};
                if (CheckCollisionRecs(pr, mr))
                {
                    monster->velocityY = -monster->jumpStrength * SCALE_FACTOR;
                    monster->jumping = true;
                    monster->direction *= -1;
                    monster->x += monster->direction * (monster->width * 0.5f);
                }
            }

            if(currentLevel == Levels::LEVEL2)
            {
                IceMonster *iceMonster = dynamic_cast<IceMonster *>(monster);
                if (iceMonster)
                {
                    for (auto &iceFire : iceMonster->iceFires)
                    {
                        iceFire.Update(dt); 
                    }
                }

                monsterTimer += dt;
                if (monsterTimer >= MONSTER_SHOOT_INTERVAL)
                {
                    iceMonster->Shoot(); 
                    monsterTimer = 0.f;
                }

                for (auto &b : iceMonster->iceFires)
                {
                    if (CheckCollisionCircleRec(b.position, b.size, {player.x, player.y, float(player.width), float(player.height)}))
                    {
                        PlaySound(death);             
                        state = GameState::GAME_OVER; 
                    }
                }
            }
            else if (currentLevel == Levels::LEVEL3)
            {
                FireMonster *fireMonster = dynamic_cast<FireMonster *>(monster);
                if (fireMonster)
                {
                    for (auto &FFire : fireMonster->FFires)
                    {
                        FFire.Update(dt);
                    }
                }

                monsterTimer += dt;
                if (monsterTimer >= MONSTER_SHOOT_INTERVAL)
                {
                    fireMonster->Shoot();
                    monsterTimer = 0.f;
                }

                for (auto &b : fireMonster->FFires)
                {
                    if (CheckCollisionCircleRec(b.position, b.size, {player.x, player.y, float(player.width), float(player.height)}))
                    {
                        PlaySound(death);
                        state = GameState::GAME_OVER;
                    }
                }
            }
            else{

                // monster shooting
                monsterTimer += dt;
                if (monsterTimer >= MONSTER_SHOOT_INTERVAL)
                {
                    monster->Shoot();
                    monsterTimer = 0.f;
                }

                // bullet collision → Game Over
                for (auto &b : monster->bullets)
                {
                    if (CheckCollisionCircleRec(b.position, b.size, {player.x, player.y, float(player.width), float(player.height)}))
                    {
                        PlaySound(death);
                        state = GameState::GAME_OVER;
                    }
                }
            }
        break;

    case GameState::GAME_OVER:
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mp, btnRestart))
                Reset();
            else if (CheckCollisionPointRec(mp, btnQuit))
                exitGame = true;
        }
        break;
    }
}

void Game::Draw()
{
    toast.Draw();
    BeginDrawing();
    ClearBackground(WHITE);
    switch (state)
    {
    case GameState::MENU:
        DrawText("Pixel Escape", winW / 2 - 130, winH / 2 - 90, 40, DARKBLUE);
        DrawRectangleRec(btnStart, DARKGREEN);
        DrawText("Start Game", int(btnStart.x + 30), int(btnStart.y + 15), 20, WHITE);
        DrawRectangleRec(btnQuit, MAROON);
        DrawText("Quit", int(btnQuit.x + 70), int(btnQuit.y + 15), 20, WHITE);
        break;

    case GameState::LOGIN:
    {
        float formWidth = 320;
        float formHeight = 350;
        float offsetX = winW / 2 - formWidth / 2;
        float offsetY = winH / 2 - formHeight / 2;

        if (currentForm == LOGIN)
            DrawText("Login", offsetX + (formWidth / 2) - MeasureText("Login", 30) / 2, offsetY - 40, 30, DARKBLUE);
        else
            DrawText("Register", offsetX + (formWidth / 2) - MeasureText("Register", 30) / 2, offsetY - 40, 30, DARKBLUE);

            float fieldOffsetY = offsetY + 40; 
            float fieldHeight = 30;
            float verticalSpacing = 20;
    
            usernameField = {offsetX + 20, fieldOffsetY, 200, fieldHeight};
            DrawText("Username:", offsetX + 20, fieldOffsetY - 20, 20, DARKGRAY);
            DrawRectangleLinesEx(usernameField, 2, DARKGRAY);
            DrawText(username.c_str(), usernameField.x + 5, usernameField.y + 5, 20, BLACK);
    
            fieldOffsetY += fieldHeight + verticalSpacing;
            passwordField = {offsetX + 20, fieldOffsetY, 200, fieldHeight};
            DrawText("Password:", offsetX + 20, fieldOffsetY - 20, 20, DARKGRAY);
            DrawRectangleLinesEx(passwordField, 2, DARKGRAY);
            DrawText(string(password.length(), '*').c_str(), passwordField.x + 5, passwordField.y + 5, 20, BLACK);
    
            if (currentForm == REGISTER)
            {
                fieldOffsetY += fieldHeight + verticalSpacing;
                confirmPasswordField = {offsetX + 20, fieldOffsetY, 200, fieldHeight};
                DrawText("Confirm Password:", offsetX + 20, fieldOffsetY - 20, 20, DARKGRAY);
                DrawRectangleLinesEx(confirmPasswordField, 2, DARKGRAY);
                DrawText(string(confirmPassword.length(), '*').c_str(), confirmPasswordField.x + 5, confirmPasswordField.y + 5, 20, BLACK);
            }

        float switchButtonWidth = MeasureText(GetButtonText().c_str(), 20) + 40;
        float switchButtonX = offsetX + (formWidth / 2) - (switchButtonWidth / 2);
        loginButton = {switchButtonX, offsetY + 180 + (currentForm == REGISTER ? 60 : 0), switchButtonWidth, 40};

        DrawRectangleRec(loginButton, BLUE);
        DrawText(GetButtonText().c_str(), loginButton.x + (switchButtonWidth - MeasureText(GetButtonText().c_str(), 20)) / 2, loginButton.y + 10, 20, WHITE);
    }

        break;

    case GameState::LEVEL_SELECTION:
        DrawText("Choose Level You want to play : ", winW / 2 - 320, winH / 2 - 90, 40, DARKBLUE);
        DrawRectangleRec(btnLevel1, DARKGREEN);
        DrawText("Forest", int(btnLevel1.x + 30), int(btnLevel1.y + 15), 20, WHITE);
        DrawRectangleRec(btnLevel2, YELLOW);
        DrawText("Frost", int(btnLevel2.x + 30), int(btnLevel2.y + 15), 20, WHITE);
        DrawRectangleRec(btnLevel3, RED);
        DrawText("Flame", int(btnLevel3.x + 30), int(btnLevel3.y + 15), 20, WHITE);
        break;

    case GameState::PLAYING:
        BeginMode2D(camera);
        {
            float bx = -camera.offset.x;
            bx -= bx * bgRatio * -0;
            DrawTexture(background, int(bx), 0, WHITE);
        }
        for (size_t i = 0; i < platforms.size(); ++i)
        {
            auto &p = platforms[i];
            if (p.type == PlatformType::FLOOR)
            {
                DrawTexture(floorTex, int(p.rec.x), int(p.rec.y - 33), WHITE);
            }
            else
            {
                bool f = (i % 2 == 0);
                Texture2D &t = f ? plat1Tex : plat2Tex;
                int wht = f ? plat1White : plat2White;
                DrawTexture(t, int(p.rec.x - 10), int(p.rec.y - wht), WHITE);
            }
        }
        player.Draw(camera);
        monster->Draw(camera);
        EndMode2D();
        DrawText(TextFormat("Score: %d", score), 100, 100, 30, BLACK);
        break;

    case GameState::GAME_OVER:
        ClearBackground(RED);
        DrawText("Game Over", winW / 2 - 100, winH / 2 - 120, 40, WHITE);
        DrawText(TextFormat("Final Score: %d", score), winW / 2 - 110, winH / 2 - 70, 30, DARKGRAY);
        DrawRectangleRec(btnRestart, DARKGREEN);
        DrawText("Restart", int(btnRestart.x + 40), int(btnRestart.y + 20), 20, WHITE);
        DrawRectangleRec(btnQuit, MAROON);
        DrawText("Quit", int(btnQuit.x + 70), int(btnQuit.y + 20), 20, WHITE);
        break;
    }
    EndDrawing();
}

void Game::Cleanup() {
    player.Unload();
    if (monster) {
        monster->Unload();
        delete monster;
    }
    UnloadTexture(background);
    UnloadTexture(floorTex);
    UnloadTexture(plat1Tex);
    UnloadTexture(plat2Tex);
    UnloadSound(jump);
    UnloadSound(death);
    CloseAudioDevice();
    CloseWindow();
}
