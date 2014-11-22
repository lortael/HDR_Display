#include "DisplayManager.h"
#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "Window.h"

using namespace std;

void DisplayManager::addDisplay(DisplayDevice* device)
{
    m_DisplayList.push_back(device);

    size_t deviceIndex = m_DisplayList.size() - 1;

    m_DisplayList[deviceIndex]->setId(deviceIndex);
}

void DisplayManager::multipleDisplay()
{
    for (unsigned int i = 0; i < m_DisplayList.size(); ++i)
        m_DisplayList[i]->displayImageCV();

    cv::waitKey(0);
}
