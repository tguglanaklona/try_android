//
// gl_draw.cpp
//

#include "gl_draw.h"

//Panorama globalScene;

gl_draw::gl_draw(const Panorama* pgScene, GLuint* pgvPositionHandle):
        mpScene(pgScene), mpvPositionHandle(pgvPositionHandle){
    barriersVelocity = 0.001f;
}

GLuint gl_draw::mvPositionHandle(){
    return *mpvPositionHandle;
}

void gl_draw::drawBarriers(){

    for (TListItemOf<BarrierRect>* pBarrier = mpScene->barriers()->First(); pBarrier; pBarrier = pBarrier->Next()) {
        BarrierRect* pB = &(pBarrier->m_value);
        pB->mGlobalVertex.mX -= barriersVelocity;

        glVertexAttribPointer(mvPositionHandle(), 2, GL_FLOAT, GL_FALSE, 0, pB->glDrawVertices(1));
        checkGlError("glVertexAttribPointer");
        glEnableVertexAttribArray(mvPositionHandle());
        checkGlError("glEnableVertexAttribArray");
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
        checkGlError("glDrawArrays");
    }
}