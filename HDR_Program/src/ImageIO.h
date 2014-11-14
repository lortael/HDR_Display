#ifndef IMAGEIO_H
#define IMAGEIO_H

#include "Image.h"

class ImageIO
{
public :

    static void loadImg(Image& dst, std::string const filePath);
    static void saveImg(Image const src, std::string const filePath) const;

    Image toneMapping(Image const src);

private:

protected:

};

#endif IMAGEIO_H
