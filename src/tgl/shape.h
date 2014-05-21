#ifndef _TGL__SHAPE_H_
#define _TGL__SHAPE_H_

#include <vector>

// Forward declarations.
class QImage;

namespace tgl
{

// Forward declarations.
class Vector;
class Matrix;
class Screen;

class Shape
{
  public:
    Shape();
    virtual ~Shape();
    // Ammount of required points for this shape.
    virtual int requiredVertices() = 0;
    // Each shape should know how to render itself.
    virtual void render(Matrix &p_transformation, 
        Screen &p_screen, QImage &p_surface) = 0;
    // Add consecutive points to the shape.
    // ... return false if more points needed.
    // ... return true if no more points are needed.
    virtual bool addVertex(Vector *p_vertex, Vector *p_color = NULL, 
        Vector *p_normal = NULL);
    virtual void deleteVertices();
    virtual Vector *getVertex(int p_index);
    virtual Vector *getVertexNormal(int p_index);
    // Enable z-buffer check for rendering this shape.
    virtual void setZBuffer(int *p_z_buffer, unsigned int p_width, 
        unsigned int p_height);
    virtual void unsetZBuffer();


  protected:
    std::vector<Vector *> m_vertices;
    std::vector<Vector *> m_colors;
    std::vector<Vector *> m_normals;
    int *m_z_buffer; // Fixed point z-buffer (2.30)
    unsigned int m_z_buffer_width;
    unsigned int m_z_buffer_height;
    // Vertices transformed into eye space.
    std::vector<Vector> m_vertices_eye_space;

  protected:
    // Transform shape coordinates with the specified matrix
    // ... transformation.
    Vector transformVertex(unsigned int p_vertex_index,
        Matrix &p_transformation, Screen &p_screen);
    // Special transformation for the normal vectors (into eye space).
    Vector transformNormal(unsigned int p_vertex_index,
        Matrix &p_transformation);
};

}

#endif /* _TGL__SHAPE_H_ */
