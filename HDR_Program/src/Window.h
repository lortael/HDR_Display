#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

//#include "../glrendering/GLRender.h"

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <string>

class Window
{
public :

    Window();

    Window(unsigned int height, unsigned int width, cv::Mat img, std::string name);

    std::string name() {return m_WindowName;}
    cv::Mat image() {return m_Image;}
    unsigned int height() const {return m_Height;}
    unsigned int width() const {return m_Width;}

    Window& operator=(Window const &win);


private:

protected:

    std::string m_WindowName;

    unsigned int m_Height;
    unsigned int m_Width;

    cv::Mat m_Image;
};

#endif //WINDOW_H_INCLUDED
