//
// geometry_render.cpp
//

#include "geometry_render.h"

GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                         shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint gcreateProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

const char FlappyPaint::vertexShaderCode[] =
        "attribute vec4 vPosition;\n" \
        "void main() {\n" \
        "  gl_Position = vPosition;\n" \
        "}\n";

const char FlappyPaint::fragmentShaderCode[] =
        "precision mediump float;\n" \
        "void main() {\n" \
        "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n" \
        "}\n";

void FlappyPaint::paintTheBird(const Scale* pScale)/*const*/{
    glUseProgram(mProgram);
    checkGlError("glUseProgram");

    unsigned int n = 0;
    GLfloat* pV = glDrawVertices(1, &n);

    GLuint vPositionHandle = glGetAttribLocation(mProgram, "vPosition");
    checkGlError("glGetAttribLocation");

    glVertexAttribPointer(vPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, pScale->paintScaling(pV, n));
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(vPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLE_FAN, 0, n);
    checkGlError("glDrawArrays");
}

const char BarrierPaint::vertexShaderCode[] =
        "attribute vec4 vPosition;\n"
        "void main() {\n"
        "  gl_Position = vPosition;\n"
        "}\n";

const char BarrierPaint::fragmentShaderCode[] =
        "precision mediump float;\n"
        "void main() {\n"
        "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n" ////rand
        "}\n";

GLuint BarrierPaint::createProgram(){
    //LOGI("BarrierPaint :: createProgram");
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

/*void BarrierPaint::deleteProgram(){
    if (mProgram!=0) {
        glDeleteProgram(mProgram);
        checkGlError("glDeleteProgram");
        mProgram = 0;
    }
}*/

void BarrierPaint::paintBarrier(const Scale* pScale)/*const*/{
    glUseProgram(mProgram);
    checkGlError("glUseProgram");

    GLfloat* pV = glDrawVertices(1);

    GLint vPositionHandle = glGetAttribLocation(mProgram, "vPosition");
    checkGlError("glGetAttribLocation");

    glVertexAttribPointer(vPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, pScale->paintScaling(pV, 4));
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(vPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    checkGlError("glDrawArrays");
}
