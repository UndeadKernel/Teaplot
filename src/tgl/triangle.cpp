#include "triangle.h"
#include "matrix.h"
#include "vector.h"
#include "screen.h"

#include <stdexcept>
#include <QImage>
#include <QColor>
#include <cmath>
#include <algorithm>
#include <iostream>


namespace tgl
{

//------------------------------------------------------------------------------
// Public Functions

Triangle::Triangle()
{
    
}

int Triangle::requiredVertices()
{
    // The number of points that we need to store.
    return 3;
}

void Triangle::render(Matrix &p_transformation, 
    Screen &p_screen, QImage &p_surface)
{
    // Get vertices in screen space.
    Vector p1 = transformVertex(0, p_transformation, p_screen);
    Vector p2 = transformVertex(1, p_transformation, p_screen);
    Vector p3 = transformVertex(2, p_transformation, p_screen);

    // Get bounding box of triangle.
    m_min_x = static_cast<int>(round(std::min(p1.x(), std::min(p2.x(), p3.x()))));
    m_min_y = static_cast<int>(round(std::min(p1.y(), std::min(p2.y(), p3.y()))));
    m_max_x = static_cast<int>(round(std::max(p1.x(), std::max(p2.x(), p3.x()))));
    m_max_y = static_cast<int>(round(std::max(p1.y(), std::max(p2.y(), p3.y()))));

    // Rasterize only triangles potentially inside the screen.
    if( (m_max_x >= 0 && m_min_x <= p_screen.width()) &&
        (m_max_y >= 0 && m_min_y <= p_screen.height())) {
        // Transform the normals into eye space.
        Vector n1 = transformNormal(0, p_transformation);
        Vector n2 = transformNormal(1, p_transformation);
        Vector n3 = transformNormal(2, p_transformation);

        rasterize(p1, p2, p3,n1, n2, n3, p_surface);
    }
}


//------------------------------------------------------------------------------
// Private Functions

// The following code was inspired by the user 'Nick'.
// ... Pieces of code were taken and modified from:
// ... http://www.devmaster.net/forums/showthread.php?t=1884
void Triangle::rasterize(const Vector &p_p1, const Vector &p_p2, 
    const Vector &p_p3, const Vector &p_n1, const Vector &p_n2, 
    const Vector &p_n3, QImage &p_surface)
{
    // Flag that tells if we have to stop drawing pixels.
    bool after_edge;

    // The Following commented code was an attempt to rasterize using 
    // ... barycentric coordinates. The precision loss of the calculations
    // ... had a big effect on how the triangles were drawn. There was no
    // ... easy way to determine if an edge was left, right or top
    // ... for the fill convention.

    // double x1 = p_p1[0];
    // double x2 = p_p2[0];
    // double x3 = p_p3[0];

    // double y1 = p_p1[1];
    // double y2 = p_p2[1];
    // double y3 = p_p3[1];

    // Find the bounding box of the triangle.
    // Bounding boxes pre-calculated in the render function.

    // Barycentric stuff.
    // double alpha;
    // double beta;
    // double gamma;
    // double alpha_den = edgef(x1, y1, x2, y2, x3, y3);
    // double beta_den = edgef(x2, y2, x3, y3, x1, y1);
    // No need to calculate gamma explicitly.

    // // Go through each scanline in the bounding rectangle.
    // for(int y = m_min_y; y <= m_max_y; ++y) {
        
    //     after_edge = false;

    //     for(int x = m_min_x; x <= m_max_x; ++x) {

    //         // Calculate Barycentric coordinate of this point.
    //         alpha = edgef(x, y, x2, y2, x3, y3) / alpha_den;
    //         beta = edgef(x, y, x3, y3, x1, y1) / beta_den;
    //         gamma = 1 - alpha - beta; // Implicit calculation of gamma.

    //         if( (alpha >= 0 && alpha <= 1) && 
    //             (beta >= 0 && beta <= 1) &&
    //             (gamma >= 0 && gamma <= 1)) {

    //             // We have entered an edge.
    //             after_edge = true;

    //             // Is the point to render valid in the render surface?
    //             if(p_surface.valid(x, y)) {
    //                 p_surface.setPixel(x, y, QColor(alpha*255, beta*255, gamma*255).rgb());
    //             }
    //         } else if(after_edge == true) {
    //             // We are past the left edge. Ignore the rest.
    //             break;
    //         }
            
    //     }
    // }
    
    // Fixed point arithmetic (28.4)
    int x1 = round(p_p1.x() * 16.0);
    int x2 = round(p_p2.x() * 16.0);
    int x3 = round(p_p3.x() * 16.0);

    int y1 = round(p_p1.y() * 16.0);
    int y2 = round(p_p2.y() * 16.0);
    int y3 = round(p_p3.y() * 16.0);

    // Fixed point (2.30)
    int z1 = round(p_p1.z() * (1<<30));
    int z2 = round(p_p2.z() * (1<<30));
    int z3 = round(p_p3.z() * (1<<30));

    // Barycentric stuff, in (24.8) fixed point format.
    int alpha;
    int beta;
    int gamma;
    int alpha_den = edgef(x1, y1, x2, y2, x3, y3);
    int beta_den = edgef(x2, y2, x3, y3, x1, y1);

    // Deltas (28.4)
    int dx12 = x1 - x2;
    int dx23 = x2 - x3;
    int dx31 = x3 - x1;

    int dy12 = y1 - y2;
    int dy23 = y2 - y3;
    int dy31 = y3 - y1;

    // Deltas (24.8)
    int fdx12 = dx12 << 4;
    int fdx23 = dx23 << 4;
    int fdx31 = dx31 << 4;

    int fdy12 = dy12 << 4;
    int fdy23 = dy23 << 4;
    int fdy31 = dy31 << 4;

    // Find the bounding box of the triangle (32.0). Round up.
    int min_x = (std::min(x1, std::min(x2, x3)) + 0xF) >> 4;
    int min_y = (std::min(y1, std::min(y2, y3)) + 0xF) >> 4;
    int max_x = (std::max(x1, std::max(x2, x3)) + 0xF) >> 4;
    int max_y = (std::max(y1, std::max(y2, y3)) + 0xF) >> 4;

    // Clamp points to a reazonable size.
    if(min_x < 0) min_x = 0;
    if(min_y < 0) min_y = 0;
    if(max_x > p_surface.width()) max_x = p_surface.width();
    if(max_y > p_surface.height()) max_y = p_surface.height();

    // Half-edge constants (28.4 * 28.4) = (56.8) -> (24.8)
    int c1 = dy12 * x1 - dx12 * y1;
    int c2 = dy23 * x2 - dx23 * y2;
    int c3 = dy31 * x3 - dx31 * y3;

    // Pixel depth (24.8)
    long pixel_depth = 0;

    // Corrections for the fill convension top-left and horizontal edges.
    if(dy12 < 0 || (dy12 == 0 && dx12 > 0)) c1++;
    if(dy23 < 0 || (dy23 == 0 && dx23 > 0)) c2++;
    if(dy31 < 0 || (dy31 == 0 && dx31 > 0)) c3++;

    // Evaluate the y coordinate of the first point of the bounding rectangle. 
    // ... (24.8) + (28.4 * 28.4) - (28.4 * 28.4) = (24.8)
    int cy1 = c1 + dx12 * (min_y << 4) - dy12 * (min_x << 4);
    int cy2 = c2 + dx23 * (min_y << 4) - dy23 * (min_x << 4);
    int cy3 = c3 + dx31 * (min_y << 4) - dy31 * (min_x << 4);

    // Evaluation of the x coordinate, calculated in the loop.
    int cx1;
    int cx2;
    int cx3;

    for(int y = min_y; y < max_y; ++y) {
        cx1 = cy1;
        cx2 = cy2;
        cx3 = cy3;

        after_edge = false;

        for(int x = min_x; x < max_x; ++x) {
            // Counter clockwise culling (CCW).
            if(cx1 > 0 && cx2 > 0 && cx3 > 0) {
                // We have entered an edge, mark the flag as so.
                after_edge = true;
                // Shall we draw the pixel?
                if(p_surface.valid(x, y)) {
                    // Calculate barycentric coordinates for this valid pixel.
                    // ... (48.16) / (24.8) = (24.8)
                    alpha = (static_cast<long>(edgef(x << 4, y << 4, x2, y2, x3, y3)) << 8) / 
                        alpha_den;
                    beta = (static_cast<long>(edgef(x << 4, y << 4, x3, y3, x1, y1)) << 8) / 
                        beta_den;
                    gamma = (1 << 8) - alpha - beta;

                    // Calculate the pixel depth. (24.8 * 24.8) -> (48.16)
                    pixel_depth = static_cast<long>(z1) * static_cast<long>(alpha) + 
                                  static_cast<long>(z2) * static_cast<long>(beta) + 
                                  static_cast<long>(z3) * static_cast<long>(gamma);
                    // (48.16) -> (56.8) -> (24.8)
                    pixel_depth = static_cast<int>(pixel_depth >> 8);

                    // Shall we render this pixel? Are we in front or back?
                    // Are we doing buffer testing?
                    if(m_z_buffer != NULL) {
                        // Test against the z-buffer.
                        if(pixel_depth > 0 && pixel_depth < m_z_buffer[m_z_buffer_height * y + x]) {
                            // Draw the pixel and update the z-buffer.
                            m_z_buffer[m_z_buffer_height * y + x] = pixel_depth;
                            // Calculate plain color.
                            QColor color = getColor(alpha, beta, gamma);
                            // Calculate illumination color.
                            color = getIlluminatedColor(p_n1, p_n2, p_n3, alpha, beta, gamma, color);
                            p_surface.setPixel(x, y, color.rgb());
                        }
                    }
                    else {
                        // No depth buffer. Print the pixel with the weighted color.
                        p_surface.setPixel(x, y, getColor(alpha, beta, gamma).rgb());
                    }
                }
            } else if(after_edge == true) {
                // We are past the left edge. Skip next loops.
                break;
            }

            // (24.8)
            cx1 -= fdy12;
            cx2 -= fdy23;
            cx3 -= fdy31;
        }

        // (24.8)
        cy1 += fdx12;
        cy2 += fdx23;
        cy3 += fdx31;
    }

}

}
