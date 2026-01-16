#pragma once

void MatsunoSystem::init() {

    // Random seed
    srand((unsigned)time(NULL));

    // SDL Init
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init failed: %s", SDL_GetError());
        SDL_Quit();
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow(
        sys.windowTitle,
        gfx.windowWidth,
        gfx.windowHeight,
        SDL_WINDOW_VULKAN |
        SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_MOUSE_CAPTURE
    );
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s", SDL_GetError());
        SDL_Quit();
    }
    gfx.window = window; // pass it into the globals so matsuno can see it

    // Set the icon
    SDL_Surface *icon = IMG_Load("res/icon.png");
    if (!icon) {
        SDL_Log("IMG_Load failed: %s", SDL_GetError());
        SDL_Quit();
    }

    SDL_SetWindowIcon(window, icon);
    SDL_DestroySurface(icon);

    // Create the renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(gfx.window, nullptr);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(gfx.window);
        SDL_Quit();
    }
    gfx.renderer = renderer; // pass it to matsuno

    // Hinting
    SDL_SetWindowMinimumSize(gfx.window, 1024, 576);  
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, gfx.vsync ? "1" : "0");

    // Load font
    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_Init failed: %s", SDL_GetError());
        SDL_Quit();
    }
    gfx.font = TTF_OpenFont(gfx.font_path, gfx.fontSize);
    if (!gfx.font) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_OpenFont failed: %s", SDL_GetError());
        SDL_Quit();
    }

    // ok we good
    sys.ShouldExit = false;
}

void MatsunoSystem::update() {

    // Handle SDL events
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        // Escape
        if (e.type == SDL_EVENT_QUIT ||
            e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
            sys.ShouldExit = true;
            break;
        } else if (e.type == SDL_EVENT_KEY_DOWN) {
            if (e.key.scancode == SDL_SCANCODE_ESCAPE) {
                sys.ShouldExit = true;
                break;
            }
        }
        
        // Resize
        if (e.type == SDL_EVENT_WINDOW_RESIZED) {
            SDL_GetWindowSize(gfx.window, &gfx.windowWidth, &gfx.windowHeight);
            gfx.centerX = gfx.windowWidth / 2;
            gfx.centerY = gfx.windowHeight / 2;
        }
    }

    // delta time stuff
    gfx.fps.deltaTime = (SDL_GetPerformanceCounter() - gfx.fps.lastCounter) / gfx.fps.deltaFreq;
    gfx.fps.lastCounter = SDL_GetPerformanceCounter();
    if ((gfx.fps.frameTime = SDL_GetTicks() - gfx.fps.frameStart) < gfx.fps.frameDelay) {
        SDL_Delay(gfx.fps.frameDelay - gfx.fps.frameTime);
    }

    // tick coroutines
    Coroutines.update();

    // update the renderer
    SDL_RenderPresent(gfx.renderer);

}

void MatsunoSystem::run() {

    sys.init();

    SDL_Texture* icon = gfx.loadTexture(gfx.renderer, "res/black_lace.png");

    while (!sys.ShouldExit) {

        // Should put an isMinimized check here to skip background rendering, but it's broken on wayland

        SDL_RenderClear(gfx.renderer);
        SDL_SetRenderDrawColor(gfx.renderer, 0, 0, 0, 255);

        //gfx.drawSquares();
        //gfx.drawText("Matsuno", 0, 0, colors.lightgray, hCenter, vMiddle);
        static float fade = 0.0f;

        float scaleX = gfx.windowWidth  / 900.0f;
        float scaleY = gfx.windowHeight / 180.0f;
        float scale  = glm_min(scaleX, scaleY) * 0.5f;

        int img_width  = int(900 * scale);
        int img_height = int(180 * scale);

        Coroutines.start("logos",
            repeat(1.0, {}),
            repeat(2.5, {
                fade += gfx.fps.deltaTime / 2.5f;
                if (fade > 1.0f) fade = 1.0f;
                gfx.drawSprite(icon, gfx.centerX, gfx.centerY, img_width, img_height, fade);
            }),
            repeat(4.0, {
                gfx.drawSprite(icon, gfx.centerX, gfx.centerY, img_width, img_height, fade);
            }),
            repeat(2.5, {
                fade -= gfx.fps.deltaTime / 2.5f;
                if (fade < 0.0f) fade = 0.0f;
                gfx.drawSprite(icon, gfx.centerX, gfx.centerY, img_width, img_height, fade);
            })
        );

        sys.update();

    }

    // Might want to move this into a shutdown() function at some point
    SDL_DestroyRenderer(gfx.renderer);
    SDL_DestroyWindow(gfx.window);
    SDL_Quit();
}
