//
// gl_draw: uses Panorama objects to draw in DrawGLScene()
//

#ifndef FLAPPYBIRDAPP_GL_DRAW_H
#define FLAPPYBIRDAPP_GL_DRAW_H
#pragma once

#ifndef FLAPPYBIRDAPP_PANORAMA_H
#include "panorama.h"
#endif

#include <android/log.h>
#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

class gl_draw {
public:
    gl_draw(Panorama* pgScene, GLuint* pgvPositionHandle);
    ~gl_draw(){};
    GLuint mvPositionHandle();

    void drawBarriers();

private:
    Panorama* mpScene;
    GLuint* mpvPositionHandle;

public:
    GLfloat mBarriersVelocity; // units/frame
    GLfloat mBirdVelocity;     // units/frame

    GLfloat mGlobalVelocity;   // units/frame
};


#endif //FLAPPYBIRDAPP_GL_DRAW_H
