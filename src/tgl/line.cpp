#include "line.h"
#include "matrix.h"
#include "vector.h"

#include <stdexcept>
#include <QImage>
#include <QColor>
#include <cmath>


namespace tgl
{

//------------------------------------------------------------------------------
// Public Functions

Line::Line()
    : Shape()
{
    
}

int Line::requiredVertices()
{
    // The number of points that we need to store.
    return 2;
}

void Line::render(Matrix &p_transformation, 
    Screen &p_screen, QImage &p_surface)
{
    Vector p1 = transformVertex(0, p_transformation, p_screen);
    Vector p2 = transformVertex(1, p_transformation, p_screen);

    drawLine(p1, p2, p_surface);
}


//------------------------------------------------------------------------------
// Private Functions

// Line drawing code taken from: 
// ... http://www.gamedev.net/page/resources/_/technical/game-programming/line-drawing-algorithm-explained-r1275
// ... Modified be me :)
void Line::drawLine(Vector &p_p1, Vector &p_p2, QImage &p_surface)
{
    int x; // Next x-coordinate of the pixel value to draw.
    int y; // Next y-coordinate of the pixel value to draw.
    int d_x; // Delta x.
    int d_y; // Delta y.
    int x_increment1;
    int y_increment1;
    int x_increment2;
    int y_increment2;
    int denominator;
    int numerator;
    int numerator_add;
    int pixels;
    // bool render_point;

    d_x = std::abs(p_p2[0] - p_p1[0]);
    d_y = std::abs(p_p2[1] - p_p1[1]);

    x = p_p1[0];                   	// Start x off at the first pixel
    y = p_p1[1];                   	// Start y off at the first pixel

    if (p_p2[0] >= p_p1[0]) {            	// The x-values are increasing
        x_increment1 = 1;
        x_increment2 = 1;
    }
    else {                     	// The x-values are decreasing
        x_increment1 = -1;
        x_increment2 = -1;
    }

    if (p_p2[1] >= p_p1[1]) {            	// The y-values are increasing
        y_increment1 = 1;
        y_increment2 = 1;
    }
    else {                     	// The y-values are decreasing
        y_increment1 = -1;
        y_increment2 = -1;
    }

    if (d_x >= d_y) {    	// There is at least one x-value for every y-value
        x_increment1 = 0;              	// Don't change the x when numerator >= denominator
        y_increment2 = 0;              	// Don't change the y for every iteration
        denominator = d_x;
        numerator = d_x / 2; // Start half way thorugh (to make up for precision errors).
        numerator_add = d_y;
        pixels = d_x;     	// There are more x-values than y-values
    }
    else {                     	// There is at least one y-value for every x-value
        x_increment2 = 0;              	// Don't change the x for every iteration
        y_increment1 = 0;              	// Don't change the y when numerator >= denominator
        denominator = d_y;
        numerator = d_y / 2;
        numerator_add = d_x;
        pixels = d_y;     	// There are more y-values than x-values
    }

    for (int i = 0; i <= pixels; i++) {
        // Should we render this pixel?

        // render_point = true;
        // if(x < 0 || x > p_surface.width()) {
        //     // Skip drawing this point.
        //     render_point = false;
        // }
        // if(y < 0 || y > p_surface.height()) {
        //     // Or skip this point.
        //     render_point = false;
        // }        

        if(p_surface.valid(x, y)) {
            p_surface.setPixel(x, y, QColor(0, 0, 255).rgb());  	// Draw the current pixel
        }

        numerator += numerator_add;          	            // Increase the numerator by the top of the fraction

        if (numerator >= denominator) {                    	// Check if numerator >= denominator
            numerator -= denominator;           	        // Calculate the new numerator value
            x += x_increment1;           	                // Change the x as appropriate
            y += y_increment1;           	                // Change the y as appropriate
        }

        x += x_increment2;       // Change the x as appropriate
        y += y_increment2;       // Change the y as appropriate
    }
}

}
