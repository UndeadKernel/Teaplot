#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "shape.h"
#include "vector.h"
#include "tgl.h"

#include <cmath>
#include <QColor>


// Forward declarations.
class QImage;


namespace tgl
{

// Forward declarations.
class Screen;


class Triangle: public Shape
{
  public:
    Triangle();
    // The required points for this shape.
    virtual int requiredVertices();
    virtual void render(Matrix &p_transformation, 
        Screen &p_screen, QImage &p_surface);

  private:
    // Bounding boxes for precalculated triangles.
    int m_min_x;
    int m_min_y;
    int m_max_x;
    int m_max_y;

    void rasterize(const Vector &p_p1, const Vector &p_p2, 
        const Vector &p_p3, const Vector &p_n1, const Vector &p_n2, 
        const Vector &p_n3, QImage &p_surface);
    // Calculate edge function for Barycentric coords.
    // ... Input -> fixed points (28.4)
    // ... Output -> fixed point (24.8)
    inline int edgef(long x, long y, long x_a, long y_a, 
        long x_b, long y_b);
    // Round helper.
    inline int round(double p_r);
    // Calculate the desired color of a point. (24.8)
    inline QColor getColor(int alpha, int beta, int gamma);
    // Calculate the illuminated color. (24.8)
    inline QColor getIlluminatedColor(const Vector &p_n1, const Vector &p_n2, 
        const Vector &p_n3, int alpha, int beta, int gamma, const QColor &p_color);

};


//------------------------------------------------------------------------------
// Inline Functions

int Triangle::edgef(long x, long y, long x_a, long y_a, 
    long x_b, long y_b) {
    // Return (24.8) fixed point.
    // long t1 = (y_a - y_b)*x;
    // long t2 = (x_b - x_a)*y;
    // long t3 = x_a*y_b;
    // long t4 = x_b*y_a;

    // return t1 + t2 + t3 - t4;

    return (y_a - y_b)*x + (x_b - x_a)*y + x_a*y_b - x_b*y_a;
}


int Triangle::round(double p_r) { 
    double tmp = (p_r > 0.0) ? std::floor(p_r + 0.5) : std::ceil(p_r - 0.5);
    return tmp;
}

// Parameters are supplied in fixed point (24.8)
QColor Triangle::getColor(int alpha, int beta, int gamma)
{
    Vector *c1;
    Vector *c2;
    Vector *c3;
    Vector white(255, 255, 255);
    // Fixed point (24.8)
    int color_r;
    int color_g;
    int color_b;

    c1 = m_colors.at(0);
    c2 = m_colors.at(1);
    c3 = m_colors.at(2);

    // Check if these colors exist, or replace them with white.
    if(c1 == NULL) c1 = &white;
    if(c2 == NULL) c2 = &white;
    if(c3 == NULL) c3 = &white;

    // Calculate the colors given the barycentric coordinates.
    color_r = ((int)(*c1)[0] * alpha) +
              ((int)(*c2)[0] * beta) +
              ((int)(*c3)[0] * gamma);

    color_g = ((int)(*c1)[1] * alpha) +
              ((int)(*c2)[1] * beta) +
              ((int)(*c3)[1] * gamma);

    color_b = ((int)(*c1)[2] * alpha) +
              ((int)(*c2)[2] * beta) +
              ((int)(*c3)[2] * gamma);

    return QColor(color_r >> 8, color_g >> 8, color_b >> 8);
}

// Parameters are supplied in fixed point (24.8)
QColor Triangle::getIlluminatedColor(const Vector &p_n1, 
    const Vector &p_n2, const Vector &p_n3,
    int alpha, int beta, int gamma, const QColor &p_color)
{
    // Transform from fixed point to floating point.
    double d_alpha = (double)alpha/(1 << 8);
    double d_beta = (double)beta/(1 << 8);
    double d_gamma = (double)gamma/(1 << 8);

    // Get the vertices in eye space.
    Vector &p1 = m_vertices_eye_space.at(0);
    Vector &p2 = m_vertices_eye_space.at(1);
    Vector &p3 = m_vertices_eye_space.at(2);

    // Interpolate to get the pixel position in eye space.
    Vector pixel_position;
    pixel_position[0] = p1[0]*d_alpha + p2[0]*d_beta + p3[0]*d_gamma;
    pixel_position[1] = p1[1]*d_alpha + p2[1]*d_beta + p3[1]*d_gamma;
    pixel_position[2] = p1[2]*d_alpha + p2[2]*d_beta + p3[2]*d_gamma;

    // Interpolate the vertex normals for this pixel.
    Vector pixel_normal;
    pixel_normal[0] = p_n1[0]*d_alpha + p_n2[0]*d_beta + p_n3[0]*d_gamma;
    pixel_normal[1] = p_n1[1]*d_alpha + p_n2[1]*d_beta + p_n3[1]*d_gamma;
    pixel_normal[2] = p_n1[2]*d_alpha + p_n2[2]*d_beta + p_n3[2]*d_gamma;
    
    double red = 0;//= p_color.redF();
    double green = 0;// = p_color.greenF();
    double blue = 0;// = p_color.blueF();

    // Ambient.
    QColor ambient = Tgl::getAmbientColor();
    double ka = Tgl::getAmbientReflectance();
    red += ka * p_color.redF();
    green += ka * p_color.greenF();
    blue += ka * p_color.blueF();

    // Diffuse
    QColor diffuse = Tgl::getDiffuseColor();
    Vector light_direction = Tgl::getLightPosition() - pixel_position;
    light_direction /= light_direction.len(); // Normalize.
    double diffuse_factor = std::max(0.0, pixel_normal.dot(light_direction));
    red += p_color.redF() * diffuse.redF() * diffuse_factor;
    green += p_color.greenF() * diffuse.greenF() * diffuse_factor;
    blue += p_color.blueF() * diffuse.blueF() * diffuse_factor;

    // Specular
    QColor specular = Tgl::getSpecularColor();
    double shininess = Tgl::getShininess();
    Vector halfway = light_direction - pixel_position;
    halfway /= halfway.len(); // Normalize
    double tmp = std::max(0.0, pixel_normal.dot(halfway));
    // Approximate the shininess to speed things up a bit.
    double specular_factor = tmp / (shininess - tmp * shininess + tmp); 
    red += (p_color.redF() * specular.redF()) * specular_factor;
    green += (p_color.greenF() * specular.greenF()) * specular_factor;
    blue += (p_color.blueF() * specular.blueF()) * specular_factor;

    // Clamp values.
    if(red > 1.0) red = 1.0;
    if(green > 1.0) green = 1.0;
    if(blue > 1.0) blue = 1.0;
    if(red < 0.0) red = 0.0;
    if(green < 0.0) green = 0.0;
    if(blue < 0.0) blue = 0.0;

    QColor final_color;
    final_color.setRedF(red);
    final_color.setGreenF(green);
    final_color.setBlueF(blue);
   
    return final_color;
}

}

#endif /* _TRIANGLE_H_ */
