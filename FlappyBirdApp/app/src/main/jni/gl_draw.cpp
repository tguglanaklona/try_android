//
// gl_draw.cpp
//

#include "gl_draw.h"

gl_draw::gl_draw(Panorama* pgScene, GLuint* pgvPositionHandle):
        mpScene(pgScene), mpvPositionHandle(pgvPositionHandle){
    mGlobalVelocity   = 0.001f;               // units/frame
    mBirdVelocity     = 3.0f*mGlobalVelocity; // units/frame
    mBarriersVelocity = 2.0f*mGlobalVelocity; // units/frame
}

GLuint gl_draw::mvPositionHandle(){
    return *mpvPositionHandle;
}

void gl_draw::drawBarriers(){
    TListItemOf<BarrierRect>* pFirst = mpScene->barriers()->First();
    if (!pFirst) return;

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

        //can draw with scaling ((f) paint)
        glVertexAttribPointer(mvPositionHandle(), 2, GL_FLOAT, GL_FALSE, 0, pB->glDrawVertices(1));
        checkGlError("glVertexAttribPointer");
        glEnableVertexAttribArray(mvPositionHandle());
        checkGlError("glEnableVertexAttribArray");
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        checkGlError("glDrawArrays");
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

bool gl_draw::drawBird() {
    FlappyCircle* pTheBird = mpScene->bird();
    pTheBird->mGlobalCenter.mY -= mBirdVelocity;

    if (pTheBird->mGlobalCenter.mY - pTheBird->mRadius <= -1.0){ //the end
        return false;
    }

    //can draw with scaling ((f) paint)
    unsigned int n = 0;
    glVertexAttribPointer(mvPositionHandle(), 2, GL_FLOAT, GL_FALSE, 0, pTheBird->glDrawVertices(1, &n));
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(mvPositionHandle());
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLE_FAN, 0, n);
    checkGlError("glDrawArrays");
    return true;
}