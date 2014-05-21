#include "objectparser.h"
#include "vector.h"

#include <string>
#include <fstream>
#include <sstream>


namespace tgl
{

//------------------------------------------------------------------------------
// Public Functions

ObjectParser::ObjectParser()
{

}

ObjectParser::~ObjectParser()
{
    // Delete all the vertices we have stored.
    for(unsigned int i = 0; i < m_vertices.size(); i++) {
        delete m_vertices.at(i);
    }
    m_vertices.clear();

    // Delete all the faces we have stored.
    for(unsigned int i = 0; i < m_faces.size(); i++) {
        delete m_faces.at(i);
    }
    m_faces.clear();

    // Delete all colors we have stored.
    for(unsigned int i = 0; i < m_vertex_colors.size(); i++) {
        delete m_vertex_colors.at(i);
    }
    m_vertex_colors.clear();
    
    // Delete face normals.
    for(unsigned int i = 0; i < m_face_normals.size(); i++) {
        delete m_face_normals.at(i);
    }
    m_face_normals.clear();

    // Delete vertices face normals.
    m_vertex_neighbour_normals.clear(); // We just have copies of m_face_normals.

    // Delete vertex normals.
    for(unsigned int i = 0; i < m_vertex_normals.size(); i++) {
        delete m_vertex_normals.at(i);
    }
    m_vertex_normals.clear();
}

void ObjectParser::parseObjFile(const char *p_filename)
{
    std::string line;
    double fx;
    double fy;
    double fz;
    unsigned int uix;
    unsigned int uiy;
    unsigned int uiz;
    unsigned int index;

    m_filename = std::string(p_filename);

    std::ifstream file(p_filename);

    // Parse the file line by line.
    while(std::getline(file, line)) {
        std::stringstream tokens(line);
        // Place were we are holding our parsed data.
        std::string type;
        // See if we can extract a letter.
        tokens >> type;
        if(type.compare("v") == 0) {
            fx = 0;
            fy = 0;
            fz = 0;
            // We have a vertex, extract the x,y and z coordinates.
            tokens >> fx >> fy >> fz;
            m_vertices.push_back(new Vector(fx, fy, fz));
        }
        else if(type.compare("f") == 0) {
            uix = 0;
            uiy = 0;
            uiz = 0;
            // This is a face, extract the vector points.
            tokens >> uix >> uiy >> uiz;
            // Store the face.
            m_faces.push_back(new Vector(uix, uiy, uiz));
        }
        else if(type.compare("#vertexcolor") == 0) {
            // A vertex has been assigned a color.
            index = 0;
            uix = 0;
            uiy = 0;
            uiz = 0;
            // Extract the vertex index and color.
            tokens >> index >> uix >> uiy >> uiz;
            m_vertex_colors[index - 1] = new Vector(uix, uiy, uiz);
        }
    }

    // Calculate the face normals.
    calculateTriangleNormals();
    // Get all the face normals that surround a vertex.
    calculateVertexNormals();
}

std::string ObjectParser::getObjFilename()
{
    return m_filename;
}

int ObjectParser::getVertexCount()
{
    return m_vertices.size();
}

Vector *ObjectParser::getVertex(int p_vertex_index)
{
    return m_vertices.at(p_vertex_index);
}

int ObjectParser::getTriangleCount()
{
    return m_faces.size();
}

Vector *ObjectParser::getTriangleVertex(int p_face, int p_vertex)
{
    Vector *face;
    Vector *vertex;

    face = m_faces.at(p_face); // Obtain the face we want.

    vertex = m_vertices[(*face)[p_vertex] - 1]; // Get the Vertex the index points to.
    
    return vertex;
}

const Vector *ObjectParser::getTriangleVertexColor(int p_face, int p_vertex)
{
    Vector *face;
    unsigned int vertex_index;
    std::map<unsigned int, Vector *>::iterator it;

    face = m_faces.at(p_face);
    vertex_index = (*face)[p_vertex] - 1;

    it = m_vertex_colors.find(vertex_index);

    if(it == m_vertex_colors.end()) {
        // The desired vertex has no color or was not specified.
        return NULL;
    }
    else {
        // The vertex has a color.
        return (*it).second;
    }
}

const Vector *ObjectParser::getTriangleVertexNormal(int p_face, int p_vertex)
{
    Vector *face;
    unsigned int vertex_index;
    std::map<unsigned int, Vector *>::iterator it;

    face = m_faces.at(p_face);
    vertex_index = (*face)[p_vertex] - 1;

    it = m_vertex_normals.find(vertex_index);

    if(it == m_vertex_normals.end()) {
        // The desired vertex has no normal.
        return NULL;
    }
    else {
        // The vertex has a color.
        return (*it).second;
    }
}


//------------------------------------------------------------------------------
// Private Functions

void ObjectParser::calculateTriangleNormals()
{
    unsigned int face_count = m_faces.size();
    Vector *v1;
    Vector *v2;
    Vector *v3;
    Vector *normal;
    double length;
    Vector *face;
    unsigned int vertex_index;
    std::list<Vector *> *vertex_normals;

    for(unsigned int i = 0; i < face_count; ++i) {
        v1 = getTriangleVertex(i,0);
        v2 = getTriangleVertex(i,1);
        v3 = getTriangleVertex(i,2);

        normal = new Vector();
        // (B - A) x (C - A)
        (*normal) = ((*v2) - (*v1)).cross((*v3) - (*v1));
        length = normal->len();
        (*normal) /= length;
        
        // Store the normal vector.
        m_face_normals.push_back(normal);

        // Associate this face normal with all its vertices.
        face = m_faces.at(i);
        for(int j = 0; j < 3; ++j) {
            vertex_index = (*face)[j] - 1;
            // Get the list of normals for this vertex.
            vertex_normals = &m_vertex_neighbour_normals[vertex_index];
            // Add the face normal to the list.
            vertex_normals->push_back(normal);
        }
    }
}

void ObjectParser::calculateVertexNormals()
{
    std::map<unsigned int, std::list<Vector *> >::iterator it;
    std::list<Vector *>::iterator list_it;
    std::list<Vector *> *vertex_normals;
    Vector *vertex_normal;
    unsigned int shared_normals;

    // Iterata through all the neighbouring normals of vertices.
    for(it = m_vertex_neighbour_normals.begin();
        it != m_vertex_neighbour_normals.end();
        ++it) {
        // Get the list of normals.
        vertex_normals = &(it->second);

        vertex_normal = new Vector(0.0, 0.0, 0.0, 0.0);
        shared_normals = 0;
        // Iterate the list of neighbouring normals.
        for(list_it = vertex_normals->begin();
            list_it != vertex_normals->end();
            ++list_it) {
            // Sum the normal vectors of all the neighbouring faces.
            (*vertex_normal) += *(*list_it);
            // Keep record of how many normals have been added.
            ++shared_normals;
        }

        // Average the normal.
        (*vertex_normal) /= shared_normals;
        // Normalize.
        //(*vertex_normal) /= vertex_normal->len();

        // Store the resulting normal.
        m_vertex_normals[it->first] = vertex_normal;
    }
    
}

}
