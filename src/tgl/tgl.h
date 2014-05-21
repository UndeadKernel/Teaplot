#ifndef _TGL__TGL_H_
#define _TGL__TGL_H_

#include "vector.h"

#include <vector>
#include <list>
#include <map>
#include <QColor>

// Forward declarations.
namespace tgl
{
    class Matrix;
    class Screen;
    class Shape;
}

class QImage;


class Tgl
{
  public:
    // Available Matrices.
    enum eMatrix {MODELVIEW, PROJECTION, MATRICES};
    // Available draw modes for the vertices.
    enum eDrawMode {POINTS, LINES, TRIANGLES};

  public:
    static void init();
    // Activete a certain matrix to do transformations on it.
    static void setActiveMatrix(eMatrix p_m);
    // Functions over shapes.
    static void clearShapes();
    // Transformation functions.
    static void loadIdentity();
    static void translate(double p_x = 0.0f, double p_y = 0.0f, double p_z = 0.0f);
    static void scale(double p_x = 1.0f, double p_y = 1.0f, double p_z = 1.0f);
    static void rotateY(double p_angle);
    // Draw functions.
    static void beginDraw(eDrawMode p_drawmode);
    static void setVertex(double p_x, double p_y, double p_z);
    static void setVertex(tgl::Vector &p_vertex);
    static void setVertexColor(const tgl::Vector &p_color);
    static void setVertexNormal(const tgl::Vector &p_normal);
    static void endDraw();
    static void renderScene(QImage *p_surface);
    // Viewport functions.
    static void setViewport(int p_x = 0, int p_y = 0, int p_w = 0, 
        int p_h = 0, double p_n = 0.0f, double p_f = 1.0f);
    // Projection functions.
    static void setOrtho(double p_left, double p_right, double p_bottom,
        double p_top, double p_near, double p_far);
    static void setFrustum(double p_left, double p_right, double p_bottom,
        double p_top, double p_near, double p_far);
    static void makeFrustum(double fovY, double aspectRatio, double front, double back);
    // Lighting functions.
    static void setLightPosition(const tgl::Vector& p_pos) { m_light_position = p_pos; };
    static tgl::Vector getLightPosition() { return m_light_position; };
    static void setAmbientColor(const QColor &p_color) {m_ambient = p_color; };
    static void setSpecularColor(const QColor &p_color) {m_specular = p_color; };
    static void setDiffuseColor(const QColor &p_color) {m_diffuse = p_color; };
    static QColor getAmbientColor() { return m_ambient; };
    static QColor getDiffuseColor() { return m_diffuse; };
    static QColor getSpecularColor() { return m_specular; };
    static void setAmbientReflectance(double p_ka) {m_ambient_reflectance = p_ka; };
    static double getAmbientReflectance() { return m_ambient_reflectance; };
    static void setShininess(double p_s) { m_shininess = p_s; };
    static double getShininess() { return m_shininess; };
    
    
  private:
    // The current active matrix.
    static eMatrix m_active_matrix;
    // Transformation matrices.
    static std::vector<tgl::Matrix*> m_matrices;
    // Current draw mode.
    static eDrawMode m_active_drawmode;
    // The viewport.
    static tgl::Screen m_viewport;
    // Temporary storage for vertices to be converted into shapes.
    static std::list<tgl::Vector *> m_shape_vertices;
    static unsigned int m_shape_vertex_count;
    // The color of the vertices.
    static std::map<unsigned int, tgl::Vector *> m_vertices_color;
    // The normal of the vertices.
    static std::map<unsigned int, tgl::Vector *> m_vertices_normal;
    // The shapes to draw.
    static std::list<tgl::Shape *> m_shapes;
    // Light things.
    static tgl::Vector m_light_position;
    // Light colors (only one light).
    static QColor m_ambient;
    static QColor m_diffuse;
    static QColor m_specular;
    // Light constants.
    static double m_ambient_reflectance;
    static double m_shininess;


  private:
    // Function that collects the points for a lines.
    static void collectShapes();
    // Return a new shape object based on the current desired shape.
    static tgl::Shape *createNewShape();
};


#endif /* _TGL__TGL_H_ */
