//
// gl_draw.cpp
//

#include "gl_draw.h"

//Panorama globalScene;



GLuint gl_draw::mvPositionHandle(){
    return *mpvPositionHandle;
}

void gl_draw::drawBarriers(){
    if (!mpScene->isEmptyBarrier()){

        //for (BarrierRect* pBarrier = globalScene.firstBarrier(); pBarrier; pBarrier = pBarrier->Next()) {
        //
        //}

        BarrierRect* pBarrier = mpScene->firstBarrier();
        if (!pBarrier) return;
        pBarrier->mGlobalVertex.mX -= 0.01f;

        glVertexAttribPointer(mvPositionHandle(), 2, GL_FLOAT, GL_FALSE, 0, pBarrier->glDrawVertices());
        checkGlError("glVertexAttribPointer");
        glEnableVertexAttribArray(mvPositionHandle());
        checkGlError("glEnableVertexAttribArray");
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
        checkGlError("glDrawArrays");
    }
}