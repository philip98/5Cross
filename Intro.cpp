#include "Intro.h"
#include "FiveCross.h"

int Intro::Init() {
    if (Load())
        FC_ERROR("Fehler beim Laden des Spielzustands!", FC_ERR);
    return FC_OK;
}

int Intro::Load() {
    title = SOIL_load_OGL_texture("titel.png", SOIL_LOAD_AUTO,
                                  SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS |
                                  SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
                                  SOIL_FLAG_COMPRESS_TO_DXT);
    if (!title)
        FC_ERROR("Fehler beim Laden des Titelbilds!", FC_ERR);

    return FC_OK;
}

int Intro::Exit() {
    Unload();
    return FC_OK;
}

int Intro::Unload() {
    glDeleteTextures(1, &title);

    return FC_OK;
}

int Intro::Render(float t) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();
    glDisable(GL_LIGHTING);

    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, title);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);
    glTextCoord2f(0, 1);
    glVertex3f(0, 100, 0);
    glTexCoord2f(1, 0);
    glVertex3f(100, 0, 0);
    glTexCoord2f(1, 1);
    glVertex3f(100, 100, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
