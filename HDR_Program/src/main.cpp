//#include <cstdlib>
#include <iostream>
//#include <vector>
//#include <string>

#include "Image.h"
#include "ImageIO.h"

//#define DATA_DIR HDR_DIR"/data"

main()
{
    std::cout << "hello world" << std::endl;
    Image test;
    ImageIO testIO;
    testIO.imgLoad(test, HDR_DIR"/data/Lake.hdr");
    testIO.toneMapping(test);
    test.rgb2hsv();
//    test.hsv2rgb();
    testIO.imgSave(test, HDR_DIR"/output/test.png");

    return 0;
}
