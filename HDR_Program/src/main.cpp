#include <iostream>

#include "Image.h"
#include "ImageIO.h"
#include "DisplayManager.h"
#include "../gui/mainwindow.h"

#include "../glrendering/RenderingWidget.h"
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::locale::global(std::locale("C"));

    QGLFormat gl_profile(QGL::DoubleBuffer | QGL::Rgba | QGL::AlphaChannel);
    gl_profile.setVersion(4, 4);
    gl_profile.setProfile(QGLFormat::CompatibilityProfile);
    QGLFormat::setDefaultFormat(gl_profile);

    DisplayManager multipleMonitor;

    multipleMonitor.initManager(HDR_DIR"/data/Lake.hdr");

    multipleMonitor.multipleDisplay();

//    std::cout << QApplication::desktop()->screenCount() << std::endl;

//    MainWindow controlWindow;
//    controlWindow.show();

    return app.exec();
}
