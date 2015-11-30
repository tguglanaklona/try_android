//
// All screen objects are saved on [-1; 1]x[-1; 1] grid.
// Then they are drawn by OpenGL SE in DrawGLScene()
//

#ifndef FLAPPYBIRDAPP_PANORAMA_H
#define FLAPPYBIRDAPP_PANORAMA_H

#ifndef FLAPPYBIRDAPP_GEOMETRY_H
#include "geometry.h"
#endif

#ifndef FLAPPYBIRDAPP_TLIST_H
#include "tlist.h" // if we go without STL library - create simple List
#endif

class Panorama { // just repository (otherwise can operates with global objects)
public:
    Panorama() : mpFlappyBird(NULL), mplstRectBarriers(NULL){ // first time initialization here
        mpFlappyBird = new FlappyCircle(PntR2(-0.75f, 0.0f), 0.2f);

        mplstRectBarriers = new TListOf<BarrierRect>();
        BarrierRect barrierRect(PntR2(-0.5f, -1.0f), 0.1f, 0.2f);
        appendBarrier(barrierRect);
        BarrierRect barrierRec2(PntR2(0.5f, -1.0f), 0.1f, 0.3f);
        appendBarrier(barrierRec2);
    };
    ~Panorama(){
        if (mpFlappyBird) delete(mpFlappyBird);
        if (mplstRectBarriers) delete(mplstRectBarriers);
    };

private:
    FlappyCircle* mpFlappyBird;
    TListOf<BarrierRect>* mplstRectBarriers;

public:
    void appendBarrier(BarrierRect& item); // append last (push)
    void deleteBarrier();                  // delete first (pop)
    bool isEmptyBarriers() const;

    //TListItemOf<BarrierRect>* firstBarrier() const;
    TListOf<BarrierRect>* barriers() const;
};

#endif //FLAPPYBIRDAPP_PANORAMA_H
