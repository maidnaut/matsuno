#pragma once

typedef enum {
    sLogos,
    sTitle,
    sCutscene,
    sMain,
    sMenu,
    sPause,
    sDeath
} GameStates;

typedef enum {
    hLeft, hCenter, hRight,
    vTop, vMiddle, vBottom
} tAlign;

typedef enum {
    tTop, tMiddle, tBottom
} textboxPosition;

// Matsuno System
struct MatsunoSystem {
    int vMajor = 0;
    int vMinor = 1;
    std::string title = "matsuno";
    std::string _windowTitle = title + " " + std::to_string(vMajor) + "." + std::to_string(vMinor);
    const char* windowTitle = _windowTitle.c_str(); // stupid bullshit to get the concatenated string back down to c

    const char* windowIcon = "res/icon.png";

    bool ShouldExit;

    GameStates GameState = sLogos;

    void init();
    void update();
    void run();
};

//Matsuno Graphics
struct MatsunoGraphics {
    int windowWidth = 1280;
    int windowHeight = 720;
    int minimumWidth = 1024;
    int minimumHeight = 576;

    int vsync = 1;
    int fpsTarget = 60;
    int fontSize = 48;
    int padding = 16;

    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;
    int middleLeft = centerX / 2;
    int middleRight = centerX * 1.5;

    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;

    Uint32 windowFlags = SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE;

    struct FPS {
        Uint32 frameDelay;
        Uint32 frameStart;
        Uint32 frameTime;

        uint64_t now = 0;
        double deltaTime = 0.0;

        double deltaFreq = (double)SDL_GetPerformanceFrequency();
        uint64_t lastCounter = SDL_GetPerformanceCounter();
        
        FPS(int fpsTarget) {
            frameDelay = fpsTarget > 0 ? 1000 / fpsTarget : 0;
        }
    } fps{fpsTarget};

    bool minimized = false;

    const char* font_path = "res/Roboto-Light.ttf";
    TTF_Font *font = nullptr;

    void drawSprite(SDL_Texture* image, float x, float y, float width, float height, float fade);
    void drawSquares();
    void drawText(const char *str, int x, int y, SDL_Color color, tAlign hAlign, tAlign vAlign);
    SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
};

struct MatsunoColors {

    // Stole these values from raylib cus i like them
    SDL_Color white      {255, 255, 255, 255};
    SDL_Color black      {0, 0, 0, 255};
    SDL_Color lightgray  {200, 200, 200, 255};
    SDL_Color gray       {130, 130, 130, 255};
    SDL_Color darkgray   {80, 80, 80, 255};

    SDL_Color yellow     {253, 249, 0, 255};
    SDL_Color gold       {255, 203, 0, 255};
    SDL_Color orange     {255, 161, 0, 255};
    SDL_Color pink       {255, 109, 194, 255};
    SDL_Color red        {230, 41, 55, 255};
    SDL_Color maroon     {190, 33, 55, 255};
    SDL_Color green      {0, 228, 48, 255};
    SDL_Color lime       {0, 158, 47, 255};
    SDL_Color darkgreen  {0, 117, 44, 255};
    SDL_Color skyblue    {102, 191, 255, 255};
    SDL_Color blue       {0, 121, 241, 255};
    SDL_Color darkblue   {0, 82, 172, 255};
    SDL_Color magenta    {255, 0, 255, 255};
    SDL_Color purple     {200, 122, 255, 255};
    SDL_Color violet     {135, 60, 190, 255};
    SDL_Color darkpurple {112, 31, 126, 255};
    SDL_Color beige      {211, 176, 131, 255};
    SDL_Color brown      {127, 106, 79, 255};
    SDL_Color darkbrown  {76, 63, 47, 255};
};

// Matsuno Audio
struct MatsunoAudio {
    // Todo
};

// Matsuno Input
struct MatsunoInput {
    // Todo
};

// Matsuno Assets
struct MatsunoAssets {
    // Todo
};

inline MatsunoSystem sys;
inline MatsunoGraphics gfx;
inline MatsunoColors colors;
inline MatsunoAudio audio;
inline MatsunoInput input;
inline MatsunoAssets assets;