//
// Created by HP on 29.11.2015.
//

#ifndef FLAPPYBIRDAPP_PANORAMA_H
#include "panorama.h"
#endif

void Panorama::appendBarrier(BarrierRect& item){ // append last (push)
    TListItemOf<BarrierRect>* pItem = new TListItemOf<BarrierRect>;
    pItem->m_value = item;
    mplstRectBarriers->Append(pItem);
}

void Panorama::deleteBarrier(){                  // delete first (pop)
}

BarrierRect* Panorama::firstBarrier() const{
    if (mplstRectBarriers->IsEmpty())            // comment if slow
        return NULL;

    TListItemOf<BarrierRect>* pItem = mplstRectBarriers->First();
    return &(pItem->m_value);
}

bool Panorama::isEmptyBarrier() const{
    return (mplstRectBarriers->IsEmpty()) ? true : false;
}