#ifndef TOAST
#define TOAST

#include <string>
#include <raylib.h>

class Toast
{
private:
    std::string message; 
    float displayTime;   
    float timeElapsed;   
    Rectangle toastRect;
    float alpha = 0.0f; 

public:
    Toast();

    void Show(const std::string &msg, float duration = 3.0f);

    void Update(float dt);

    void Draw();

    bool IsVisible();
};

#endif
