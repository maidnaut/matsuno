#ifndef SOURCE_H
#define SOURCE_H

typedef enum {
    sLogos,
    sTitle,
    sCutscene,
    sMain,
    sMenu,
    sPause,
    sDeath
} GameState;

typedef enum {
    hLeft, hCenter, hRight,
    vTop, vMiddle, vBottom
} tAlign;

// Matsuno
struct Matsuno {
    const char* windowIcon = "res/icon.png";
    int windowWidth = 1280;
    int windowHeight = 720;
    int vMajor = 0;
    int vMinor = 1;

    std::string title = "matsuno";
    std::string _windowTitle = title + " " + std::to_string(vMajor) + "." + std::to_string(vMinor);
    const char* windowTitle = _windowTitle.c_str(); // stupid bullshit to get the concatenated string back down to c

    int vsync = 1;
    int fpsTarget = 10;
    int fontSize = 30;
    int padding = 16;

    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;
    int middleLeft = centerX / 2;
    int middleRight = centerX * 1.5;

    void start();
    void drawText(const char *str, int x, int y, int size, Color color, tAlign hAlign, tAlign vAlign);
};
inline Matsuno matsuno; // matsuno matsuno matsuno matsuno

#endif