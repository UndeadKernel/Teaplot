#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "gui/ui_mainWindow.h"

#include <QMainWindow>
#include <QImage>

class Viewport;
class QString;

class MainWindow: public QMainWindow
{
    Q_OBJECT

  signals:
    void optionChanged();

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    // Overwrite show().
    virtual void show();
    // Capture resize events.
    
    // Tell the viewport to render the surface into the widget.
    void updateViewport();
    // Obtain the render surface our GUI has created.
    QImage *getRenderSurface();
    // Get user options.
    QString getLineAlgorithmOption();
    QString getProjectionOption();
    QString getMeshOption();
    int getScaleOption();
    int getHorizontalOption();
    int getVerticalOption();
    int getDepthOption();
    int getRotateYOption();
    int getLightX();
    int getLightY();
    int getLightZ();
    int getLightAmbient();
    int getLightShininess();
    QColor getDiffuseColor();
    QColor getSpecularColor();


  private:
    Ui::MainWindow m_ui;
    Viewport *m_viewport;
    QColor m_diffuse_color;
    QColor m_specular_color;

  private:
    // Connect all the signals from the options.
    void connectSignals();

  private slots:
    void setDiffuseColor();
    void setSpecularColor();
};

#endif /* _MAINWINDOW_H_ */
