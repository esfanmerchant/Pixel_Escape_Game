#include "./includes/Toast.h"

Toast::Toast() : message(""), displayTime(3.0f), timeElapsed(0.0f) {}

void Toast::Show(const std::string &msg, float duration)
{
    message = msg;
    displayTime = duration;
    timeElapsed = 0.0f;
    alpha = 0.0f;
}

void Toast::Update(float dt)
{
    if (!IsVisible())
        return;

    if (timeElapsed < displayTime)
    {
        timeElapsed += dt;
        float fadeDuration = 0.5f;
        if (timeElapsed < fadeDuration)
        {
            // Fade in
            alpha = timeElapsed / fadeDuration;
        }
        else if (timeElapsed > displayTime - fadeDuration)
        {
            // Fade out
            alpha = 1.0f - ((timeElapsed - (displayTime - fadeDuration)) / fadeDuration);
        }
        else
        {
            // Fully visible
            alpha = 1.0f;
        }
    }
}

void Toast::Draw()
{
    if (!IsVisible())
        return;

    int fontSize = 20;
    int padding = 20;
    int textWidth = MeasureText(message.c_str(), fontSize);
    int rectWidth = textWidth + padding * 2;
    int rectHeight = 50;

    toastRect = {
        (float)(GetScreenWidth() - rectWidth - 20), // Top-right with 20px margin
        20.0f,
        (float)rectWidth,
        (float)rectHeight};

    Color bgColor = Fade(DARKGRAY, alpha);
    Color textColor = Fade(WHITE, alpha);

    DrawRectangleRec(toastRect, bgColor);
    DrawText(message.c_str(), (int)(toastRect.x + padding), (int)(toastRect.y + (rectHeight - fontSize) / 2), fontSize, textColor);
}

bool Toast::IsVisible()
{
    return timeElapsed < displayTime;
}
