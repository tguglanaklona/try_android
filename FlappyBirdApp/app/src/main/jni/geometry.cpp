//
// Created by HP on 29.11.2015.
//

#ifndef FLAPPYBIRDAPP_GEOMETRY_H
#include "geometry.h"
#endif

PntR2::PntR2(const PntR2& p){
    mX = p.mX; mY = p.mY;
}

void PntR2::operator=(const PntR2& p){
    mX = p.mX; mY = p.mY;
}

FlappyCircle::FlappyCircle(const FlappyCircle& c){
    mGlobalCenter = c.mGlobalCenter; mRadius = c.mRadius;
}

void FlappyCircle::operator=(const FlappyCircle& c){
    mGlobalCenter = c.mGlobalCenter; mRadius = c.mRadius;
}

bool FlappyCircle::isEmpty(){
    return (mGlobalCenter.mX == 0.0f)&&(mGlobalCenter.mY == 0.0f)&&(mRadius == 0.0f);
}

unsigned int FlappyCircle::calcDrawVertices(){
    if (pGLVertices){ delete (pGLVertices); pGLVertices = NULL; }
    unsigned int outVertices = 14;
    pGLVertices = new GLfloat[outVertices*2];
    pGLVertices[0]=mGlobalCenter.mX;
    pGLVertices[1]=mGlobalCenter.mY;

    //cos, sin expanded
    pGLVertices[2]=mGlobalCenter.mX;
    pGLVertices[3]=mGlobalCenter.mY + mRadius;

    pGLVertices[4]=mGlobalCenter.mX + mRadius*0.5f;
    pGLVertices[5]=mGlobalCenter.mY + mRadius*0.5f*sqrt(3.0f);

    pGLVertices[6]=mGlobalCenter.mX + mRadius*0.5f*sqrt(3.0f);
    pGLVertices[7]=mGlobalCenter.mY + mRadius*0.5f;

    pGLVertices[8]=mGlobalCenter.mX + mRadius;
    pGLVertices[9]=mGlobalCenter.mY;

    pGLVertices[10]=mGlobalCenter.mX + mRadius*0.5f*sqrt(3.0f);
    pGLVertices[11]=mGlobalCenter.mY - mRadius*0.5f;

    pGLVertices[12]=mGlobalCenter.mX + mRadius*0.5f;
    pGLVertices[13]=mGlobalCenter.mY - mRadius*0.5f*sqrt(3.0f);

    pGLVertices[14]=mGlobalCenter.mX;
    pGLVertices[15]=mGlobalCenter.mY - mRadius;

    pGLVertices[16]=mGlobalCenter.mX - mRadius*0.5f;
    pGLVertices[17]=mGlobalCenter.mY - mRadius*0.5f*sqrt(3.0f);

    pGLVertices[18]=mGlobalCenter.mX - mRadius*0.5f*sqrt(3.0f);
    pGLVertices[19]=mGlobalCenter.mY - mRadius*0.5f;

    pGLVertices[20]=mGlobalCenter.mX - mRadius;
    pGLVertices[21]=mGlobalCenter.mY;

    pGLVertices[22]=mGlobalCenter.mX - mRadius*0.5f*sqrt(3.0f);
    pGLVertices[23]=mGlobalCenter.mY + mRadius*0.5f;

    pGLVertices[24]=mGlobalCenter.mX - mRadius*0.5f;
    pGLVertices[25]=mGlobalCenter.mY + mRadius*0.5f*sqrt(3.0f);

    pGLVertices[26]=mGlobalCenter.mX;
    pGLVertices[27]=mGlobalCenter.mY + mRadius;

    return outVertices;
}

const GLfloat* FlappyCircle::glDrawVertices(bool bRecalc, unsigned int* outVertices/* = NULL*/){
    if (bRecalc) *outVertices = calcDrawVertices();
    return pGLVertices;
}

BarrierRect::BarrierRect():mGlobalVertex(), mL(0), mH(0){
    pGL4Vertices = NULL; calcDrawVertices();
}

BarrierRect::BarrierRect(PntR2 globalBottomRight, GLfloat width, GLfloat height):
                         mGlobalVertex(globalBottomRight), mL(width), mH(height){
    pGL4Vertices = NULL; calcDrawVertices();
}

BarrierRect::~BarrierRect(){
    if (pGL4Vertices) delete(pGL4Vertices);
}

BarrierRect::BarrierRect(const BarrierRect& c){
    mGlobalVertex = c.mGlobalVertex; mL = c.mL; mH = c.mH;
    if (pGL4Vertices){ delete (pGL4Vertices); pGL4Vertices = NULL; }
    calcDrawVertices();
}

void BarrierRect::operator=(const BarrierRect& c){
    mGlobalVertex = c.mGlobalVertex; mL = c.mL; mH = c.mH;
    if (pGL4Vertices){ delete (pGL4Vertices); pGL4Vertices = NULL; }
    calcDrawVertices();
}

bool BarrierRect::isEmpty(){
    return (mGlobalVertex.mX == 0.0f)&&(mGlobalVertex.mY == 0.0f)&&(mL == 0.0f)&&(mH == 0.0);
}

const GLfloat* BarrierRect::glDrawVertices(bool bRecalc){
    if (bRecalc) calcDrawVertices();
    return pGL4Vertices;
}

void BarrierRect::calcDrawVertices() {
    if (pGL4Vertices){ delete (pGL4Vertices); pGL4Vertices = NULL; }
    pGL4Vertices = new GLfloat[8];
    pGL4Vertices[0]=mGlobalVertex.mX - mL;
    pGL4Vertices[1]=mGlobalVertex.mY;

    pGL4Vertices[2]=mGlobalVertex.mX - mL;
    pGL4Vertices[3]=mGlobalVertex.mY + mH;

    pGL4Vertices[4]=mGlobalVertex.mX;
    pGL4Vertices[5]=mGlobalVertex.mY;

    pGL4Vertices[6]=mGlobalVertex.mX;
    pGL4Vertices[7]=mGlobalVertex.mY + mH;

    /*pGL4Vertices[0]=mGlobalVertex.mX - mL;
    pGL4Vertices[1]=mGlobalVertex.mY;
    pGL4Vertices[2]=mGlobalVertex.mX - mL;
    pGL4Vertices[3]=mGlobalVertex.mY + mH;
    pGL4Vertices[4]=mGlobalVertex.mX;
    pGL4Vertices[5]=mGlobalVertex.mY + mH;
    pGL4Vertices[6]=mGlobalVertex.mX;
    pGL4Vertices[7]=mGlobalVertex.mY;
    pGL4Vertices[8]=pGL4Vertices[0];
    pGL4Vertices[9]=pGL4Vertices[1];*/
}

