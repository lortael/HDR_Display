#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
#include "ImageIO.h"
#include "Image.h"
#include "../extern/lodepng.h"
#include "../extern/rgbe.h"

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

ImageIO::ImageIO()
{

}

ImageIO::~ImageIO()
{

}

void ImageIO::imgLoad(Image& img, QString filename)
{
    float* pixels;
    int height, width;

    if (filename.endsWith(".hdr"))
    {
        FILE* f = fopen(filename.toStdString().c_str(), "rb");

        RGBE_ReadHeader(f, &width, &height, 0);

        img.setHeight(height);
        img.setWidth(width);
        img.initImage();

        pixels = new float[sizeof(float)*3*height*width];
        // Read image data
        RGBE_ReadPixels_RLE(f, reinterpret_cast<float*>(pixels), width, height);

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                float r = pixels[(x + width*y)*3];
                float g = pixels[(x + width*y)*3 + 1];
                float b = pixels[(x + width*y)*3 + 2];
                img.setPixel(x, y, Eigen::Vector4f(r, g, b, 1.f));
            }
        }

        cout << "HDR image loaded" << endl;

    }
    else if (filename.endsWith(".png"))
    {
        loadPng(img, filename.toStdString());
        cout << "png image loaded" << endl;
    }
    else
    {
        cerr << "Wrong format (only .hdr or .png)" << endl;
        exit(EXIT_FAILURE);
    }
}

void ImageIO::loadPng(Image& png_img, const string filename)
{
    vector<unsigned char> png_data;
    vector<unsigned char> raw_data;

    int height, width;

    //load and decode
    lodepng::load_file(png_data, filename);//utilisation de lodepng pour lire le fichier
    unsigned error = lodepng::decode(raw_data, (unsigned int&)width, (unsigned int&)height, png_data);//utilisation de lodepng pour d�compresser les donn�es
    png_data.clear();
    //if there's an error, display it
    if(error)
    {
        cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;
        exit (EXIT_FAILURE);
    }

    vector<unsigned int> rgb_pixel;
    vector<unsigned int> alpha_value;
    rgb_pixel.resize(width*height*3);
    alpha_value.resize(width*height);
    int i = 0;
    int j = 0;
    int k = 0;
    while (i != width*height*3)
    {
        rgb_pixel[i] = (unsigned int)raw_data[j];
        rgb_pixel[i+1] = (unsigned int)raw_data[j+1];
        rgb_pixel[i+2] = (unsigned int)raw_data[j+2];
        alpha_value[k] = (unsigned int)raw_data[j+3];
        i = i+3;
        j = j+4;
        k = k+1;
    }//conversion en int et copie dans l'image 3 canaux + canal alpha
    raw_data.clear();

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float rgb[3];
            for (int col = 0; col < 3; col++)
            {
                rgb[col] = rgb_pixel[(x+y*width)*3 + col]/255.f;
            }
            png_img.setPixel(x, y, Eigen::Vector4f(rgb[0], rgb[1], rgb[2], 1.f*alpha_value[x+y*width]/255.f));
//            delete rgb;
        }
    }
    rgb_pixel.clear();
    alpha_value.clear();
}

void ImageIO::imgSave(Image const & src, const std::string filename)
{
//    string formatS;
//    size_t pos = nom_s.find(".");
//    formatS = nom_s.substr(pos, pos+4);

//    if (formatS == ".ppm")
//    {
//        Save_ppm(img, nom_s);
//    }
//    else if (formatS == ".pgm")
//    {
//        Save_pgm(img, nom_s);
//    }
//    else if (formatS == ".png")
//    {
    savePng(src, filename);
//    }
}

void ImageIO::savePng(Image const & img, const std::string filename)
{
    int height = img.height();
    int width = img.width();

    vector<unsigned char> raw_png;
    vector<int> raw_data;

    raw_data.reserve(height*width*4);

    for (int i = 0; i < height*width*4; i++)
    {
        raw_png.push_back(0);
    }
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            for (int col = 0; col < 3; ++col)
            {
                raw_data[(x+y*width)*4 + col] = static_cast<int>(img.pixel(x, y)[col]*255);

            }

            raw_data[(x+y*width)*4 + 3] = static_cast<int>(img.pixel(x, y)[3]*255);// On stocke l'image dans un format � 4 canaux
        }
    }

    int i = 0;
    while (i != width*height*4)
    {
        raw_png[i] = (unsigned char)raw_data[i];//conversion en char, n�cessaire pour la sauvegarde
        i++;
    }
    raw_data.clear();

    vector<unsigned char> png;

    unsigned error_save = lodepng::encode(png, raw_png, width, height);//utilisation de lodepng pour la compression des donn�es
    raw_png.clear();

    if(!error_save) lodepng::save_file(png, filename);//utilisation de lodepng pour l'�criture du fichier
    png.clear();

    //if there's an error, display it
    if(error_save) std::cout << "encoder error " << error_save << ": "<< lodepng_error_text(error_save) << std::endl;

    cout << "png image saved" << endl;
}

void ImageIO::toneMapping(Image &src)
{
    using namespace Eigen;
    Vector4f min(50.f, 50.f, 50.f, 1.f), max(0.f, 0.f, 0.f, 1.f);
    for (int y = 0; y < src.height(); ++y)
        for (int x = 0; x < src.width(); ++x)
        {
            float r = src.pixel(x, y)(0);
            float g = src.pixel(x, y)(1);
            float b = src.pixel(x, y)(2);
            if (r > max(0) && g > max(1) && b > max(2))
                max = Vector4f(r, g, b, 1.f);
            else if (r < min(0) && g < min(1) && b < min(2))
                min = Vector4f(r, g, b, 1.f);
        }

    float r_min = min(0);
    float g_min = min(1);
    float b_min = min(2);

    float r_max = max(0);
    float g_max = max(1);
    float b_max = max(2);

    for (int y = 0; y < src.height(); ++y)
        for (int x = 0; x < src.width(); ++x)
        {
            float r = src.pixel(x, y)(0);
            float g = src.pixel(x, y)(1);
            float b = src.pixel(x, y)(2);

            r = (r - r_min)/(r_max - r_min);
            g = (g - g_min)/(g_max - g_min);
            b = (b - b_min)/(b_max - b_min);

            src.setPixel(x, y, Vector4f(r, g, b, 1.f));
        }
}
