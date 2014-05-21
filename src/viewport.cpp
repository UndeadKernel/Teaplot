#include "viewport.h"

#include <QDebug>
#include <QPainter>
#include <QColor>


//------------------------------------------------------------------------------
// Public Functions

Viewport::Viewport(QWidget *parent/* = 0*/)
    : QWidget(parent)
    , m_render_surface(NULL)
{
    
}

void Viewport::show()
{
    //qDebug() << "Viewport show event!";

    QWidget::show();
}

void Viewport::resizeEvent(QResizeEvent *p_event)
{
    //qDebug() << "Viewport resize event!";

    setupRenderSurface(width(), height());
    emit widgetResized();
}

void Viewport::paintEvent(QPaintEvent *p_event)
{
    //qDebug() << "Viewport paint event!";

    renderSurface();
}

void Viewport::setupRenderSurface(int p_w, int p_h)
{
    if(m_render_surface != NULL) {
        // We already have a render area, so delete it first :)
        delete m_render_surface;
    }

    //qDebug() << "Render area (w, h): " << p_w << ", " << p_h;

    // Create our QImage.
    m_render_surface = new QImage(p_w, p_h, QImage::Format_RGB32);
}

void Viewport::renderSurface()
{
    if(m_render_surface == NULL) {
        return;
    }

    // Call in the painter. Tell him the canvas is that ugly colorless widget.
    QPainter painter(this);
    // Draw painter, draw!
    //m_render_surface->fill(QColor(0, 0, 0).rgb());
    painter.drawImage(QPoint(0,0), *m_render_surface);
}

QImage *Viewport::getRenderSurface()
{
    return m_render_surface;
}

//------------------------------------------------------------------------------
// Private Functions
