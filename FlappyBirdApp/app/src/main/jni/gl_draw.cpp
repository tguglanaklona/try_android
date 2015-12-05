//
// gl_draw.cpp
//

#include "gl_draw.h"

GlDraw::GlDraw(GLuint* pgvPositionHandle):  // first time initialization here
        mpScene(NULL), mpvPositionHandle(pgvPositionHandle), M_X(1.0f){
    mGlobalVelocity   = 0.001f;               // units/frame
    mBirdVelocity     = 3.0f*mGlobalVelocity; // units/frame
    mBarriersVelocity = 2.0f*mGlobalVelocity; // units/frame

    newPanorama();
}

GlDraw::~GlDraw(){
    if (mpScene) delete(mpScene);
}

void GlDraw::newPanorama(){// first time initialization here
    PntR2 flappyCenter(-0.75f, 0.0f);
    if (!mpScene){
        mpScene = new Panorama(flappyCenter);
    }
    else {
        mpScene->newOne(flappyCenter);
    }
    BarrierRect barrierRect(PntR2(0.0f, -1.0f), mpScene->mBarrierLimits.maxWidth,
                            mpScene->mBarrierLimits.minHeight);
    BarrierRect barrierRec2(PntR2(0.5f, -1.0f), mpScene->mBarrierLimits.minWidth,
                            mpScene->mBarrierLimits.maxHeight);
    mpScene->appendBarrier(barrierRect);
    mpScene->appendBarrier(barrierRec2);
}

GLuint GlDraw::mvPositionHandle() const{
    return *mpvPositionHandle;
}

void GlDraw::setScale(GLfloat scale){
    //[-1; M_X]x[-1; 1]
    if (scale >= 1.0){
        M_X = 2.0f*scale - 1.0f;
    }
    else{
        M_X = 2.0f/scale - 1.0f;
    }
}

void GlDraw::paintBarrier(BarrierRect* pB) const{
    if (!pB) return;
    GLfloat* pV = pB->glDrawVertices(1);
    paintScaling(pV, 4);
    glVertexAttribPointer(mvPositionHandle(), 2, GL_FLOAT, GL_FALSE, 0, pV);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(mvPositionHandle());
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    checkGlError("glDrawArrays");
}

void GlDraw::paintTheBird(FlappyCircle* pTheBird) const{
    unsigned int n = 0;
    if (!pTheBird) {
        pTheBird = mpScene->bird();
        if (!pTheBird) return;
    }
    GLfloat* pV = pTheBird->glDrawVertices(1, &n);
    paintScaling(pV, n);
    glVertexAttribPointer(mvPositionHandle(), 2, GL_FLOAT, GL_FALSE, 0, pV);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(mvPositionHandle());
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLE_FAN, 0, n);
    checkGlError("glDrawArrays");
}

//to do
GLfloat* GlDraw::paintScaling(GLfloat* v, unsigned int n) const{ //to do: GLfloat* v == this, some paint class: { GLfloat*, int n }, paintBird, paintBarrier
    // x* = 0.5*(M_X+1)*x + 0.5*(M_X-1)
    // y* = y
    for (int i=0; i<2*n; i+=2){
        v[i] = (2.0f/(GLfloat)(M_X+1))*v[i] - ((GLfloat)(M_X-1))/((GLfloat)(M_X+1));
    }

    return v;
    //to do: return this
}

void GlDraw::drawBarriers(){
    TListItemOf<BarrierRect>* pFirst = mpScene->barriers()->First();
    if (!pFirst)
    {// first
        BarrierRect newB(PntR2(M_X, -1.0f), mpScene->getRndLastBarrierWidth(),
                         mpScene->getRndLastBarrierHeight());
        mpScene->appendBarrier(newB);
        pFirst = mpScene->barriers()->First();
    }

    {// delete barrier
        if (pFirst->m_value.mGlobalVertex.mX < -1.0f) {
            mpScene->deleteBarrier();
            pFirst = mpScene->barriers()->First();
        }
    }

    TListItemOf<BarrierRect>* pLast = pFirst;
    for (TListItemOf<BarrierRect>* pBarrier = pFirst; pBarrier; pBarrier = pBarrier->Next()) {
        BarrierRect* pB = &(pBarrier->m_value);
        pB->mGlobalVertex.mX -= mBarriersVelocity;

        //can draw with scaling
        paintBarrier(pB);
        pLast = pBarrier;
    }

    {// new barrier
        GLfloat distance = mpScene->getRndLastBarrierSpace();
        if ((M_X - pLast->m_value.mGlobalVertex.mX) >= distance) {
            GLfloat width = mpScene->getRndLastBarrierWidth();
            BarrierRect newB(PntR2(M_X, -1.0f), width, mpScene->getRndLastBarrierHeight());
            mpScene->appendBarrier(newB);
        }
    }
}

bool GlDraw::drawBird(){
    FlappyCircle* pTheBird = mpScene->bird();
    pTheBird->mGlobalCenter.mY -= mBirdVelocity;

    // if The End
    if ((pTheBird->getTopY() >= 1.0)||(pTheBird->getBottomY() <= -1.0)){
        return true;
    }
    if (mpScene->isIntersection()){
        return true;
    }

    //can draw with scaling
    paintTheBird(pTheBird);
    return false;
}

void GlDraw::onTouch(GLfloat x, GLfloat y) /* x, y - unused */{
    FlappyCircle* pBird = mpScene->bird();
    if (!pBird) return;
    pBird->mGlobalCenter.mY += mpScene->mBirdJump;
}


