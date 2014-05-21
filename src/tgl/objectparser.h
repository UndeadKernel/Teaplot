#ifndef _OBJECTPARSER_H_
#define _OBJECTPARSER_H_

#include <vector>
#include <string>
#include <map>
#include <list>


namespace tgl
{

class Vector;

class ObjectParser
{
  public:
    ObjectParser();
    ~ObjectParser();
    // Set a filename to parse.
    void parseObjFile(const char *p_filename);
    std::string getObjFilename();
    // Vertices operations.
    int getVertexCount();
    Vector *getVertex(int p_vertex_index);
    // Triangle operations.
    int getTriangleCount();
    Vector *getTriangleVertex(int p_face, int p_vertex);
    const Vector *getTriangleVertexColor(int p_face, int p_vertex);
    const Vector *getTriangleVertexNormal(int p_face, int p_vertex);


  private:
    std::vector<Vector *> m_vertices;
    std::vector<Vector *> m_faces;
    std::map<unsigned int, Vector *> m_vertex_colors;
    // Normals for a given face.
    std::vector<Vector *> m_face_normals;
    // Face normals next to a particular vertex.
    std::map<unsigned int, std::list<Vector *> > m_vertex_neighbour_normals;
    // Normals of the single vertices.
    std::map<unsigned int, Vector *> m_vertex_normals;
    std::string m_filename;

  private:
    void calculateTriangleNormals();
    void calculateVertexNormals();
    
};


}


#endif /* _OBJECTPARSER_H_ */
