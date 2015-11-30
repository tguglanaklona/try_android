//
// gl_draw.cpp
//

#include "gl_draw.h"

//Panorama globalScene;

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
    TListItemOf<BarrierRect>* pLast = NULL;
    for (TListItemOf<BarrierRect>* pBarrier = mpScene->barriers()->First(); pBarrier; pBarrier = pBarrier->Next()) {
        BarrierRect* pB = &(pBarrier->m_value);
        pB->mGlobalVertex.mX -= mBarriersVelocity;

        //can draw with scaling
        glVertexAttribPointer(mvPositionHandle(), 2, GL_FLOAT, GL_FALSE, 0, pB->glDrawVertices(1));
        checkGlError("glVertexAttribPointer");
        glEnableVertexAttribArray(mvPositionHandle());
        checkGlError("glEnableVertexAttribArray");
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
        checkGlError("glDrawArrays");
        pLast = pBarrier;
    }

    //new barrier
    if (pLast) {
        GLfloat distance = mpScene->getRndLastBarrierSpace();
        if ((1.0 - pLast->m_value.mGlobalVertex.mX) >= distance) {
            GLfloat width = mpScene->getRndLastBarrierWidth();
            BarrierRect newB(PntR2(1.0f, -1.0f), width, mpScene->getRndLastBarrierHeight());
            mpScene->appendBarrier(newB);
        }
    }
}