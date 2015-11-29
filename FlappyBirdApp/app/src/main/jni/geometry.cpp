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

BarrierRect::BarrierRect():mGlobalVertex(), mL(0), mH(0){
    pGL5Vertices = NULL; calcDrawVertices();
}

BarrierRect::BarrierRect(PntR2 globalBottomRight, GLfloat width, GLfloat height):
                         mGlobalVertex(globalBottomRight), mL(width), mH(height){
    pGL5Vertices = NULL; calcDrawVertices();
}

BarrierRect::~BarrierRect(){
    if (pGL5Vertices) delete(pGL5Vertices);
}

BarrierRect::BarrierRect(const BarrierRect& c){
    mGlobalVertex = c.mGlobalVertex; mL = c.mL; mH = c.mH;
    if (pGL5Vertices){ delete (pGL5Vertices); pGL5Vertices = NULL; }
    calcDrawVertices();
}

void BarrierRect::operator=(const BarrierRect& c){
    mGlobalVertex = c.mGlobalVertex; mL = c.mL; mH = c.mH;
    if (pGL5Vertices){ delete (pGL5Vertices); pGL5Vertices = NULL; }
    calcDrawVertices();
}

bool BarrierRect::isEmpty(){
    return (mGlobalVertex.mX == 0.0f)&&(mGlobalVertex.mY == 0.0f)&&(mL == 0.0f)&&(mH == 0.0);
}

const GLfloat* BarrierRect::glDrawVertices() const{
    return pGL5Vertices;
}

void BarrierRect::calcDrawVertices() {
    if (pGL5Vertices){ delete (pGL5Vertices); pGL5Vertices = NULL; }
    pGL5Vertices = new GLfloat[10];
    pGL5Vertices[0]=mGlobalVertex.mX - mL;
    pGL5Vertices[1]=mGlobalVertex.mY;
    pGL5Vertices[2]=mGlobalVertex.mX - mL;
    pGL5Vertices[3]=mGlobalVertex.mY + mH;
    pGL5Vertices[4]=mGlobalVertex.mX;
    pGL5Vertices[5]=mGlobalVertex.mY + mH;
    pGL5Vertices[6]=mGlobalVertex.mX;
    pGL5Vertices[7]=mGlobalVertex.mY;
    pGL5Vertices[8]=pGL5Vertices[0];
    pGL5Vertices[9]=pGL5Vertices[1];
}

