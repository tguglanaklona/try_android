//
// OpenGL ES 2.0 code
//

#include <jni.h>
#include "headers.h" //GLES2

#include "gl_code.h"

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

/*
static const char gVertexShader[] =
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

static const char gFragmentShader[] = 
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";

GLuint    gProgram;
GLuint    gvPositionHandle;
*/

SceneControl scene;

int       gEndTimer = 0;
const int gEndTime = 100;

bool setupGraphics(int w, int h) {// implements onSurfaceChanged
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    GLfloat gViewportScale = (GLfloat)w/(GLfloat)h;
    scene.setScale(gViewportScale > 1.0f ? gViewportScale : 1.0f/gViewportScale);
    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    return true;
}

void DrawGLScene(){// Here's Where We Do All The Drawing

    if (!gEndTimer){
        scene.drawBarriers();
        bool theEnd = scene.drawBird();

        if (theEnd) {
            //recreate our opengl scene
            scene.newScene();
            gEndTimer++;
            return;
        }
    }
    else{
        gEndTimer++;
        if (gEndTimer >= gEndTime) gEndTimer = 0;
    }

    /*
     * test triangle
     *
    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");
     */
}

void onTouch(float x, float y){
    if (!gEndTimer) {
        scene.onTouch(x, y);
    }
    else{
        gEndTimer = 0;
    }
}

void renderFrame() {// implements onDrawFrame
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    DrawGLScene();
}

extern "C" {
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_touch(JNIEnv * env, jobject obj, jfloat x, jfloat y);
};

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height) // onSurfaceChanged
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj) // onDrawFrame
{
    renderFrame();
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_touch(JNIEnv * env, jobject obj, jfloat x, jfloat y) //onTouchEvent
{
    onTouch(x, y);
}
