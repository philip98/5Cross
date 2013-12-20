#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED

#include <SOIL.h>
#include <GL/gl.h>

class Intro {
public:
    int Init();
    int Exit();
    int Load();
    int Unload();
    int Move(float t);
    int Render(float t);

    GLuint title;
};

#endif // INTRO_H_INCLUDED
