//
// gl_draw.cpp
//

#include "gl_draw.h"

PntR2 gFlappyCenter(-0.75f, 0.0f); // first time initialization

SceneActionPaint::SceneActionPaint():Panorama(gFlappyCenter), Scale(1.0f){  // first time initialization here
    mBirdVelocity     = 3.0f*mGlobalVelocity; // units/frame
    mBarriersVelocity = 2.0f*mGlobalVelocity; // units/frame

    newScene();
}

void SceneActionPaint::newScene(){// first time initialization here
    this->newOne(gFlappyCenter);

    PntR2 bottomRightCorner(0.0f, -1.0f);
    BarrierPaint barrierRectBtm(bottomRightCorner, mBarrierLimits.maxWidth,
                               mBarrierLimits.minHeight);
    bottomRightCorner = PntR2(0.75f, -1.0f);
    BarrierPaint barrierRecBtm2(bottomRightCorner, mBarrierLimits.minWidth,
                               mBarrierLimits.maxHeight);

    GLfloat height = mBarrierLimits.maxHeight;
    bottomRightCorner = PntR2(0.5f,  1.0f - height);
    BarrierPaint barrierRectTop(bottomRightCorner,
                               mBarrierLimits.maxWidth, height);
    height = mBarrierLimits.maxHeight;
    bottomRightCorner = PntR2(1.0f, 1.0f - height);
    BarrierPaint barrierRecTop2(bottomRightCorner,
                               mBarrierLimits.minWidth, height);

    appendBarrier(barrierRectBtm);
    appendBarrier(barrierRectTop);
    appendBarrier(barrierRecBtm2);
    appendBarrier(barrierRecTop2);
}

void SceneActionPaint::drawBarriers(){
    TListItemOf<BarrierPaint>* pFirst = barriers()->First();
   if (!pFirst)
    {// first
        PntR2 newCenter(M_X, -1.0f);
        BarrierPaint newB(newCenter, getRndLastBarrierWidth(),
                         getRndLastBarrierHeight());
        appendBarrier(newB);
        pFirst = barriers()->First();
    }

    {// delete barrier
        if (pFirst->m_value.mGlobalVertex.mX < -1.0f) {
            deleteBarrier();
            pFirst = barriers()->First();
        }
    }

    TListItemOf<BarrierPaint>* pLast = pFirst;
    for (TListItemOf<BarrierPaint>* pBarrier = pFirst; pBarrier; pBarrier = pBarrier->Next()){
        BarrierPaint* pB = &(pBarrier->m_value);
        pB->mGlobalVertex.mX -= mBarriersVelocity;

        //can draw with scaling
        pB->paintBarrier(getScale());
        pLast = pBarrier;
    }

    {// new barrier
        GLfloat distance = getRndLastBarrierSpace();
        if ((M_X - pLast->m_value.mGlobalVertex.mX) >= distance){
            GLfloat height = getRndLastBarrierHeight();
            GLfloat decide = rand();
            GLfloat rndTopBottom = decide<0.5*RAND_MAX ? -1.0f : 1.0f - height;
            PntR2 newCenter(M_X, rndTopBottom);
            BarrierPaint newB(newCenter, getRndLastBarrierWidth(), height);
            appendBarrier(newB);

            //additional probability to appears together (can be modified)
            if ((decide<=0.7*RAND_MAX)&&(decide>0.3*RAND_MAX)){
                PntR2 newCentre(M_X, -height-rndTopBottom);
                BarrierPaint pairB(newCentre, getRndLastBarrierWidth(), height);
                appendBarrier(pairB);
            }
        }
    }
}

bool SceneActionPaint::drawBird(){
    FlappyPaint* pTheBird = bird();
    pTheBird->mGlobalCenter.mY -= mBirdVelocity;
    //LOGI("pTheBird: %x\n", pTheBird);

    // if The End
    if ((pTheBird->getTopY() >= 1.0)||(pTheBird->getBottomY() <= -1.0)){
        return true;
    }
    if (isIntersection()){
        return true;
    }

    //can draw with scaling
    pTheBird->paintTheBird(getScale());
    return false;
}

void SceneActionPaint::onTouch(GLfloat x, GLfloat y) /* x, y - unused */{
    bird()->mGlobalCenter.mY += mBirdJump;
}


