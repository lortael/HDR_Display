#include <iostream>

#include "Image.h"
#include "ImageIO.h"
#include "DisplayManager.h"

#include "../glrendering/RenderingWidget.h"

//#define DATA_DIR HDR_DIR"/data"

//enum DISPLAY {CV = 0, GL = 1};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::locale::global(std::locale("C"));

    QGLFormat gl_profile(QGL::DoubleBuffer | QGL::Rgba | QGL::AlphaChannel);
    gl_profile.setVersion(3, 3);
    gl_profile.setProfile(QGLFormat::CoreProfile);
    QGLFormat::setDefaultFormat(gl_profile);

    DisplayManager multipleMonitor;

    Image test;
    ImageIO testIO;
    testIO.imgLoad(test, HDR_DIR"/data/Lake.hdr");
    multipleMonitor.initManager(test);

    multipleMonitor.multipleDisplay();

    return app.exec();
}
