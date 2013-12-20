#ifndef FIVECROSS_H_INCLUDED
#define FIVECROSS_H_INCLUDED

#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define FC_OK 0
#define FC_ERR 1
#define FC_STOP 2
#define FC_ERROR(m, r) { MessageBox(NULL, (m), "Fehler!", MB_OK); return r;}
#define FC_DELETE(p) { delete (p); (p) = NULL; }
#define FC_DELETE_ARRAY(a) { delete[] (a); (a) = NULL; }

enum class GameState {
    GS_NONE,
    GS_INTRO,
    GS_MAIN_MENU,
    GS_GAME
};

class FiveCross {
public:
    Intro    *intro;      // Frau Vogtmann wird mich umbringen :D
    MainMenu *mainMenu;
    Game     *game;
    GameState gameState;
    float     time;

    int SetGameState(GameState newGameState);
    int Load();
    int Unload();
    int Init();
    int Exit():
    int Render(float t);
    int Move(float t);
    int Run();

    void KeyPressed(unsigned char key, int x, int y);
    void KeyUp(unsigned char key, int x, int y);
    void MouseMoved(int x, int y);
};

extern FiveCross *g_fiveCross;
extern bool *g_buttons;
#endif // FIVECROSS_H_INCLUDED
