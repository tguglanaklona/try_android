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
    ~PntR2(){};

    //vector operations
    PntR2& operator+=(const PntR2&);                      //  a = a + b
    PntR2& operator-=(const PntR2&);                      //  a = a - b
    PntR2& operator*=(GLfloat F);                         //  a = a * F
    PntR2& operator/=(GLfloat F);                         //  a = a / F
    const PntR2 operator+(const PntR2&) const;            //  a + b
    const PntR2 operator-(const PntR2&) const;            //  a - b
    const PntR2 operator*(GLfloat F) const;               //  a * F
    const PntR2 operator/(GLfloat F) const;               //  a / F
    const PntR2 doublevector_product(const PntR2&) const; // [a x b] x b
    GLfloat scalar_product(const PntR2&) const;           // (a, b)
    GLfloat length() const;                               // ||a||

    GLfloat mX;
    GLfloat mY;
};

class LineR2 { //R^2 line
public:
    LineR2():mVec(), mPnt(){};//for the consistence
    LineR2(PntR2 point, PntR2 vector):mVec(vector), mPnt(point){};
    virtual ~LineR2(){};

    PntR2 mPnt; // point
    PntR2 mVec; // direction vector
};

class Side : public LineR2 { //R^2 line with Limits
public:
    Side():LineR2(){};//for the consistence
    Side(PntR2 point, PntR2 vector/*full*/);
    ~Side(){};
};

class FlappyCircle { //Circled bird
public:
    FlappyCircle():mGlobalCenter(), mRadius(0){}; //for the consistence
    FlappyCircle(PntR2 globalCenter, GLfloat radius):
            mGlobalCenter(globalCenter), mRadius(radius){};

    FlappyCircle(const FlappyCircle&);
    void operator=(const FlappyCircle&);
    ~FlappyCircle();
    bool isEmpty() const;

    GLfloat mRadius;
    PntR2 mGlobalCenter;

    GLfloat getTopY()    const {return mGlobalCenter.mY + mRadius;}
    GLfloat getRightX()  const {return mGlobalCenter.mX + mRadius;}
    GLfloat getBottomY() const {return mGlobalCenter.mY - mRadius;}
    GLfloat getLeftX()   const {return mGlobalCenter.mX - mRadius;}

//pre-calc
private:
    //we can save more positions or not
    GLfloat *mpGLVertices;
    unsigned int calcDrawVertices();

public:
    /*const*/GLfloat* glDrawVertices(bool, unsigned int* out = NULL);
};

class BarrierRect { //Rectangle barrier
    static const unsigned int SZS = 4;
public:
    BarrierRect();//for the consistence
    BarrierRect(PntR2 globalBottomRight, GLfloat width, GLfloat height);

    BarrierRect(const BarrierRect&);
    void operator=(const BarrierRect&);
    ~BarrierRect();
    bool isEmpty() const;

    PntR2 mGlobalVertex;// Bottom right
    GLfloat mL;
    GLfloat mH;

//pre-calc
private:
    GLfloat *mpGL4Vertices;
    void calcDrawVertices();
    Side mpSides[SZS];//may be reconstructed for polygonal intersections
    void calcSides();

public:
    /*const*/GLfloat* glDrawVertices(bool);
    const Side* getSides(bool);
};

bool circRectIntersect(const FlappyCircle*, BarrierRect*);

#endif //FLAPPYBIRDAPP_GEOMETRY_H
