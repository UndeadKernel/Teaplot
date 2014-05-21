#include "point.h"
#include "matrix.h"
#include "vector.h"

#include <QImage>
#include <QColor>
#include <stdexcept>


namespace tgl
{

//------------------------------------------------------------------------------
// Public Functions

Point::Point()
    : Shape()
{
    
}

int Point::requiredVertices()
{
    // The number of points that we need to store.
    return 1;
}

void Point::render(Matrix &p_transformation, 
        Screen &p_screen, QImage &p_surface)
{
    Vector screen_coords = transformVertex(0, p_transformation, p_screen);

    if(!p_surface.valid(screen_coords[0], screen_coords[1])) {
        return;
    }

    // Draw the screen coords to the surface.
    p_surface.setPixel(screen_coords[0], screen_coords[1], 
        QColor(255, 0, 0).rgb());
}

//------------------------------------------------------------------------------
// Private Functions

}
