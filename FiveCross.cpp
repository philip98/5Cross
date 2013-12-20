#include "FiveCross.h"

int FiveCross::SetGameState(GameState newGameState) {
    switch (gameState) {
    case GS_INTRO:
        intro->Exit();
        break;

    case GS_MAIN_MENU:
        mainMenu->Exit();
        break;

    case GS_GAME:
        game->Exit();
        break;
    }

    time = 0.0f;

    int r = FC_OK;

    gameState = newGameState;
    switch (gameState) {
    case GS_INTRO:
        r = intro->Init();
        break;

    case GS_MAIN_MENU:
        r = mainMenu->Init();
        break;

    case GS_GAME:
        r = game->Init();
        break;
    }

    if (r)
        FC_ERROR("Fehler beim Laden des Spielzustands", FC_ERR);

    return FC_OK;
}

int FiveCross::Load() {
    //Initialisieren bzw. Laden der einzelnen Komponenten

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("5Cross");
    glutKeyboardFunc(KeyPressed);
    glutKeyboardUpFunc(KeyUp);

    buttons = new bool[256];
}

int FiveCross::Unload() {
    FC_DELETE(buttons);
}

int FiveCross::Init() {
    ZeroMemory(this, sizeof(FiveCross));

    glutInit(NULL, NULL);

    if (Load())
        FC_ERROR("Fehler beim Laden des Spiels!", FC_ERR);

    intro    = new Intro;
    mainMenu = new mainMenu;
    game     = new Game;

    SetGameState(GS_INTRO);
    return FC_OK;
}

int FiveCross::Exit() {
    SetGameState(GS_NONE);
    FC_DELETE(intro);
    FC_DELETE(mainMenu);
    FC_DELETE(game);
}

int FiveCross::Move(float t) {
    int r = FC_OK;

    switch (gameState) {
    case GS_INTRO:
        r = intro->Move(t);
        break;

    case GS_MAIN_MENU:
        r = mainMenu->Move(t);
        break;

    case GS_GAME:
        r = game->Move(t);
        break;
    }

    if (r)
        FC_ERROR("Fehler beim Bewegen des Spielzustands", FC_ERR);

    time += t;

    return FC_OK;
}

int FiveCross::Render(float t) {
    int r = FC_OK;

    switch (gameState) {
    case GS_INTRO:
        r = intro->Render(t);
        break;

    case GS_MAIN_MENU:
        r = mainMenu->Render(t);
        break;

    case GS_GAME:
        r = game->Render(t);
        break;
    }

    if (r)
        FC_ERROR("Fehler beim Rendern des Spielzustands", FC_ERR);

    return FC_OK;
}

int FiveCross::Run() {
    MSG msg;
    long long int startTime;
    long long int endTime;
    double t;
    bool quit = false;

    ZeroMemory(&msg, sizeof(MSG));

    t = 0.0;

    while (!quit) {
        startTime = (long long int)GetTickCount();
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                quit = true;

            if (Render((float)t) == FC_STOP)
                break;

            if (t == 0.0) {
                endTime = (long long int)GetTickCount();
                if (endTime == startTime)
                    t = 0.0001;
                else
                    t = (float)(endTime - startTime) / 1000;
            }

            if (Move((float)t) == FC_STOP)
                break;

            endTime = (long long int)GetTickCount();
            if (endTime == startTime)
                t = 0.0001;
            else
                t = (float)(endTime - startTime) / 1000;
        }
    }

    return FC_OK;
}
