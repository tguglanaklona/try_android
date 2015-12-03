//
// gl_draw.cpp
//

#include "gl_draw.h"

gl_draw::gl_draw(GLuint* pgvPositionHandle):  // first time initialization here
        mpScene(NULL), mpvPositionHandle(pgvPositionHandle), M_X(1.0f){
    mGlobalVelocity   = 0.001f;               // units/frame
    mBirdVelocity     = 3.0f*mGlobalVelocity; // units/frame
    mBarriersVelocity = 2.0f*mGlobalVelocity; // units/frame

    newPanorama();
}

gl_draw::~gl_draw(){
    if (mpScene) delete(mpScene);
}

void gl_draw::newPanorama(){// first time initialization here
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

GLuint gl_draw::mvPositionHandle() const{
    return *mpvPositionHandle;
}

void gl_draw::setScale(GLfloat scale){
    //[-1; M_X]x[-1; 1]
    if (scale >= 1.0){
        M_X = scale - 1.0f;
    }
    else{
        M_X = 1.0f/scale - 1.0f;
    }
}

void gl_draw::paintBarrier(BarrierRect* pB) const{
    if (!pB) return;
    glVertexAttribPointer(mvPositionHandle(), 2, GL_FLOAT, GL_FALSE, 0, pB->glDrawVertices(1));
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(mvPositionHandle());
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    checkGlError("glDrawArrays");
}

void gl_draw::paintTheBird(FlappyCircle* pTheBird) const{
    unsigned int n = 0;
    if (!pTheBird) {
        pTheBird = mpScene->bird();
        if (!pTheBird) return;
    }
    glVertexAttribPointer(mvPositionHandle(), 2, GL_FLOAT, GL_FALSE, 0, pTheBird->glDrawVertices(1, &n));
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(mvPositionHandle());
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLE_FAN, 0, n);
    checkGlError("glDrawArrays");
}

void gl_draw::drawBarriers(){
    TListItemOf<BarrierRect>* pFirst = mpScene->barriers()->First();
    if (!pFirst)
    {// first
        BarrierRect newB(PntR2(1.0f, -1.0f), mpScene->getRndLastBarrierWidth(),
                         mpScene->getRndLastBarrierHeight());
        mpScene->appendBarrier(newB);
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
        if ((1.0 - pLast->m_value.mGlobalVertex.mX) >= distance) {
            GLfloat width = mpScene->getRndLastBarrierWidth();
            BarrierRect newB(PntR2(1.0f, -1.0f), width, mpScene->getRndLastBarrierHeight());
            mpScene->appendBarrier(newB);
        }
    }
}

bool gl_draw::drawBird(){
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

void gl_draw::onTouch(GLfloat x, GLfloat y) /* x, y - unused */{
    FlappyCircle* pBird = mpScene->bird();
    if (!pBird) return;
    pBird->mGlobalCenter.mY += mpScene->mBirdJump;
}


