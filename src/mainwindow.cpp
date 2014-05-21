#include "mainwindow.h"
#include "viewport.h"

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QSizePolicy>
#include <QString>
#include <QColorDialog>


//--------------------------------------------------------------------------------
// Public Functions

MainWindow::MainWindow(QWidget *parent/* = 0*/)
  : QMainWindow(parent)
  , m_viewport(NULL)
  , m_diffuse_color(255,255,255)
  , m_specular_color(255,255,255)
{
    // Setup the main window.
    m_ui.setupUi(this);

    // Setup the viewport widget.
    m_viewport = new Viewport(m_ui.gb_viewport);
    m_ui.gb_viewport->layout()->addWidget(m_viewport);
    m_viewport->show();
}

MainWindow::~MainWindow()
{
    if(m_viewport) {
        delete m_viewport;
    }
}

void MainWindow::show()
{
    // Show the screen as normal.
    QMainWindow::show();
    
    // Connect the signals for all the options.
    connectSignals();
}

void MainWindow::updateViewport()
{
    if(m_viewport) {
        // Schedule a repaint event in the viewport widget.
        m_viewport->update();
    }
}

QImage *MainWindow::getRenderSurface()
{
    return m_viewport->getRenderSurface();
}

QString MainWindow::getLineAlgorithmOption()
{
    return m_ui.cb_lines->currentText();
}

QString MainWindow::getProjectionOption()
{
    return m_ui.cb_projection->currentText();
}

QString MainWindow::getMeshOption()
{
    return m_ui.cb_mesh->currentText();
}

int MainWindow::getScaleOption()
{
    return m_ui.s_scale->value();
}

int MainWindow::getHorizontalOption()
{
    return m_ui.s_horizontal->value();
}

int MainWindow::getVerticalOption()
{
    return m_ui.s_vertical->value();
}

int MainWindow::getDepthOption()
{
    return m_ui.s_depth->value();
}

int MainWindow::getRotateYOption()
{
    return m_ui.s_rotatey->value();
}

int MainWindow::getLightX()
{
    return m_ui.s_lightx->value();
}

int MainWindow::getLightY()
{
    return m_ui.s_lighty->value();
}

int MainWindow::getLightZ()
{
    return m_ui.s_lightz->value();
}

int MainWindow::getLightAmbient()
{
    return m_ui.s_lightambient->value();
}

int MainWindow::getLightShininess()
{
    return m_ui.s_lightshininess->value();
}

QColor MainWindow::getDiffuseColor()
{
    return m_diffuse_color;
}

QColor MainWindow::getSpecularColor()
{
    return m_specular_color;
}


//--------------------------------------------------------------------------------
// Private Functions

void MainWindow::connectSignals()
{
    // Selected line style.
    QObject::connect(m_ui.cb_lines, SIGNAL(currentIndexChanged(int)),
        this, SIGNAL(optionChanged()));
    // Selected Projection.
    QObject::connect(m_ui.cb_projection, SIGNAL(currentIndexChanged(int)),
        this, SIGNAL(optionChanged()));
    // Selected Mesh.
    QObject::connect(m_ui.cb_mesh, SIGNAL(currentIndexChanged(int)),
        this, SIGNAL(optionChanged()));
    // Rerender whenever the size of the render surface changes.
    QObject::connect(m_viewport, SIGNAL(widgetResized()),
        this, SIGNAL(optionChanged()));
    // Scale
    QObject::connect(m_ui.s_scale, SIGNAL(valueChanged(int)),
        this, SIGNAL(optionChanged()));
    // Horizontal
    QObject::connect(m_ui.s_horizontal, SIGNAL(valueChanged(int)),
        this, SIGNAL(optionChanged()));
    // Vertical
    QObject::connect(m_ui.s_vertical, SIGNAL(valueChanged(int)),
        this, SIGNAL(optionChanged()));
    // Depth
    QObject::connect(m_ui.s_depth, SIGNAL(valueChanged(int)),
        this, SIGNAL(optionChanged()));
    // Rotate Y
    QObject::connect(m_ui.s_rotatey, SIGNAL(valueChanged(int)),
        this, SIGNAL(optionChanged()));
    // Light X
    QObject::connect(m_ui.s_lightx, SIGNAL(valueChanged(int)),
        this, SIGNAL(optionChanged()));
    // Light Y
    QObject::connect(m_ui.s_lighty, SIGNAL(valueChanged(int)),
        this, SIGNAL(optionChanged()));
    // Light Z
    QObject::connect(m_ui.s_lightz, SIGNAL(valueChanged(int)),
        this, SIGNAL(optionChanged()));
    // Light Ambient
    QObject::connect(m_ui.s_lightambient, SIGNAL(valueChanged(int)),
        this, SIGNAL(optionChanged()));
    // Light Shininess
    QObject::connect(m_ui.s_lightshininess, SIGNAL(valueChanged(int)),
        this, SIGNAL(optionChanged()));
    // Color buttons.
    QObject::connect(m_ui.b_diffuse, SIGNAL(clicked()), this, 
        SLOT(setDiffuseColor()));
    QObject::connect(m_ui.b_specular, SIGNAL(clicked()), this, 
        SLOT(setSpecularColor()));
}

void MainWindow::setDiffuseColor()
{
    m_diffuse_color = QColorDialog::getColor(m_diffuse_color, 
        this, "Select the Diffuse Color");

    if(m_diffuse_color.isValid()) {
        const QString style_sheet = QString("QPushButton {"
            "background-color: %1}").arg(m_diffuse_color.name());
        m_ui.b_diffuse->setStyleSheet(style_sheet);
        //m_ui.b_diffuse->setAutoFillBackground(true);
    }
    else {
        // Reset color to white.
        m_diffuse_color = Qt::white;
    }

    emit optionChanged();
}

void MainWindow::setSpecularColor()
{
    m_specular_color = QColorDialog::getColor(m_specular_color, 
        this, "Select the Specular Color");

    if(m_specular_color.isValid()) {
        const QString style_sheet = QString("QPushButton {"
            "background-color: %1}").arg(m_specular_color.name());
        m_ui.b_specular->setStyleSheet(style_sheet);
        //m_ui.b_specular->setAutoFillBackground(true);
    }
    else {
        // Reset color to white.
        m_specular_color = Qt::white;
    }

    emit optionChanged();
}
