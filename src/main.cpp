// author: Carlos Garcia Cordero (s1065405)

#include "teaplot.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TeaPlot teaplot;

    teaplot.showMainWindow();
    teaplot.draw3dObject();

    return app.exec();
}
