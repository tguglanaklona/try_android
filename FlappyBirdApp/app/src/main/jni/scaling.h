//
// scaling.h
//

#ifndef FLAPPYBIRDAPP_SCALING_H
#define FLAPPYBIRDAPP_SCALING_H

#ifndef FLAPPYBIRDAPP_HEADERS_H
#include "headers.h"
#endif

class Scale {
public:
    Scale();//for the consistence
    Scale(GLfloat scale);
    virtual ~Scale();

    void setScale(GLfloat scale);
    const GLfloat* paintScaling(GLfloat*, unsigned int) const;

protected:
    GLfloat M_X;
    GLfloat mGlobalVelocity; // units/frame

    const Scale* getScale() const{ return this; }

private:
    Scale(const Scale&);
    void operator=(const Scale&);
};

#endif //FLAPPYBIRDAPP_SCALING_H
