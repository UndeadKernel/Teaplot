#include "shape.h"
#include "vector.h"
#include "matrix.h"
#include "screen.h"

#include <stdexcept>


namespace tgl
{

//------------------------------------------------------------------------------
// Public Functions

Shape::Shape()
    : m_z_buffer(NULL)
    , m_z_buffer_width(0)
    , m_z_buffer_height(0)
{

}

Shape::~Shape()
{
    deleteVertices();
}

bool Shape::addVertex(Vector *p_vertex, Vector *p_color /*= NULL*/, 
        Vector *p_normal/* = NULL*/)
{
    int vertex_count = m_vertices.size();

    // Make sure we don't add more vertices than the allowed.
    if(vertex_count == requiredVertices()) {
        throw std::length_error("This shape has enough vertices already.");
    }

    m_vertices.push_back(p_vertex);
    m_colors.push_back(p_color);
    m_normals.push_back(p_normal);
    m_vertices_eye_space.push_back(Vector());

    // Are we missing points or not?
    if(++vertex_count == requiredVertices()) {
        // We are full now.
        return true;
    } else {
        // We are still missing points.
        return false;
    }
}

void Shape::deleteVertices()
{
    int vertex_count = m_vertices.size();
    Vector *vector;

    // Delete the vertices of this shape.
    for(int i = 0; i < vertex_count; i++) {
        vector = m_vertices.back();
        m_vertices.pop_back();
        delete vector;
    }

    // Delete all the colors we have stored for the vertices.
    for(int i = 0; i < vertex_count; i++) {
        vector = m_colors.back();
        m_colors.pop_back();
        if(vector != NULL) {
            delete vector;
        }
    }

    // Delete all the normals we have stored for the vertices.
    for(int i = 0; i < vertex_count; i++) {
        vector = m_normals.back();
        m_normals.pop_back();
        if(vector != NULL) {
            delete vector;
        }
    }
}

Vector *Shape::getVertex(int p_index)
{
    if(p_index > requiredVertices()) {
        throw std::out_of_range("This shape doesn't have that many points.");
    }

    return m_vertices.at(p_index);
}

Vector *Shape::getVertexNormal(int p_index)
{
    if(p_index > requiredVertices()) {
        throw std::out_of_range("This shape doesn't have that many normals.");
    }

    return m_normals.at(p_index);
}

void Shape::setZBuffer(int *p_z_buffer, unsigned int p_width, 
       unsigned int p_height)
{
    m_z_buffer = p_z_buffer;
    m_z_buffer_width = p_width;
    m_z_buffer_height = p_height;
}

void Shape::unsetZBuffer()
{
    m_z_buffer = NULL;
    m_z_buffer_width = 0;
    m_z_buffer_height = 0;
}


//------------------------------------------------------------------------------
// Protected Functions

Vector Shape::transformVertex(unsigned int p_vertex_index,
    Matrix &p_transformation, Screen &p_screen)
{
    Vector &current_vertex = *getVertex(p_vertex_index);

    //ModelView - Projection transformation
    Vector transformed_vertex = p_transformation * current_vertex;
    // Store a copy of the transformed vertex.
    m_vertices_eye_space[p_vertex_index] = transformed_vertex;

    //Perspective Divide
    transformed_vertex.perspectiveDivide();

    // Viewport transformation.
    Vector screen_coords = transformed_vertex.viewportTransformation(p_screen);

    return screen_coords;
}

Vector Shape::transformNormal(unsigned int p_vertex_index,
        Matrix &p_transformation)
{
    Vector &current_normal = *getVertexNormal(p_vertex_index);

    //ModelView - Projection transformation
    Vector transformed_normal = p_transformation * current_normal;

    // Normalize the normal.
    transformed_normal /= transformed_normal.len();

    return transformed_normal;
}

}
