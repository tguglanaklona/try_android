//
// GlDraw: uses Panorama objects to draw in DrawGLScene()
//         Arrange them at [-1; M_X]x[-1; 1] grid.
//
// Consists of controlling methods
// and those which calls paint by OpenGL SE
//

#ifndef FLAPPYBIRDAPP_GL_DRAW_H
#define FLAPPYBIRDAPP_GL_DRAW_H
#pragma once

#ifndef FLAPPYBIRDAPP_PANORAMA_H
#include "panorama.h"
#endif

class GlDraw {
public:
    GlDraw(GLuint* pgvPositionHandle);
    ~GlDraw();
    GLuint mvPositionHandle() const;
    void setScale(GLfloat scale);
    void newPanorama();

    void drawBarriers();
    bool drawBird();

    void paintBarrier(BarrierRect*) const;
    void paintTheBird(FlappyCircle* pTheBird = NULL) const;
    const GLfloat* paintScaling(GLfloat*, unsigned int) const;

    void onTouch(GLfloat, GLfloat);

private:
    Panorama* mpScene;
    GLuint* mpvPositionHandle;
    GLfloat M_X;

    GlDraw(const GlDraw&);
    void operator=(const GlDraw&);

public:
    GLfloat mBarriersVelocity; // units/frame
    GLfloat mBirdVelocity;     // units/frame

    GLfloat mGlobalVelocity;   // units/frame
};


#endif //FLAPPYBIRDAPP_GL_DRAW_H
