//
// panorama.cpp
//

#ifndef FLAPPYBIRDAPP_PANORAMA_H
#include "panorama.h"
#endif

Panorama::Panorama(PntR2& flappyCenter) : mpFlappyBird(NULL), mplstRectBarriers(NULL){
    newOne(flappyCenter);
}

void Panorama::newOne(PntR2& flappyCenter){ // first time initialization here
    // relative parameters initialization
    mBirdRadius = 0.10f;              //units
    mBirdJump = 1.5f*mBirdRadius;
    mBarrierLimits.minWidth = 0.03f;  // units
    mBarrierLimits.maxWidth = 0.10f;  // units
    mBarrierLimits.minLastSpace = 2.0f*mBarrierLimits.maxWidth;
    mBarrierLimits.maxLastSpace = 3.5f*mBarrierLimits.maxWidth;
    mBarrierLimits.minHeight = 0.1f; // units
    mBarrierLimits.maxHeight = 1.0f - 2.5f*mBirdRadius; // when appeared simultaneously
    randLastBarrier();

    // first time initialization
    if (!mpFlappyBird) {
        mpFlappyBird = new FlappyCircle(flappyCenter, mBirdRadius);
    }
    else{
        mpFlappyBird->mGlobalCenter = flappyCenter;
        mpFlappyBird->mRadius = mBirdRadius;
    }

    if (!mplstRectBarriers) {
        mplstRectBarriers = new TListOf<BarrierRect>();
    }
    else{
        mplstRectBarriers->Clear();
    }
}

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

GLfloat Panorama::getRndLastBarrierSpace() const{
    return mRndLastBarrierSpace;
}

GLfloat Panorama::getRndLastBarrierWidth() const{
    return mRndLastBarrierWidth;
}

GLfloat Panorama::getRndLastBarrierHeight() const{
    return mRndLastBarrierHeight;
}

bool Panorama::isIntersection() const{
    GLfloat rightLim = mpFlappyBird->getRightX();
    for (TListItemOf<BarrierRect>* pBarrier = mplstRectBarriers->First(); pBarrier; pBarrier = pBarrier->Next()) {//п/п
        BarrierRect* pB = &(pBarrier->m_value);

        GLfloat leftLim = pB->mGlobalVertex.mX - pB->mL;
        if (leftLim - rightLim > 0.0)
            continue; //break; if barriers go one-by-one

        if (circRectIntersect(mpFlappyBird, pB))
            return true;
    }
    return false;
}