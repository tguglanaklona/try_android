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

struct BarrierLimits{
    GLfloat minWidth; // units (1x1)
    GLfloat maxWidth; // units (1x1)
    GLfloat minLastSpace;
    GLfloat maxLastSpace;
    GLfloat minHeight;
    GLfloat maxHeight;
};

class Panorama { // just repository (otherwise can operate with global objects)
public:
    Panorama(); // first time initialization here
    ~Panorama();
    void newOne();

private:
    FlappyCircle* mpFlappyBird;
    TListOf<BarrierRect>* mplstRectBarriers;

    Panorama(const Panorama&);
    void operator=(const Panorama&);

public:
    void appendBarrier(BarrierRect& item); // append last (push)
    void deleteBarrier();                  // delete first (pop)
    bool isEmptyBarriers() const;

    //TListItemOf<BarrierRect>* firstBarrier() const;
    TListOf<BarrierRect>* barriers() const;
    FlappyCircle* bird() const;

    bool isIntersection() const;

public: // geometry
    void randLastBarrier();
    GLfloat getRndLastBarrierSpace() const;
    GLfloat getRndLastBarrierWidth() const;
    GLfloat getRndLastBarrierHeight() const;
    BarrierLimits mBarrierLimits; //Barrier limits
    GLfloat mBirdRadius;          //Bird limits
    GLfloat mBirdJump;

private:
    GLfloat mRndLastBarrierSpace;
    GLfloat mRndLastBarrierWidth;
    GLfloat mRndLastBarrierHeight;

    void randLastBarrierSpace();
    void randLastBarrierWidth();
    void randLastBarrierHeight();
};

#endif //FLAPPYBIRDAPP_PANORAMA_H
