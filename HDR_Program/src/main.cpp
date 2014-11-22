#include <iostream>

#include "Image.h"
#include "ImageIO.h"
#include "DisplayManager.h"

#include "../glrendering/GlRender.h"

//#define DATA_DIR HDR_DIR"/data"



int main(int argc, char *argv[])
{
    Image test;
    ImageIO testIO;
    testIO.imgLoad(test, HDR_DIR"/data/Lake.hdr");
    testIO.toneMapping(test);

//    test.rgb2hsv();
//    test.hsv2rgb();

//    test.color2gray();

    DisplayManager multipleMonitor;

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

//    testIO.imgSave(test, HDR_DIR"/output/test.png");

//    return 0;

//    QApplication app(argc, argv);

//    QGLFormat gl_profile(QGL::DoubleBuffer | QGL::Rgba | QGL::AlphaChannel);
//    gl_profile.setVersion(3, 3);
//    gl_profile.setProfile(QGLFormat::CoreProfile);
//    QGLFormat::setDefaultFormat(gl_profile);

//    GlRender simple_gl;
//    simple_gl.resize(600,500);
//    simple_gl.show();
//    return app.exec();
}
