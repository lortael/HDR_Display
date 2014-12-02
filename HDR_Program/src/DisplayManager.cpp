#include "DisplayManager.h"
#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "Window.h"

using namespace std;

DisplayManager::DisplayManager()
    : m_CurrentMode(GL)
{

}

void DisplayManager::initManager(Image const& img, unsigned int nbDevices)
{
    m_Image = img;
    if (nbDevices != 2)
    {

    }
    else
    {
        DisplayDevice* front = new FrontPanel();
        addDisplay(front);

//        DisplayDevice* back = new BackPanel();
//        addDisplay(back);
    }
}

void DisplayManager::initManager(QString filepath, unsigned int nbDevices)
{
    Image img;
    ImageIO testIO;
    testIO.imgLoad(img, filepath);
    m_Image = img;
    if (nbDevices != 2)
    {

    }
    else
    {
        DisplayDevice* front = new FrontPanel();
        addDisplay(front);

        DisplayDevice* back = new BackPanel();
        addDisplay(back);
    }
}


void DisplayManager::addDisplay(DisplayDevice* device)
{
    m_DisplayList.push_back(device);

    size_t deviceIndex = m_DisplayList.size() - 1;

    m_DisplayList[deviceIndex]->setId(deviceIndex);
}

void DisplayManager::multipleDisplay()
{
    if (m_CurrentMode == CV)
    {
        for (unsigned int i = 0; i < m_DisplayList.size(); ++i)
            m_DisplayList[i]->displayImageCV(m_Image);
        cv::waitKey(0);
    }
    else
        for (unsigned int i = 0; i < m_DisplayList.size(); ++i)
            m_DisplayList[i]->displayImageGL(m_Image);
}
