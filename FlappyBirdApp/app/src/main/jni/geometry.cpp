//
// Created by HP on 29.11.2015.
//

#ifndef FLAPPYBIRDAPP_GEOMETRY_H
#include "geometry.h"
#endif

PntR2& PntR2::operator+=(const PntR2 &p) {
    mX += p.mX;
    mY += p.mY;
    return *this;
}

PntR2& PntR2::operator-=(const PntR2 &p) {
    mX -= p.mX;
    mY -= p.mY;
    return *this;
}

PntR2& PntR2::operator*=(GLfloat F) {
    mX *= F;
    mY *= F;
    return *this;
}

PntR2& PntR2::operator/=(GLfloat F) {
    mX = mX / F;
    mY = mY / F;
    return *this;
}

const PntR2 PntR2::operator+(const PntR2 &p) const{
    return PntR2(*this) += p;
}

const PntR2 PntR2::operator-(const PntR2 &p) const{
    return PntR2(*this) -= p;
}

const PntR2 PntR2::operator*(GLfloat F) const{
    return PntR2(*this) *= F;
}

const PntR2 PntR2::operator/(GLfloat F) const{
    return PntR2(*this) /= F;
}

const PntR2 PntR2/*a*/::doublevector_product(const PntR2& b/*b*/) const{
    //double vector product [a x b] x b (expanded)
    PntR2 result = *this;
    GLfloat k =  this->mX * b.mY - this->mY * b.mX;
    result.mX = -k * b.mY;
    result.mY =  k * b.mX;
    return result;
}

GLfloat PntR2/*a*/::scalar_product(const PntR2& b/*b*/) const{
    //scalar product (a, b)
    return mX*b.mX + mY*b.mY;
}

GLfloat PntR2::length() const{
    //norm of this vector
    return (GLfloat)sqrt(mX*mX + mY*mY);
}

FlappyCircle::FlappyCircle():mGlobalCenter(), mRadius(0){
    mpGLVertices = NULL;
};

FlappyCircle::FlappyCircle(PntR2& globalCenter, GLfloat radius):
        mGlobalCenter(globalCenter), mRadius(radius){
    mpGLVertices = NULL;
}

FlappyCircle::FlappyCircle(const FlappyCircle& c){
    mGlobalCenter = c.mGlobalCenter; mRadius = c.mRadius;
    mpGLVertices = NULL;
}

void FlappyCircle::operator=(const FlappyCircle& c){
    mGlobalCenter = c.mGlobalCenter; mRadius = c.mRadius;
    mpGLVertices = NULL;
}

FlappyCircle::~FlappyCircle() {
    if (mpGLVertices) delete (mpGLVertices);
}

bool FlappyCircle::isEmpty() const{
    return (mGlobalCenter.mX == 0.0f)&&(mGlobalCenter.mY == 0.0f)&&(mRadius == 0.0f);
}

unsigned int FlappyCircle::calcDrawVertices(){
    unsigned int outVertices = 26;
    if (mpGLVertices){ delete (mpGLVertices); mpGLVertices = NULL; }

    mpGLVertices = new GLfloat[outVertices*2];
    GLfloat* pGLVertices = mpGLVertices;
    pGLVertices[0]=mGlobalCenter.mX; pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY; pGLVertices++;

    float sqrt3 = (float)sqrt(3.0f);
    float sqrt2 = (float)sqrt(2.0f);

    //cos, sin expanded
    pGLVertices[0]=mGlobalCenter.mX;                        pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY + mRadius;              pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX + mRadius*0.258819045f; pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY + mRadius*0.965925826f; pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX + mRadius*0.5f;         pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY + mRadius*0.5f*sqrt3;   pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX + mRadius*0.5f*sqrt2;   pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY + mRadius*0.5f*sqrt2;   pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX + mRadius*0.5f*sqrt3;   pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY + mRadius*0.5f;         pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX + mRadius*0.965925826f; pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY + mRadius*0.258819045f; pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX + mRadius;              pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY;                        pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX + mRadius*0.965925826f; pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY - mRadius*0.258819045f; pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX + mRadius*0.5f*sqrt3;   pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY - mRadius*0.5f;         pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX + mRadius*0.5f*sqrt2;   pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY - mRadius*0.5f*sqrt2;   pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX + mRadius*0.5f;         pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY - mRadius*0.5f*sqrt3;   pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX + mRadius*0.258819045f; pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY - mRadius*0.965925826f; pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX;                        pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY - mRadius;              pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX - mRadius*0.258819045f; pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY - mRadius*0.965925826f; pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX - mRadius*0.5f;         pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY - mRadius*0.5f*sqrt3;   pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX - mRadius*0.5f*sqrt2;   pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY - mRadius*0.5f*sqrt2;   pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX - mRadius*0.5f*sqrt3;   pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY - mRadius*0.5f;         pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX - mRadius*0.965925826f; pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY - mRadius*0.258819045f; pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX - mRadius;              pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY;                        pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX - mRadius*0.965925826f; pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY + mRadius*0.258819045f; pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX - mRadius*0.5f*sqrt3;   pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY + mRadius*0.5f;         pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX - mRadius*0.5f*sqrt2;   pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY + mRadius*0.5f*sqrt2;   pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX - mRadius*0.5f;         pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY + mRadius*0.5f*sqrt3;   pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX - mRadius*0.258819045f; pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY + mRadius*0.965925826f; pGLVertices++;

    pGLVertices[0]=mGlobalCenter.mX;                        pGLVertices++;
    pGLVertices[0]=mGlobalCenter.mY + mRadius;

    return outVertices;
}

GLfloat* FlappyCircle::glDrawVertices(bool bRecalc, unsigned int* outVertices/* = NULL*/){
    if (bRecalc) *outVertices = calcDrawVertices();
    return mpGLVertices;
}

BarrierRect::BarrierRect():mGlobalVertex(), mL(0), mH(0){
    mpGL4Vertices = NULL;
    for (int i=0; i<SZS; i++){
        mpSides[i] = Side();
    }
}

BarrierRect::BarrierRect(PntR2& globalBottomRight, GLfloat width, GLfloat height):
                         mGlobalVertex(globalBottomRight), mL(width), mH(height){
    mpGL4Vertices = NULL;
    /*calcSides();*/
}

BarrierRect::~BarrierRect(){
    if (mpGL4Vertices) delete(mpGL4Vertices);
}

BarrierRect::BarrierRect(const BarrierRect& c){
    mGlobalVertex = c.mGlobalVertex; mL = c.mL; mH = c.mH;
    /*calcSides();*/mpGL4Vertices = NULL;
}

void BarrierRect::operator=(const BarrierRect& c){
    mGlobalVertex = c.mGlobalVertex; mL = c.mL; mH = c.mH;
    /*calcSides();*/mpGL4Vertices = NULL;
}

bool BarrierRect::isEmpty() const{
    return (mGlobalVertex.mX == 0.0f)&&(mGlobalVertex.mY == 0.0f)&&(mL == 0.0f)&&(mH == 0.0);
}

void BarrierRect::calcSides(){ //mpSides can be list either
    //left
    PntR2 p(mGlobalVertex.mX - mL, mGlobalVertex.mY);
    PntR2 v((GLfloat)0.0f, mH);
    mpSides[0] = Side(p, v);
    //top
    p = PntR2(mGlobalVertex.mX - mL, mGlobalVertex.mY + mH);
    v = PntR2(mL, (GLfloat)0.0f);
    mpSides[1] = Side(p, v);
    //bottom
    p = PntR2(mGlobalVertex.mX - mL, mGlobalVertex.mY);
    v = PntR2(mL, (GLfloat)0.0f);
    mpSides[2] = Side(p, v);
    //right
    p = PntR2(mGlobalVertex.mX, mGlobalVertex.mY);
    v = PntR2((GLfloat)0.0f, mH);
    mpSides[3] = Side(p, v);
}

GLfloat* BarrierRect::glDrawVertices(bool bRecalc){
    if (bRecalc) calcDrawVertices();
    return mpGL4Vertices;
}

const Side* BarrierRect::getSides(bool bRecalc){
    if (bRecalc) calcSides();
    return mpSides;
}

void BarrierRect::calcDrawVertices() {
    if (mpGL4Vertices){ delete (mpGL4Vertices); mpGL4Vertices = NULL; }
    mpGL4Vertices = new GLfloat[8];
    mpGL4Vertices[0]=mGlobalVertex.mX - mL;
    mpGL4Vertices[1]=mGlobalVertex.mY;

    mpGL4Vertices[2]=mGlobalVertex.mX - mL;
    mpGL4Vertices[3]=mGlobalVertex.mY + mH;

    mpGL4Vertices[4]=mGlobalVertex.mX;
    mpGL4Vertices[5]=mGlobalVertex.mY;

    mpGL4Vertices[6]=mGlobalVertex.mX;
    mpGL4Vertices[7]=mGlobalVertex.mY + mH;
}

bool circRectIntersect(const FlappyCircle* pCirc, BarrierRect* pRect){// polygonal in common
    PntR2 O(pCirc->mGlobalCenter);

    const Side* side4 = pRect->getSides(1);
    for (int is = 0; is<3; is++) { //one flow - three sides can be intersected
        Side side = side4[is];

        PntR2 A(side.mPnt);
        PntR2 OAVector(A - O);
        PntR2 lVector(side.mVec);

        //orthogonal vector is -[OA x l] x l = p
        PntR2 p = OAVector.doublevector_product(lVector) * (-1.0);
        GLfloat norm = p.length();
        GLfloat proj = 0.0;
        if (norm > 0.00001f) {// eps, or 0.01*mGlobalVelocity
            p = p / norm;

            //projection value is (OA, p/||p||)
            proj = OAVector.scalar_product(p);
        }
        else {
            p = PntR2(0.0f, 0.0f);
        }

        //bird's radius must be no more than projection value,
        //     otherwise - the circle intersects current side (line)
        GLfloat radius = pCirc->mRadius;
        if (proj - radius < 0.0f) {

            //fits piece of side:
            //     side-sector includes one of intersection points
            GLfloat x = (GLfloat) sqrt(radius * radius - proj * proj);
            norm = lVector.length();
            PntR2 intersectionl = p * proj + (lVector / norm) * x;//left limit
            PntR2 intersectionr = p * proj - (lVector / norm) * x;//right limit

            if (((OAVector + lVector - intersectionl).scalar_product(OAVector - intersectionl) <= 0.0f) ||
                ((OAVector + lVector - intersectionr).scalar_product(OAVector - intersectionr) <= 0.0f)){//opposite way
                return true;
            }
        }
    }
    return false;
}


/*LOGI("A: %f, %f; O: %f, %f\n", pRect->mGlobalVertex.mX, pRect->mGlobalVertex.mY, pCirc->mGlobalCenter.mX, pCirc->mGlobalCenter.mY);
    LOGI("A: %f, %f; OA: %f, %f\n", A.mX, A.mY, OAVector.mX, OAVector.mY);
    LOGI("lVector: %f, %f\n", lVector.mX, lVector.mY);
    LOGI("p: %f, %f; norm = %f\n", p.mX, p.mY, norm);
    LOGI("proj: %f\n", projjjj);
    LOGI("abs proj: %f\n", abs(projjjj));
    LOGI("Radius: %f\n", pCirc->mRadius);
*/

/*LOGI("O: %f, %f\n", O.mX, O.mY); LOGI("A: %f, %f\n", A.mX, A.mY);
            LOGI("L, H: %f, %f\n", pRect->mL, pRect->mH);
            LOGI("x: %f; lVector: %f, %f\n", x, lVector.mX, lVector.mY);
            LOGI("proj: %f; p: %f, %f\n", proj, p.mX, p.mY);
            LOGI("intersectionr: %f, %f\n", intersectionr.mX, intersectionr.mY);
            LOGI("OAVector: %f, %f\n", OAVector.mX, OAVector.mY);
*/

