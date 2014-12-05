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

    //Save an image according to the desired format (.ppm, .pgm, .png)
    void imgSave(Image const &src, const std::string filename);

    void imgLoad(Image& img, QString filename);

    void loadPng(Image& png_img, const std::string filename);

    void savePng(Image const & img, const std::string filename);

    //CPU tone-mapping in order to save an image
    void toneMapping(Image &src);

private:

protected:

};

#endif //IMAGEIO_H_INCLUDED
