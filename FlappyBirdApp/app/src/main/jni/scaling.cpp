//
// scaling.cpp
//

#include "scaling.h"

Scale::Scale(): M_X(1.0f){
    mGlobalVelocity   = 0.001f; // units/frame
}

Scale::Scale(GLfloat scale): M_X(1.0f){
    mGlobalVelocity   = 0.001f; // units/frame
    setScale(scale);
}

Scale::~Scale(){
}

void Scale::setScale(GLfloat scale){
    //[-1; M_X]x[-1; 1]
    if (scale >= 1.0){
        M_X = 2.0f*scale - 1.0f;
    }
    else{
        M_X = 2.0f/scale - 1.0f;
    }
}

const GLfloat* Scale::paintScaling(GLfloat* v /*non-const*/, unsigned int n) const{
    // x* = 0.5*(M_X+1)*x + 0.5*(M_X-1)
    // y* = y
    for (int i=0; i<2*n; i+=2){
        v[i] = (2.0f/(GLfloat)(M_X+1))*v[i] - ((GLfloat)(M_X-1))/((GLfloat)(M_X+1));
    }
    return v;
}

