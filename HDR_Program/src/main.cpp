#include <iostream>

#include "Image.h"
#include "ImageIO.h"
#include "DisplayManager.h"

//#include "../glrendering/GlRender.h"
#include "../glrendering/RenderingWidget.h"

//#define DATA_DIR HDR_DIR"/data"

enum DISPLAY {CV = 0, GL = 1};

int main(int argc, char *argv[])
{
    DISPLAY current(GL);

    Image test;
    ImageIO testIO;
    testIO.imgLoad(test, HDR_DIR"/data/Lake.hdr");
//    testIO.toneMapping(test);

    if (current == CV)
    {
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

        testIO.imgSave(test, HDR_DIR"/output/test.png");

        return 0;
    }
    else
    {
//        GlRender test;
//        test.resize(800,600);
//        test.initRender(argc, argv);

        QApplication app(argc, argv);
        std::locale::global(std::locale("C"));

        QGLFormat gl_profile(QGL::DoubleBuffer | QGL::Rgba | QGL::AlphaChannel);
        gl_profile.setVersion(3, 3);
        gl_profile.setProfile(QGLFormat::CoreProfile);
        QGLFormat::setDefaultFormat(gl_profile);

        RenderingWidget simple_gl;
        simple_gl.loadImage(test);
        simple_gl.resize(1920,1080);
        simple_gl.show();

        return app.exec();
    }
}
