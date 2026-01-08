void Matsuno::start() {

    // Random seed
    srand(time(NULL));

    // Disable logs
    SetTraceLogLevel(LOG_NONE);

    // Launch window
    InitWindow(matsuno.windowWidth, matsuno.windowHeight, matsuno.windowTitle);
    Image icon = LoadImage(matsuno.windowIcon);
    SetWindowIcon(icon);
    SetTargetFPS(matsuno.fpsTarget);

    // Set default gamestate
    GameState GameState = sLogos;

    // Main loop
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        switch (GameState) {
            case sLogos: {
                matsuno.drawText(
                    "Matsuno",
                    0,
                    0,
                    matsuno.fontSize,
                    LIGHTGRAY,
                    hCenter,
                    vMiddle
                );

                drawSquares();

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
    }

    // Shutdown
    CloseWindow();

}