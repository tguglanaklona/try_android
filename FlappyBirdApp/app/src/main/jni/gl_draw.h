//
// gl_draw: uses Panorama objects to draw in DrawGLScene()
//

#ifndef FLAPPYBIRDAPP_GL_DRAW_H
#define FLAPPYBIRDAPP_GL_DRAW_H
#pragma once

#ifndef FLAPPYBIRDAPP_PANORAMA_H
#include "panorama.h"
#endif

class gl_draw {
public:
    gl_draw(Panorama* pgScene, GLuint* pgvPositionHandle);
    ~gl_draw(){};
    GLuint mvPositionHandle();

    void drawBarriers();
    bool drawBird();

    void onTouch(GLfloat, GLfloat);

private:
    Panorama* mpScene;
    GLuint* mpvPositionHandle;

public:
    GLfloat mBarriersVelocity; // units/frame
    GLfloat mBirdVelocity;     // units/frame

    GLfloat mGlobalVelocity;   // units/frame
};


#endif //FLAPPYBIRDAPP_GL_DRAW_H
