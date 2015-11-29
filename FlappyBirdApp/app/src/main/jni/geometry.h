//
// Objects primitives and intersections.
// Then they are mapped to Panorama grid
//

#ifndef FLAPPYBIRDAPP_GEOMETRY_H
#define FLAPPYBIRDAPP_GEOMETRY_H

#ifndef FLAPPYBIRDAPP_HEADERS_H
#include "headers.h"
#endif

class PntR2 { //R^2 point
public:
    PntR2():mX(0), mY(0){};
    PntR2(GLfloat x, GLfloat y):mX(x), mY(y){};

    PntR2(const PntR2&);
    void operator=(const PntR2&);
    ~PntR2(){};

    GLfloat mX;
    GLfloat mY;
};

class FlappyCircle { //Circled bird
public:
    FlappyCircle():mGlobalCenter(), mRadius(0){}; //for the consistence
    FlappyCircle(PntR2 globalCenter, GLfloat radius):
            mGlobalCenter(globalCenter), mRadius(radius){};

    FlappyCircle(const FlappyCircle&);
    void operator=(const FlappyCircle&);
    ~FlappyCircle(){};
    bool isEmpty();

    GLfloat mRadius;
    PntR2 mGlobalCenter;
};

class BarrierRect { //Rectangle barrier (частный случай пересечения - быстрый)
public:
    BarrierRect(); //for the consistence
    BarrierRect(PntR2 globalBottomRight, GLfloat width, GLfloat height);

    BarrierRect(const BarrierRect&);
    void operator=(const BarrierRect&);
    ~BarrierRect();
    bool isEmpty();

    GLfloat mL;
    GLfloat mH;
    PntR2 mGlobalVertex;// Bottom right

//pre-calc
private:
    GLfloat *pGL5Vertices;
    void calcDrawVertices();

public:
    const GLfloat* glDrawVertices() const;
};

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

class BarrierPoly { //Polygonal barrier (более общий случай пересечения)
public:
    BarrierPoly(){};
    ~BarrierPoly(){};
};

#endif //FLAPPYBIRDAPP_GEOMETRY_H
