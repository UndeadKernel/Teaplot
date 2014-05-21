#ifndef _TGL__LINE_H_
#define _TGL__LINE_H_

#include "shape.h"


namespace tgl
{

class Line: public Shape
{
  public:
    Line();
    // The required points for this shape.
    virtual int requiredVertices();
    virtual void render(Matrix &p_transformation, 
        Screen &p_screen, QImage &p_surface);


  private:
    void drawLine(Vector &p_p1, Vector &p_p2, QImage &p_surface);
};



}
#endif /* _TGL__LINE_H_ */
