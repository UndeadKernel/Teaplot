/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created: Mon Dec 19 15:45:59 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QGroupBox *gb_options;
    QGridLayout *gridLayout_3;
    QToolBox *tb_options;
    QWidget *page_2;
    QGridLayout *gridLayout_5;
    QLabel *label_2;
    QComboBox *cb_projection;
    QSpacerItem *verticalSpacer_2;
    QFrame *line_3;
    QFrame *line_4;
    QLabel *label_4;
    QSlider *s_scale;
    QFrame *line_7;
    QLabel *label_5;
    QSlider *s_horizontal;
    QLabel *label_6;
    QSlider *s_vertical;
    QLabel *label_7;
    QSlider *s_depth;
    QFrame *line_10;
    QLabel *label_8;
    QSlider *s_rotatey;
    QFrame *line_8;
    QWidget *page_1;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QComboBox *cb_lines;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QFrame *line_2;
    QWidget *page_3;
    QGridLayout *gridLayout_6;
    QFrame *line_5;
    QLabel *label_3;
    QComboBox *cb_mesh;
    QFrame *line_6;
    QSpacerItem *verticalSpacer_3;
    QWidget *page_4;
    QGridLayout *gridLayout_8;
    QFrame *line_11;
    QLabel *label_9;
    QSlider *s_lightx;
    QLabel *label_10;
    QSlider *s_lighty;
    QLabel *label_11;
    QSlider *s_lightz;
    QFrame *line_12;
    QLabel *label_12;
    QSlider *s_lightambient;
    QLabel *label_13;
    QSlider *s_lightshininess;
    QFrame *line_13;
    QLabel *label_14;
    QPushButton *b_diffuse;
    QLabel *label_15;
    QPushButton *b_specular;
    QFrame *line_9;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *gb_viewport;
    QVBoxLayout *verticalLayout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(1024, 768));
        MainWindow->setAutoFillBackground(false);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gb_options = new QGroupBox(centralwidget);
        gb_options->setObjectName(QString::fromUtf8("gb_options"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gb_options->sizePolicy().hasHeightForWidth());
        gb_options->setSizePolicy(sizePolicy1);
        gb_options->setMinimumSize(QSize(240, 0));
        gb_options->setMaximumSize(QSize(240, 16777215));
        gb_options->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gridLayout_3 = new QGridLayout(gb_options);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tb_options = new QToolBox(gb_options);
        tb_options->setObjectName(QString::fromUtf8("tb_options"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tb_options->sizePolicy().hasHeightForWidth());
        tb_options->setSizePolicy(sizePolicy2);
        tb_options->setAutoFillBackground(false);
        tb_options->setStyleSheet(QString::fromUtf8("\n"
"QToolBox::tab {\n"
"	font-size: 18px;\n"
" }\n"
"\n"
"QToolBox::tab:selected {\n"
"	font-size: 22px;\n"
"	font-weight: bold;\n"
"}\n"
""));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 216, 341));
        gridLayout_5 = new QGridLayout(page_2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_2 = new QLabel(page_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_5->addWidget(label_2, 1, 0, 1, 1);

        cb_projection = new QComboBox(page_2);
        cb_projection->setObjectName(QString::fromUtf8("cb_projection"));

        gridLayout_5->addWidget(cb_projection, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_2, 17, 0, 1, 1);

        line_3 = new QFrame(page_2);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_3, 0, 0, 1, 1);

        line_4 = new QFrame(page_2);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_4, 3, 0, 1, 1);

        label_4 = new QLabel(page_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_5->addWidget(label_4, 4, 0, 1, 1);

        s_scale = new QSlider(page_2);
        s_scale->setObjectName(QString::fromUtf8("s_scale"));
        s_scale->setMinimum(10);
        s_scale->setMaximum(130);
        s_scale->setSingleStep(10);
        s_scale->setValue(50);
        s_scale->setOrientation(Qt::Horizontal);
        s_scale->setTickPosition(QSlider::NoTicks);
        s_scale->setTickInterval(10);

        gridLayout_5->addWidget(s_scale, 5, 0, 1, 1);

        line_7 = new QFrame(page_2);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_7, 6, 0, 1, 1);

        label_5 = new QLabel(page_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_5->addWidget(label_5, 7, 0, 1, 1);

        s_horizontal = new QSlider(page_2);
        s_horizontal->setObjectName(QString::fromUtf8("s_horizontal"));
        s_horizontal->setMinimum(-115);
        s_horizontal->setMaximum(115);
        s_horizontal->setSingleStep(10);
        s_horizontal->setValue(0);
        s_horizontal->setOrientation(Qt::Horizontal);
        s_horizontal->setTickPosition(QSlider::NoTicks);
        s_horizontal->setTickInterval(10);

        gridLayout_5->addWidget(s_horizontal, 8, 0, 1, 1);

        label_6 = new QLabel(page_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_5->addWidget(label_6, 9, 0, 1, 1);

        s_vertical = new QSlider(page_2);
        s_vertical->setObjectName(QString::fromUtf8("s_vertical"));
        s_vertical->setMinimum(-130);
        s_vertical->setMaximum(100);
        s_vertical->setSingleStep(10);
        s_vertical->setValue(-30);
        s_vertical->setOrientation(Qt::Horizontal);
        s_vertical->setTickPosition(QSlider::NoTicks);
        s_vertical->setTickInterval(10);

        gridLayout_5->addWidget(s_vertical, 10, 0, 1, 1);

        label_7 = new QLabel(page_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_5->addWidget(label_7, 11, 0, 1, 1);

        s_depth = new QSlider(page_2);
        s_depth->setObjectName(QString::fromUtf8("s_depth"));
        s_depth->setMinimum(30);
        s_depth->setMaximum(130);
        s_depth->setSingleStep(10);
        s_depth->setValue(70);
        s_depth->setOrientation(Qt::Horizontal);
        s_depth->setTickPosition(QSlider::NoTicks);
        s_depth->setTickInterval(10);

        gridLayout_5->addWidget(s_depth, 12, 0, 1, 1);

        line_10 = new QFrame(page_2);
        line_10->setObjectName(QString::fromUtf8("line_10"));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_10, 13, 0, 1, 1);

        label_8 = new QLabel(page_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_5->addWidget(label_8, 14, 0, 1, 1);

        s_rotatey = new QSlider(page_2);
        s_rotatey->setObjectName(QString::fromUtf8("s_rotatey"));
        s_rotatey->setMaximum(359);
        s_rotatey->setSingleStep(1);
        s_rotatey->setOrientation(Qt::Horizontal);
        s_rotatey->setTickPosition(QSlider::NoTicks);
        s_rotatey->setTickInterval(24);

        gridLayout_5->addWidget(s_rotatey, 15, 0, 1, 1);

        line_8 = new QFrame(page_2);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_8, 16, 0, 1, 1);

        tb_options->addItem(page_2, QString::fromUtf8("Transforms"));
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        page_1->setGeometry(QRect(0, 0, 216, 75));
        sizePolicy2.setHeightForWidth(page_1->sizePolicy().hasHeightForWidth());
        page_1->setSizePolicy(sizePolicy2);
        page_1->setStyleSheet(QString::fromUtf8(""));
        gridLayout_4 = new QGridLayout(page_1);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label = new QLabel(page_1);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 1, 0, 1, 1);

        cb_lines = new QComboBox(page_1);
        cb_lines->setObjectName(QString::fromUtf8("cb_lines"));

        gridLayout_4->addWidget(cb_lines, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 5, 0, 1, 1);

        line = new QFrame(page_1);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line, 0, 0, 1, 1);

        line_2 = new QFrame(page_1);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_2, 4, 0, 1, 1);

        tb_options->addItem(page_1, QString::fromUtf8("Primitives"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setGeometry(QRect(0, 0, 216, 75));
        gridLayout_6 = new QGridLayout(page_3);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        line_5 = new QFrame(page_3);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line_5, 0, 0, 1, 1);

        label_3 = new QLabel(page_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_6->addWidget(label_3, 1, 0, 1, 1);

        cb_mesh = new QComboBox(page_3);
        cb_mesh->setObjectName(QString::fromUtf8("cb_mesh"));

        gridLayout_6->addWidget(cb_mesh, 2, 0, 1, 1);

        line_6 = new QFrame(page_3);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line_6, 3, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_3, 4, 0, 1, 1);

        tb_options->addItem(page_3, QString::fromUtf8("Geometry"));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setGeometry(QRect(0, 0, 216, 397));
        gridLayout_8 = new QGridLayout(page_4);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        line_11 = new QFrame(page_4);
        line_11->setObjectName(QString::fromUtf8("line_11"));
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_11, 0, 0, 1, 1);

        label_9 = new QLabel(page_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_8->addWidget(label_9, 1, 0, 1, 1);

        s_lightx = new QSlider(page_4);
        s_lightx->setObjectName(QString::fromUtf8("s_lightx"));
        s_lightx->setMinimum(-450);
        s_lightx->setMaximum(550);
        s_lightx->setSingleStep(20);
        s_lightx->setPageStep(20);
        s_lightx->setValue(50);
        s_lightx->setSliderPosition(50);
        s_lightx->setOrientation(Qt::Horizontal);

        gridLayout_8->addWidget(s_lightx, 2, 0, 1, 1);

        label_10 = new QLabel(page_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_8->addWidget(label_10, 3, 0, 1, 1);

        s_lighty = new QSlider(page_4);
        s_lighty->setObjectName(QString::fromUtf8("s_lighty"));
        s_lighty->setMinimum(-500);
        s_lighty->setMaximum(500);
        s_lighty->setSingleStep(20);
        s_lighty->setPageStep(20);
        s_lighty->setValue(0);
        s_lighty->setOrientation(Qt::Horizontal);

        gridLayout_8->addWidget(s_lighty, 4, 0, 1, 1);

        label_11 = new QLabel(page_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_8->addWidget(label_11, 5, 0, 1, 1);

        s_lightz = new QSlider(page_4);
        s_lightz->setObjectName(QString::fromUtf8("s_lightz"));
        s_lightz->setMinimum(-350);
        s_lightz->setMaximum(650);
        s_lightz->setSingleStep(20);
        s_lightz->setPageStep(20);
        s_lightz->setSliderPosition(150);
        s_lightz->setOrientation(Qt::Horizontal);

        gridLayout_8->addWidget(s_lightz, 6, 0, 1, 1);

        line_12 = new QFrame(page_4);
        line_12->setObjectName(QString::fromUtf8("line_12"));
        line_12->setFrameShape(QFrame::HLine);
        line_12->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_12, 7, 0, 1, 1);

        label_12 = new QLabel(page_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_8->addWidget(label_12, 8, 0, 1, 1);

        s_lightambient = new QSlider(page_4);
        s_lightambient->setObjectName(QString::fromUtf8("s_lightambient"));
        s_lightambient->setMinimum(0);
        s_lightambient->setMaximum(100);
        s_lightambient->setValue(50);
        s_lightambient->setOrientation(Qt::Horizontal);

        gridLayout_8->addWidget(s_lightambient, 9, 0, 1, 1);

        label_13 = new QLabel(page_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_8->addWidget(label_13, 10, 0, 1, 1);

        s_lightshininess = new QSlider(page_4);
        s_lightshininess->setObjectName(QString::fromUtf8("s_lightshininess"));
        s_lightshininess->setMinimum(1);
        s_lightshininess->setMaximum(50);
        s_lightshininess->setSingleStep(1);
        s_lightshininess->setPageStep(1);
        s_lightshininess->setValue(10);
        s_lightshininess->setOrientation(Qt::Horizontal);

        gridLayout_8->addWidget(s_lightshininess, 11, 0, 1, 1);

        line_13 = new QFrame(page_4);
        line_13->setObjectName(QString::fromUtf8("line_13"));
        line_13->setFrameShape(QFrame::HLine);
        line_13->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_13, 12, 0, 1, 1);

        label_14 = new QLabel(page_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_8->addWidget(label_14, 13, 0, 1, 1);

        b_diffuse = new QPushButton(page_4);
        b_diffuse->setObjectName(QString::fromUtf8("b_diffuse"));

        gridLayout_8->addWidget(b_diffuse, 14, 0, 1, 1);

        label_15 = new QLabel(page_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_8->addWidget(label_15, 15, 0, 1, 1);

        b_specular = new QPushButton(page_4);
        b_specular->setObjectName(QString::fromUtf8("b_specular"));

        gridLayout_8->addWidget(b_specular, 16, 0, 1, 1);

        line_9 = new QFrame(page_4);
        line_9->setObjectName(QString::fromUtf8("line_9"));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_9, 17, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer_4, 18, 0, 1, 1);

        tb_options->addItem(page_4, QString::fromUtf8("Illumination"));

        gridLayout_3->addWidget(tb_options, 0, 0, 1, 1);


        gridLayout->addWidget(gb_options, 0, 0, 1, 1);

        gb_viewport = new QGroupBox(centralwidget);
        gb_viewport->setObjectName(QString::fromUtf8("gb_viewport"));
        verticalLayout = new QVBoxLayout(gb_viewport);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        gridLayout->addWidget(gb_viewport, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tb_options->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TeaPlot", 0, QApplication::UnicodeUTF8));
        gb_options->setTitle(QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "<b>Projection</b>", 0, QApplication::UnicodeUTF8));
        cb_projection->clear();
        cb_projection->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Orthogonal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Frustum", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("MainWindow", "<b>Scale</b>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">X displacement</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Y displacement</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Z displacement</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Y rotation</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        tb_options->setItemText(tb_options->indexOf(page_2), QApplication::translate("MainWindow", "Transforms", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "<b>Render Primitive</b>", 0, QApplication::UnicodeUTF8));
        cb_lines->clear();
        cb_lines->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Triangles", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Points", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Lines", 0, QApplication::UnicodeUTF8)
        );
        tb_options->setItemText(tb_options->indexOf(page_1), QApplication::translate("MainWindow", "Primitives", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "<b>Mesh</b>", 0, QApplication::UnicodeUTF8));
        cb_mesh->clear();
        cb_mesh->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "teapot.obj", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "monkey.obj", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "fan.obj", 0, QApplication::UnicodeUTF8)
        );
        tb_options->setItemText(tb_options->indexOf(page_3), QApplication::translate("MainWindow", "Geometry", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "<b>X Position</b>", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "<b>Y Position</b>", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "<b>Z Position</b>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "<b>Ambient Factor</b>", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "<b>Shininess</b>", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Diffuse Color</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        b_diffuse->setText(QApplication::translate("MainWindow", "Choose Color", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "<b>Specular Color</b>", 0, QApplication::UnicodeUTF8));
        b_specular->setText(QApplication::translate("MainWindow", "Choose Color", 0, QApplication::UnicodeUTF8));
        tb_options->setItemText(tb_options->indexOf(page_4), QApplication::translate("MainWindow", "Illumination", 0, QApplication::UnicodeUTF8));
        gb_viewport->setTitle(QApplication::translate("MainWindow", "Viewport", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
