//
// Created by HP on 29.11.2015.
//

#ifndef FLAPPYBIRDAPP_PANORAMA_H
#include "panorama.h"
#endif

Panorama::Panorama() : mpFlappyBird(NULL), mplstRectBarriers(NULL){  // first time initialization here
    // parameters initialization
    mBirdRadius = 0.10f;              //units
    mBirdJump = 1.5f*mBirdRadius;
    mBarrierLimits.minWidth = 0.03f;  // units
    mBarrierLimits.maxWidth = 0.10f;  // units
    mBarrierLimits.minLastSpace = 3.0f*mBarrierLimits.maxWidth;
    mBarrierLimits.maxLastSpace = 7.0f*mBarrierLimits.maxWidth;
    mBarrierLimits.minHeight = 0.03f; // units
    mBarrierLimits.maxHeight = 0.50f - 1.5f*mBirdRadius; // units
    randLastBarrier();

    // first time initialization
    mpFlappyBird = new FlappyCircle(PntR2(-0.75f, 0.0f), mBirdRadius);

    mplstRectBarriers = new TListOf<BarrierRect>();
    BarrierRect barrierRect(PntR2(0.0f, -1.0f), mBarrierLimits.maxWidth, mBarrierLimits.minHeight);
    appendBarrier(barrierRect);
    BarrierRect barrierRec2(PntR2(0.5f, -1.0f), mBarrierLimits.minWidth, mBarrierLimits.maxHeight);
    appendBarrier(barrierRec2);
};

Panorama::~Panorama(){
    if (mpFlappyBird) delete(mpFlappyBird);
    if (mplstRectBarriers) delete(mplstRectBarriers);
};

void Panorama::appendBarrier(BarrierRect& item){ // append last (push)
    TListItemOf<BarrierRect>* pItem = new TListItemOf<BarrierRect>;
    pItem->m_value = item;
    mplstRectBarriers->Append(pItem);

    randLastBarrier();
}

void Panorama::deleteBarrier(){                  // delete first (pop)
    TListItemOf<BarrierRect>* pFirst = mplstRectBarriers->First();
    if (pFirst){ // comment check if slow
        mplstRectBarriers->DeleteItem(pFirst);
    }
}

TListOf<BarrierRect>* Panorama::barriers() const{
    return mplstRectBarriers;
}

FlappyCircle* Panorama::bird() const {
    return mpFlappyBird;
}

bool Panorama::isEmptyBarriers() const{
    return (mplstRectBarriers->IsEmpty()) ? true : false;
}

void Panorama::randLastBarrier(){
    randLastBarrierSpace();
    randLastBarrierWidth();
    randLastBarrierHeight();
}

void Panorama::randLastBarrierSpace(){
    mRndLastBarrierSpace = mBarrierLimits.minLastSpace + (mBarrierLimits.maxLastSpace - mBarrierLimits.minLastSpace)*rand()/RAND_MAX;
    if ((mRndLastBarrierSpace <= mBarrierLimits.maxWidth) || (mRndLastBarrierSpace >= 1.0f)) mRndLastBarrierSpace = 0.25f;
}

void Panorama::randLastBarrierWidth(){
    mRndLastBarrierWidth = mBarrierLimits.minWidth + (mBarrierLimits.maxWidth - mBarrierLimits.minWidth)*rand()/RAND_MAX;
    if ((mRndLastBarrierWidth <= 0.0f) || (mRndLastBarrierWidth >= 1.0f)) mRndLastBarrierWidth = 0.10f;
}

void Panorama::randLastBarrierHeight(){
    mRndLastBarrierHeight = mBarrierLimits.minHeight + (mBarrierLimits.maxHeight - mBarrierLimits.minHeight)*rand()/RAND_MAX;
    if ((mRndLastBarrierHeight <= 0.0f) || (mRndLastBarrierHeight >= 1.0f)) mRndLastBarrierHeight = 0.25f;
}

GLfloat Panorama::getRndLastBarrierSpace(){
    return mRndLastBarrierSpace;
}

GLfloat Panorama::getRndLastBarrierWidth(){
    return mRndLastBarrierWidth;
}

GLfloat Panorama::getRndLastBarrierHeight(){
    return mRndLastBarrierHeight;
}

bool Panorama::isIntersection() const{
    GLfloat rightLim = mpFlappyBird->getRightX();
    for (TListItemOf<BarrierRect>* pBarrier = mplstRectBarriers->First(); pBarrier; pBarrier = pBarrier->Next()) {
        BarrierRect* pB = &(pBarrier->m_value);

        GLfloat leftLim = pB->mGlobalVertex.mX - pB->mL;
        if (leftLim - rightLim > 0.0)
            break;

        if (circRectIntersect(mpFlappyBird, pB))
            return true;
    }
    return false;
}