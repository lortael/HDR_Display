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

    /**
     * @brief displays an image on target screen using openCV after applying the CPUprocess (no correction of response curve).
     * @param img, the Image to be displayed.
     * @see CPUprocess()
     * */
    void imgLoad(Image& img, QString filename);

    /**
     * @brief loads an png image using its filename with the lodepng lib.
     * @param img, the destination image.
     * @param filename, the file path of the image to be loaded.
     * */
    void loadPng(Image& png_img, const std::string filename);

    /**
     * @brief saves an png image using its filename with the lodepng lib. If source image is HDR, it must be tone-mapped before saving in png.
     * @param img, the destination image.
     * @param filename, the file path of the image to be loaded.
     * */
    void savePng(Image const & img, const std::string filename);

private:

protected:

};

#endif //IMAGEIO_H_INCLUDED
