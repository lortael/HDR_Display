#include <iostream>

#include "Image.h"
#include "ImageIO.h"
#include "DisplayManager.h"

#include "../glrendering/RenderingWidget.h"

//#define DATA_DIR HDR_DIR"/data"

//enum DISPLAY {CV = 0, GL = 1};

int main(int argc, char *argv[])
{
    Image test;
    ImageIO testIO;
    testIO.imgLoad(test, HDR_DIR"/data/Lake.hdr");
//    testIO.toneMapping(test);

    DisplayManager multipleMonitor;
    DISPLAYMODE current = multipleMonitor.mode();

    QApplication app(argc, argv);
    std::locale::global(std::locale("C"));

    QGLFormat gl_profile(QGL::DoubleBuffer | QGL::Rgba | QGL::AlphaChannel);
    gl_profile.setVersion(3, 3);
    gl_profile.setProfile(QGLFormat::CoreProfile);
    QGLFormat::setDefaultFormat(gl_profile);

    DisplayDevice* mainWindow;
    mainWindow = new DisplayDevice;
    multipleMonitor.addDisplay(mainWindow);
    multipleMonitor.accessDevice(0)->importImage(test);

    test.color2gray();

    DisplayDevice* secondaryWindow;
    secondaryWindow = new DisplayDevice;
    multipleMonitor.addDisplay(secondaryWindow);
    multipleMonitor.accessDevice(1)->importImage(test);

    multipleMonitor.multipleDisplay();

    if (current == GL)
        return app.exec();
    else
        return 0;
}
