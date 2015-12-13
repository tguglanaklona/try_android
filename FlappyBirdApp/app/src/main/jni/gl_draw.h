//
// SceneActionPaint: uses Panorama objects to draw in DrawGLScene()
//                   Arrange them at [-1; M_X]x[-1; 1] grid.
//
// Consists of controlling methods
// and those which calls OpenGL SE painter
//

#ifndef FLAPPYBIRDAPP_GL_DRAW_H
#define FLAPPYBIRDAPP_GL_DRAW_H
#pragma once

#ifndef FLAPPYBIRDAPP_PANORAMA_H
#include "panorama.h"
#endif

class SceneActionPaint : public Panorama, public Scale{
public:
    SceneActionPaint();
    void newScene();

    void drawBarriers();
    bool drawBird();

    void onTouch(GLfloat, GLfloat);

public:
    GLfloat mBarriersVelocity; // units/frame
    GLfloat mBirdVelocity;     // units/frame
};

#endif //FLAPPYBIRDAPP_GL_DRAW_H
