/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 *
 * */

#ifndef IMAGEIO_H_INCLUDED
#define IMAGEIO_H_INCLUDED

#include "Image.h"
#include <string>
#include <QString>
#include <string>


class ImageIO
{
public :

    ImageIO();

    ~ImageIO();

    //Save an image in png format (see savePng).
    void imgSave(Image const &src, const std::string filename);

    //Load an image (.hdr or .png format).
    void imgLoad(Image& img, QString filename);

    //Load a png image using the lodepng lib (Copyright (C) Lode Vandevenne, see extern folder for details).
    void loadPng(Image& png_img, const std::string filename);

    void savePng(Image const & img, const std::string filename);

private:

protected:

};

#endif //IMAGEIO_H_INCLUDED
