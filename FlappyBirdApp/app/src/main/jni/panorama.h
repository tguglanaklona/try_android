//
// All screen objects are saved here (with no grid) and controlled by SceneActionPaint.
// They are drawn by OpenGL SE in DrawGLScene() function.
//

#ifndef FLAPPYBIRDAPP_PANORAMA_H
#define FLAPPYBIRDAPP_PANORAMA_H

#ifndef FLAPPYBIRDAPP_GEOMETRY_RENDER_H
#include "geometry_render.h"
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
    Panorama(PntR2& flappyCenter); // first time initialization here
    virtual ~Panorama();
    void newOne(PntR2&);

private:
    FlappyPaint* mpFlappyBird;
    TListOf<BarrierPaint>* mplstRectBarriers;

    Panorama(const Panorama&);
    void operator=(const Panorama&);

public:
    void appendBarrier(BarrierPaint& item); // append last (push)
    void deleteBarrier();                   // delete first (pop)
    bool isEmptyBarriers() const;

    //TListItemOf<BarrierPaint>* firstBarrier() const;
    TListOf<BarrierPaint>* barriers() const;
    FlappyPaint* bird() const;

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
