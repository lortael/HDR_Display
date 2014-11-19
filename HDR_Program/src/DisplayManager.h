#ifndef DISPLAYMANAGER_H_INCLUDED
#define DISPLAYMANAGER_H_INCLUDED

#include <vector>
#include "DisplayDevice.h"

class DisplayManager
{
public :

    void addDisplay(DisplayDevice* device) {m_DisplayList.push_back(device);}

    DisplayDevice* accessDevice(unsigned int index) {if (index < m_DisplayList.size()) return m_DisplayList[index];}

private:

protected:

    std::vector<DisplayDevice*> m_DisplayList;

};

#endif DISPLAYMANAGER_H_INCLUDED
