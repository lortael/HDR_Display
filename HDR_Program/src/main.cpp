
#include <iostream>

#include "Image.h"
#include "ImageIO.h"
#include "DisplayManager.h"

//#define DATA_DIR HDR_DIR"/data"

main()
{
    std::cout << "hello world" << std::endl;
    Image test;
    ImageIO testIO;
    testIO.imgLoad(test, HDR_DIR"/data/Lake.hdr");
    testIO.toneMapping(test);

    Image test2;
    test2 = test;

//    DisplayManager multipleMonitor;
//    DisplayDevice* mainWindow;
////    mainWindow = new DisplayDevice(test.height(), test.width(), test, 0);
//    multipleMonitor.addDisplay(mainWindow);
//    multipleMonitor.accessDevice(0)->importImage(test);
//    multipleMonitor.accessDevice(0)->displayImage();

//    test.rgb2hsv();

//    test.hsv2rgb();
    testIO.imgSave(test2, HDR_DIR"/output/test.png");

    return 0;
}
