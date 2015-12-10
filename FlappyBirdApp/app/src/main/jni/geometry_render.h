#ifndef FLAPPYBIRDAPP_GEOMETRY_RENDER_H
#define FLAPPYBIRDAPP_GEOMETRY_RENDER_H

#ifndef FLAPPYBIRDAPP_GEOMETRY_H
#include "geometry.h"
#endif

#ifndef FLAPPYBIRDAPP_SCALING_H
#include "scaling.h"
#endif

GLuint loadShader(GLenum shaderType, const char* pSource);
GLuint gcreateProgram(const char* pVertexSource, const char* pFragmentSource);

class FlappyPaint : public FlappyCircle
{
private:
    static const char vertexShaderCode[];
    static const char fragmentShaderCode[];

    GLuint mProgram;
    GLuint createProgram(){
        //LOGI("FlappyPaint :: createProgram");
        mProgram = gcreateProgram(vertexShaderCode, fragmentShaderCode);
        if (!mProgram) {
            LOGE("Could not create program.");
            return false;
        }
        /*GLuint vTestPositionHandle = glGetAttribLocation(mProgram, "vPosition");
        checkGlError("glGetAttribLocation");
        LOGI("glGetAttribLocation(\"vPosition\") = %d\n", vTestPositionHandle);*/
        return true;
    }

public:
    FlappyPaint():FlappyCircle(){ createProgram(); }; //for the consistence
    FlappyPaint(PntR2& globalCenter, GLfloat radius):
            FlappyCircle(globalCenter, radius){ createProgram(); };

    void paintTheBird(const Scale*)/* const*/;
};

class BarrierPaint : public BarrierRect
{
private:
    static const char vertexShaderCode[];
    static const char fragmentShaderCode[];

    GLuint mProgram;
    GLuint createProgram();
    //void   deleteProgram();

public:
    BarrierPaint():BarrierRect(){ createProgram(); }//for the consistence
    BarrierPaint(PntR2& globalBottomRight, GLfloat width, GLfloat height):
            BarrierRect(globalBottomRight, width, height){ createProgram(); }

    void paintBarrier(const Scale*)/*const*/;
};

#endif //FLAPPYBIRDAPP_GEOMETRY_RENDER_H
