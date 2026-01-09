void Matsuno::start() {

    // Random seed
    srand(time(NULL));

    // Disable logs
    SetTraceLogLevel(LOG_NONE);

    // Launch window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(matsuno.windowWidth, matsuno.windowHeight, matsuno.windowTitle);
    Image icon = LoadImage(matsuno.windowIcon);
    SetWindowIcon(icon);
    SetTargetFPS(matsuno.fpsTarget);

    // Set default gamestate
    GameState GameState = sLogos;

    // Load logos
    Image logoImg = LoadImage(matsuno.windowIcon);
    Texture2D logo1 = LoadTextureFromImage(logoImg);
    UnloadImage(logoImg);

    // Main loop
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        // Update dimensions if window's been resized
        if (IsWindowResized()) {
            matsuno.windowWidth = GetScreenWidth();
            matsuno.windowHeight = GetScreenHeight();
            matsuno.centerX = matsuno.windowWidth / 2;
            matsuno.centerY = matsuno.windowHeight / 2;
        }

        switch (GameState) {
            case sLogos: {
                // matsuno.drawText(
                //     "Matsuno",
                //     0,
                //     0,
                //     matsuno.fontSize,
                //     LIGHTGRAY,
                //     hCenter,
                //     vMiddle
                // );

                drawSquares();

                static float fade = 0.0f;

                Coroutines.start("logos",
                    STEP(0.0f, {
                        printf("Starting Coroutine and waiting for 10 seconds\n");
                    }),
                    STEP(5.0f, {}), // Wait for 5s
                    STEP(0.0f, {
                        printf("Drawing logo and fading in\n");
                    }),
                    STEP(2.0f, {
                        fade += GetFrameTime() / 2.0f;
                        if (fade > 1.0f) fade = 1.0f;

                        drawRectangleTextured(
                            logo1,
                            {100, 100, 100, 100},
                            {0, 0},
                            0.0f,
                            fade
                        );
                    }),
                    STEP(0.0f, {
                        printf("Holding coroutine for 2 seconds\n");
                    }),
                    STEP(2.0f, {
                        drawRectangleTextured(
                            logo1,
                            {100, 100, 100, 100},
                            {0, 0},
                            0.0f,
                            1.0f
                        );
                    }),
                    STEP(0.0f, {
                        printf("Fading out\n");
                    }),
                    STEP(2.0f, {
                        fade -= GetFrameTime() / 2.0f;
                        if (fade < 0.0f) fade = 0.0f;

                        drawRectangleTextured(
                            logo1,
                            {100, 100, 100, 100},
                            {0, 0},
                            0.0f,
                            fade
                        );
                    }),
                    STEP(0.0f, {
                        printf("Coroutine complete\n");
                    })
                );






                if (IsKeyPressed(KEY_Z)) GameState = sTitle;

                break;
            }

            case sTitle:
                matsuno.drawText(
                    "Title",
                    0,
                    0,
                    matsuno.fontSize,
                    LIGHTGRAY,
                    hCenter,
                    vMiddle
                );

                if (IsKeyPressed(KEY_Z)) GameState = sCutscene;

                break;

            case sCutscene:
                matsuno.drawText(
                    "Cutscene",
                    0,
                    0,
                    matsuno.fontSize,
                    LIGHTGRAY,
                    hCenter,
                    vMiddle
                );

                if (IsKeyPressed(KEY_Z)) GameState = sMain;

                break;

            case sMain:
                matsuno.drawText(
                    "Main",
                    0,
                    0,
                    matsuno.fontSize,
                    LIGHTGRAY,
                    hCenter,
                    vMiddle
                );

                if (IsKeyPressed(KEY_Z)) GameState = sMenu;

                break;

            case sMenu:
                matsuno.drawText(
                    "Menu",
                    0,
                    0,
                    matsuno.fontSize,
                    LIGHTGRAY,
                    hCenter,
                    vMiddle
                );

                if (IsKeyPressed(KEY_Z)) GameState = sPause;

                break;

            case sPause:
                matsuno.drawText(
                    "Pause",
                    0,
                    0,
                    matsuno.fontSize,
                    LIGHTGRAY,
                    hCenter,
                    vMiddle
                );

                if (IsKeyPressed(KEY_Z)) GameState = sDeath;

                break;

            case sDeath:
                matsuno.drawText(
                    "Death",
                    0,
                    0,
                    matsuno.fontSize,
                    LIGHTGRAY,
                    hCenter,
                    vMiddle
                );

                if (IsKeyPressed(KEY_Z)) GameState = sLogos;

                break;
        }

        EndDrawing();

        // Update Coroutines
        Coroutines.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));

    }

    // Shutdown
    CloseWindow();

}