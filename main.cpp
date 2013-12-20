#include "FiveCross.h"

FiveCross *g_fiveCross = NULL;
bool      *g_buttons = NULL;

int main(void)
{
    g_fiveCross = new FiveCross();

    int r = g_fiveCross->Init();
    if (r) {
        g_fiveCross->Exit();
        FC_DELETE(g_fiveCross);
        FC_ERROR("Fehler beim Initialisieren des Spiels", FC_ERR);
    }

    if (g_fiveCross->Run()) {
        g_fiveCross->Exit();
        FC_DELETE(g_fiveCross);
        FC_ERROR("Fehler im Spiel!", FC_ERR;
    }

    g_fiveCross->Exit();
    FC_DELETE(g_fiveCross);

    return 0;
}
