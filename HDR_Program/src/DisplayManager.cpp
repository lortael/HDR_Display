#include "DisplayManager.h"
#include <iostream>
#include <QDesktopWidget>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

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
        DisplayDevice* main = new StandardPanel();
        addDisplay(main);

        DisplayDevice* back = new BackPanel();
        addDisplay(back);

        DisplayDevice* front = new FrontPanel();
        addDisplay(front);


    }
    else
    {
        DisplayDevice* front = new FrontPanel();
        addDisplay(front);

        DisplayDevice* back = new BackPanel();
        addDisplay(back);
    }
    m_nbDevice = m_DisplayList.size();
}

void DisplayManager::initManager(QString filepath, unsigned int nbDevices)
{
    Image img;
    ImageIO testIO;
    testIO.imgLoad(img, filepath);
    m_Image = img;
    if (nbDevices != 2)
    {
        DisplayDevice* main = new StandardPanel();
        addDisplay(main);

        DisplayDevice* front = new FrontPanel();
        addDisplay(front);

        DisplayDevice* back = new BackPanel();
        addDisplay(back);
    }
    else
    {
        DisplayDevice* front = new FrontPanel();
        addDisplay(front);

        DisplayDevice* back = new BackPanel();
        addDisplay(back);
    }
    m_nbDevice = m_DisplayList.size();
}


void DisplayManager::addDisplay(DisplayDevice* device)
{
    m_DisplayList.push_back(device);

    size_t deviceIndex = m_DisplayList.size() - 1;

    m_DisplayList[deviceIndex]->setId(QApplication::desktop()->primaryScreen() + deviceIndex);
}

void DisplayManager::multipleDisplay()
{
    if (m_CurrentMode == CV)
    {
        for (unsigned int i = 0; i < m_DisplayList.size(); ++i)
            m_DisplayList[i]->displayImageCV(m_Image);
    }
    else
        for (unsigned int i = 0; i < m_DisplayList.size(); ++i)
        {
            m_DisplayList[i]->initDevice();
            m_DisplayList[i]->displayImageGL(m_Image);
        }
}

void DisplayManager::updateDisplay()
{
    if (m_CurrentMode == CV)
    {
        cv::destroyAllWindows();
        for (unsigned int i = 0; i < m_DisplayList.size(); ++i)
            m_DisplayList[i]->displayImageCV(m_Image);
    }
    else
        for (unsigned int i = 0; i < m_DisplayList.size(); ++i)
        {
            m_DisplayList[i]->updateImageGL(m_Image);
        }
}

void DisplayManager::endDisplay()
{
    if (m_CurrentMode == GL)
    {
        for (unsigned int i = 0; i < m_DisplayList.size(); ++i)
            m_DisplayList[i]->closeGlWindow();
    }
    else
        cv::destroyAllWindows();
}

void DisplayManager::changeToneMapping(bool tm)
{
        for (unsigned int i = 0; i < m_DisplayList.size(); ++i)
            m_DisplayList[i]->changeTM(tm);
}
