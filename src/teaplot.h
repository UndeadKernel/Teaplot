#ifndef _TEAPLOT_H_
#define _TEAPLOT_H_

#include "mainwindow.h"
#include "tgl/objectparser.h"

class QObject;


class TeaPlot: public QObject
{

    Q_OBJECT

  public slots:
    // Render the 3D object into the viewport.
    void draw3dObject();

  public:
    TeaPlot();
    // Window related functions.
    void showMainWindow();
    // Parse selected obj file.
    void parseObjFile();
    // Set the user's desired projection.
    void setProjection();
    // Translation coordinates for the obj to render.
    void setTranslation();
    // Illumination settings for the obj to render.
    void setIllumination();
    // Plot the obj to the screen!
    void renderObj();
    

  private:
    MainWindow m_mainwindow;
    tgl::ObjectParser *m_parser;
};


#endif /* _TEAPLOT_H_ */
