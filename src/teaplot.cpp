#include "teaplot.h"
#include "tgl/tgl.h"
#include "tgl/vector.h"


//------------------------------------------------------------------------------
// Public Functions

TeaPlot::TeaPlot()
    : m_parser(NULL)
{
    // Setup the graphics library.
    Tgl::init();
}

void TeaPlot::showMainWindow()
{
    m_mainwindow.show();

    // Connect the ui update event to the render object function.
    QObject::connect(&m_mainwindow, SIGNAL(optionChanged()), this, SLOT(draw3dObject()));
}

void TeaPlot::draw3dObject()
{
    // Get the 3D points for the obj file.
    parseObjFile();

    // Setup the projection matrix.
    setProjection();

    // Translate the Obj to render.
    setTranslation();

    // Setup illumination settings.
    setIllumination();

    // Transform all the Obj coordinates to the screen.
    renderObj();
    
}

void TeaPlot::parseObjFile()
{
    QString obj_to_parse;

    obj_to_parse = m_mainwindow.getMeshOption();

    if(m_parser != NULL) {
        // Check if we want to parse the same file.
        if(obj_to_parse.compare(m_parser->getObjFilename().c_str()) == 0) {
            // Skip the obj parsing.
            return;
        }
        // We need a new parsed object.
        delete m_parser;
    }

    // Parse the obj file with the geomerty.
    m_parser = new tgl::ObjectParser();
    m_parser->parseObjFile(obj_to_parse.toAscii());
}

void TeaPlot::setProjection()
{
    Tgl::setActiveMatrix(Tgl::PROJECTION);
    Tgl::loadIdentity();

    if(m_mainwindow.getProjectionOption().compare("Orthogonal") == 0) {
        Tgl::setOrtho(-4.0, 4.0, -4.0, 4.0, 2.0, 11.0);
    }
    else if(m_mainwindow.getProjectionOption().compare("Frustum") == 0) {
        //Tgl::setFrustum(-4.0f, 4.0f, -4.0f, 4.0f, 0.1f, 4.0f);
        Tgl::makeFrustum(90.0, 1.0, 2.0, 9.0);
    }
}

void TeaPlot::setTranslation()
{
    double scale;
    double horizontal;
    double vertical;
    double depth;
    double rotate_y;

    Tgl::setActiveMatrix(Tgl::MODELVIEW);
    Tgl::loadIdentity();

    // Scale value selected by the user.
    scale = static_cast<double>(m_mainwindow.getScaleOption()) / 50.0f;
    Tgl::scale(scale, scale, scale);

    // Rotations.
    rotate_y = static_cast<double>(m_mainwindow.getRotateYOption() * 3.141592 / 180);
    Tgl::rotateY(rotate_y);

    // Move the object based on the user selection.
    horizontal = static_cast<double>(m_mainwindow.getHorizontalOption()) / 50.0;
    vertical = static_cast<double>(m_mainwindow.getVerticalOption()) / 50.0;
    depth = static_cast<double>(m_mainwindow.getDepthOption()) / -10.0;
    Tgl::translate(horizontal, vertical, depth);

}

void TeaPlot::setIllumination()
{
    tgl::Vector light_position;

    // Set the light position.
    light_position[0] = static_cast<double>(m_mainwindow.getLightX()) / 50.0;
    light_position[1] = static_cast<double>(m_mainwindow.getLightY()) / 50.0;
    light_position[2] = static_cast<double>(m_mainwindow.getLightZ()) / 50.0;

    Tgl::setLightPosition(light_position);

    // Set ambient reflectance.
    Tgl::setAmbientReflectance(
        static_cast<double>(m_mainwindow.getLightAmbient()) / 100.0);

    // Set shininess of the object.
    Tgl::setShininess(static_cast<double>(m_mainwindow.getLightShininess()));

    // Set colors for the light.
    Tgl::setDiffuseColor(m_mainwindow.getDiffuseColor());
    Tgl::setSpecularColor(m_mainwindow.getSpecularColor());
}

void TeaPlot::renderObj()
{
    int vertex_count;
    int triangle_count;
    tgl::Vector *current_vertex;
    QImage *render_surface;

    // Erase all the previous shapes we have stored.
    Tgl::clearShapes();

    // Are we drawing only points or lines?
    if(m_mainwindow.getLineAlgorithmOption().compare("Points") == 0) {
        // Get all the vertices of the object we have parsed.
        vertex_count = m_parser->getVertexCount();
        
        // Start to draw points.
        Tgl::beginDraw(Tgl::POINTS);

        // Drawing points:
        for(int i = 0; i < vertex_count; i++) {
            current_vertex = m_parser->getVertex(i);
            Tgl::setVertex((*current_vertex)[0], (*current_vertex)[1],
                (*current_vertex)[2]);
        }

        Tgl::endDraw(); // :D
    }
    else if(m_mainwindow.getLineAlgorithmOption().compare("Lines") == 0) {
        // Get triangle count of the object we have parsed.
        triangle_count = m_parser->getTriangleCount();

        // Start to draw lines.
        Tgl::beginDraw(Tgl::LINES);   
        // For drawing lines out of triangles.
        for(int i = 0; i < triangle_count; i++) {
            // Draw first line. v1 -> v2
            Tgl::setVertex(*(m_parser->getTriangleVertex(i, 0)));
            Tgl::setVertex(*(m_parser->getTriangleVertex(i, 1)));
            // Draw second line v2 -> v3
            Tgl::setVertex(*(m_parser->getTriangleVertex(i, 1)));
            Tgl::setVertex(*(m_parser->getTriangleVertex(i, 2)));
            // Draw third line v3 -> v1
            Tgl::setVertex(*(m_parser->getTriangleVertex(i, 2)));
            Tgl::setVertex(*(m_parser->getTriangleVertex(i, 0)));
        }

        Tgl::endDraw(); // -..-
    }
    else if(m_mainwindow.getLineAlgorithmOption().compare("Triangles") == 0) {
        // Get triangle count of the object we have parsed.
        triangle_count = m_parser->getTriangleCount();

        // Start to draw triangles.
        Tgl::beginDraw(Tgl::TRIANGLES);   

        const tgl::Vector *color;
        const tgl::Vector *normal;
        tgl::Vector *vertex;

        for(int i = 0; i < triangle_count; i++) {
            for(int j = 0; j < 3; ++j) {
                // Vertex
                vertex = m_parser->
                    getTriangleVertex(i, j);
                Tgl::setVertex(*vertex);
                // Color
                color = m_parser->
                    getTriangleVertexColor(i,j);
                if(color != NULL) {
                    Tgl::setVertexColor(*color);
                }
                // Normal
                normal = m_parser->
                    getTriangleVertexNormal(i,j);
                if(normal != NULL) {
                    Tgl::setVertexNormal(*normal);
                }
            }
        }

        Tgl::endDraw(); // c:

    }

    // Get the surface onto which we are going to render.
    render_surface = m_mainwindow.getRenderSurface();

    // Setup the viewport based on the size of the render surface.
    Tgl::setViewport(0, 0,
        render_surface->width(), render_surface->height());

    // Do the magic!!! Dark magic, I tell you.
    Tgl::renderScene(render_surface);
    m_mainwindow.updateViewport();
}

//------------------------------------------------------------------------------
// Private Functions
