#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include <QWidget>
#include <QImage>
#include <QPaintEvent>


class Viewport: public QWidget
{
    Q_OBJECT

  signals:
    void widgetResized();

  public:
    Viewport(QWidget *parent = 0);
    // Overwrite the default show().
    virtual void show();
    // Overwrite the rezise event to catch the size of the widget.
    virtual void resizeEvent(QResizeEvent *p_event);
    // Overwrite the paint event.
    virtual void paintEvent(QPaintEvent *p_event);
    // Setup the QImage that will be used as our render surface.
    void setupRenderSurface(int p_w, int p_h);
    // Render our surface (QImage) into the desired widget.
    void renderSurface();
    // Give us the surface!!
    QImage *getRenderSurface();


  private:
    QImage *m_render_surface;
};

#endif /* _VIEWPORT_H_ */
