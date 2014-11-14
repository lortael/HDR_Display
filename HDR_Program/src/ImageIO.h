#ifndef IMAGEIO_H
#define IMAGEIO_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Image.h"

class ImageIO
{
public :

    void loadImg(Image dst, std::string const filePath);
    void saveImg(Image const src, std::string const filePath) const;

    Image toneMapping(Image const src);

private:

protected:

};

#endif IMAGEIO_H
