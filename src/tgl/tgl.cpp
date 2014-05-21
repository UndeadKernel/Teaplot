#include "tgl.h"
#include "matrix.h"
#include "vector.h"
#include "screen.h"
#include "shape.h"
#include "line.h"
#include "point.h"
#include "triangle.h"

#include <QImage>
#include <QColor>
#include <cmath>
#include <stdexcept>
#include <map>


using namespace tgl;

//------------------------------------------------------------------------------
// Static Variables

Tgl::eMatrix Tgl::m_active_matrix;
std::vector<tgl::Matrix*> Tgl::m_matrices;
Tgl::eDrawMode Tgl::m_active_drawmode;
tgl::Screen Tgl::m_viewport;
std::list<tgl::Vector *> Tgl::m_shape_vertices;
unsigned int Tgl::m_shape_vertex_count = 0;
std::map<unsigned int, tgl::Vector *> Tgl::m_vertices_color;
std::map<unsigned int, tgl::Vector *> Tgl::m_vertices_normal;
std::list<tgl::Shape *> Tgl::m_shapes;
Vector Tgl::m_light_position(0, 1, -8);
QColor Tgl::m_ambient(255, 255, 255);
QColor Tgl::m_diffuse(255, 255, 255);
QColor Tgl::m_specular(255, 255, 255);
double Tgl::m_ambient_reflectance = 0.5;
double Tgl::m_shininess = 2.0;


//--------------------------------------------------------------------------------
// Public Functions

void Tgl::init()
{
    // Default matrix.
    m_active_matrix = MODELVIEW;

    // Default draw mode.
    m_active_drawmode = POINTS;
    
    // Setup initial matrices.
    for(int i = 0; i < MATRICES; i++) {
        m_matrices.push_back(new Matrix());
    }
}

void Tgl::setActiveMatrix(eMatrix p_m)
{
    m_active_matrix = p_m;
}

void Tgl::clearShapes()
{
    Shape *shape;

    // Delete all the shapes that were created.
    while(!m_shapes.empty()) {
        shape = m_shapes.front();
        delete shape;
        m_shapes.pop_front();
    }
    m_shapes.clear();
}

void Tgl::loadIdentity()
{
    m_matrices.at(m_active_matrix)->loadIdentity();
}

void Tgl::translate(double p_x /*= 0*/, double p_y /*= 0*/, double p_z /*= 0*/)
{
    m_matrices.at(m_active_matrix)->translate(p_x, p_y, p_z);
}

void Tgl::rotateY(double p_angle)
{
    m_matrices.at(m_active_matrix)->rotateY(p_angle);
}

void Tgl::scale(double p_x /*= 1*/, double p_y /*= 1*/, double p_z /*= 1*/)
{
    m_matrices.at(m_active_matrix)->scale(p_x, p_y, p_z);
}

void Tgl::beginDraw(eDrawMode p_drawmode)
{
    m_active_drawmode = p_drawmode;
}

void Tgl::setVertex(double p_x, double p_y, double p_z)
{
    // Add the desired vertex to the set of vertex to convert 
    // ... into shapes.
    m_shape_vertices.push_back(new tgl::Vector(p_x, p_y, p_z));
    ++m_shape_vertex_count;
}

void Tgl::setVertex(Vector &p_vertex)
{
    Vector *new_vector = new Vector(p_vertex[0],
        p_vertex[1],
        p_vertex[2]);

    m_shape_vertices.push_back(new_vector);
    ++m_shape_vertex_count;
}

void Tgl::setVertexColor(const tgl::Vector &p_color)
{
    // The vertex exists?
    if(m_shape_vertex_count == 0) {
        throw std::out_of_range("Tgl:: Color assignment doesn't match a vertex.");
    }

    Vector *color = new Vector(p_color[0],
        p_color[1],
        p_color[2]);

    // Add the color to the last added vertex.
    m_vertices_color[m_shape_vertex_count - 1] = color;
}

void Tgl::setVertexNormal(const tgl::Vector &p_normal)
{
    // The vertex exists?
    if(m_shape_vertex_count == 0) {
        throw std::out_of_range("Tgl:: Normal assignment doesn't match a vertex.");
    }

    Vector *normal = new Vector(p_normal[0],
        p_normal[1],
        p_normal[2]);

    // Add the color to the last added vertex.
    m_vertices_normal[m_shape_vertex_count - 1] = normal;
}

void Tgl::endDraw()
{
    // Create all the shapes indicated by the vertices.
    collectShapes();
}

void Tgl::renderScene(QImage *p_surface)
{
    tgl::Vector new_coords;
    tgl::Matrix modelview_projection;
    tgl::Matrix &modelview = *(m_matrices.at(MODELVIEW));
    tgl::Matrix &projection = *(m_matrices.at(PROJECTION));
    // Fixed point z-buffer (2.30)
    int *z_buffer;
    unsigned int z_buffer_width;
    unsigned int z_buffer_height;

    // Get the multiplication of MODELVIEW and PROJECTION.
    modelview_projection = projection * modelview;

    // Clear the surface.
    p_surface->fill(QColor(0, 0, 0).rgb());

    // Set the z_buffer.
    z_buffer_width = p_surface->width();
    z_buffer_height = p_surface->height();
    z_buffer = new int[z_buffer_width * z_buffer_height];
    // Init the z-buffer to fixed point 1.
    for(unsigned int y = 0; y < z_buffer_height; ++y) {
        for(unsigned int x = 0; x < z_buffer_width; ++x) {
            z_buffer[(z_buffer_height * y) + x] = (1 << 30);
        }
    }

    // Tell all the shapes to render themselves onto the screen.
    for(std::list<tgl::Shape *>::iterator iter = m_shapes.begin(); 
        iter != m_shapes.end(); iter++) {
        (*iter)->setZBuffer(z_buffer, z_buffer_width, z_buffer_height);
        (*iter)->render(modelview_projection, m_viewport, *p_surface);
    }

    // Delete the z-buffer.
    delete z_buffer;
}

void Tgl::setViewport(int p_x/* = 0*/, int p_y/* = 0*/, int p_w/* = 0*/, 
    int p_h/* = 0*/, double p_n/* = 0.0f*/, double p_f/*= 1.0f*/)
{
    m_viewport.setX(p_x);
    m_viewport.setY(p_y);
    m_viewport.setWidth(p_w);
    m_viewport.setHeight(p_h);
    m_viewport.setNear(p_n);
    m_viewport.setFar(p_f);
}

void Tgl::setOrtho(double p_left, double p_right, double p_bottom,
    double p_top, double p_near, double p_far)
{
    Matrix m; // Identity matrix.

    m[0] = 2.0f / (p_right - p_left);
    m[3] = -(p_right + p_left) / (p_right - p_left);

    m[5] = 2.0f / (p_top - p_bottom);
    m[7] = -(p_top + p_bottom) / (p_top - p_bottom);

    m[10] = -2.0f / (p_far - p_near);
    m[11] = -(p_far + p_near) / (p_far - p_near);

    // Multiply the current matrix by the new projection.
    *(m_matrices.at(m_active_matrix)) = *(m_matrices.at(m_active_matrix)) * m;
}

void Tgl::setFrustum(double p_l, double p_r, double p_b,
    double p_t, double p_n, double p_f)
{
    Matrix m;
    m.loadIdentity();

    m[0] = (2 * p_n) / (p_r - p_l);
    m[2] = (p_r + p_l) / (p_r - p_l);

    m[5] = (2 * p_n) / (p_t - p_b);
    m[6] = (p_t + p_b) / (p_t - p_b);

    m[10] = -(p_f + p_n) / (p_f - p_n);
    m[11] = -(2 * p_f * p_n) / (p_f - p_n);
    
    m[14] = -1;
    m[15] = 0;

    // Multiply the current matrix by the new projection.
    *(m_matrices.at(m_active_matrix)) = *(m_matrices.at(m_active_matrix)) * m;
}

void Tgl::makeFrustum(double p_fovy, double p_aspectratio, 
    double p_front, double p_back)
{
    const double DEG2RAD = 3.14159265 / 180.0;

    double tangent = std::tan(p_fovy/2 * DEG2RAD);   // tangent of half fovY
    double height = p_front * tangent;          // half height of near plane
    double width = height * p_aspectratio;      // half width of near plane

    // params: left, right, bottom, top, near, far
    setFrustum(-width, width, -height, height, p_front, p_back);
}


//--------------------------------------------------------------------------------
// Private Functions

void Tgl::collectShapes()
{
    unsigned int vertex_count = m_shape_vertex_count;
    tgl::Vector *current_vertex = NULL;
    tgl::Vector *vertex_color = NULL;
    tgl::Vector *vertex_normal = NULL;
    tgl::Shape *current_shape = NULL;
    std::map<unsigned int, tgl::Vector *>::iterator it;

    // Create the shapes that the vertices supplied represent.
    for(unsigned int i = 0; i < vertex_count; ++i) {
        // Get the vertex with which we are going to work this iteration.
        current_vertex = m_shape_vertices.front();

        // Does this vertex have a color?
        it = m_vertices_color.find(i);
        if(it == m_vertices_color.end()) {
            // No color for you.
            vertex_color = NULL;
        }
        else {
            // It has a color!
            vertex_color = it->second;
            // Remove it from the list.
            m_vertices_color.erase(it);
        }

        // What about a normal?
        it = m_vertices_normal.find(i);
        if(it == m_vertices_normal.end()) {
            // No normal for you.
            vertex_normal = NULL;
        }
        else {
            // Normal found!
            vertex_normal = it->second;
            // Remove the used normal from the list.
            m_vertices_normal.erase(it);
        }

        // Create an empty new shape if there isn't one yet.
        if(current_shape == NULL) {
            current_shape = createNewShape();
            if(current_shape == NULL) {
                throw std::invalid_argument("TGL:: "
                    "Specified shape not implemented!");
            }
        }

        // Add the current vertex to the shape.
        if(current_shape->addVertex(current_vertex, vertex_color, 
                vertex_normal) == true) {
            // We are finished creating the shape.
            m_shapes.push_back(current_shape);
            // Clear the current shape so that we create a new one.
            current_shape = NULL;
        }

        // Go forward one vertex.
        m_shape_vertices.pop_front(); // Remove the front vertex.
    }

    // Check if there were any vertices left over.
    if(current_shape != NULL) {
        // We have left over vertices, delte the shape to avoid memory leaks.
        delete current_shape;
    }

    // Reset the vertices count.
    m_shape_vertex_count = 0;
}

tgl::Shape *Tgl::createNewShape()
{
    switch(m_active_drawmode) {
      case POINTS:
        return new tgl::Point();
        break;
      case LINES:
        return new tgl::Line();
        break;
      case TRIANGLES:
        return new tgl::Triangle();
        break;
    }

    return NULL;
}
