#ifndef _TGL__POINT_H_
#define _TGL__POINT_H_

#include "shape.h"


namespace tgl
{

class Point: public Shape
{
  public:
    Point();
    // The required points for this shape.
    virtual int requiredVertices();
    // Each shape should know how to render itself.
    virtual void render(Matrix &p_transformation, 
        Screen &p_screen, QImage &p_surface);

  private:
    
};



}
#endif /* _TGL__POINT_H_ */
