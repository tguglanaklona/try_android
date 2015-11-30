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

TListOf<BarrierRect>* Panorama::barriers() const{
    return mplstRectBarriers;
}

/*TListItemOf<BarrierRect>* Panorama::firstBarrier() const{
    if (mplstRectBarriers->IsEmpty())            // comment if slow
        return NULL;

    return mplstRectBarriers->First();
}*/

bool Panorama::isEmptyBarriers() const{
    return (mplstRectBarriers->IsEmpty()) ? true : false;
}