#ifndef DISPLAYMANAGER_H_INCLUDED
#define DISPLAYMANAGER_H_INCLUDED

#include <vector>
#include "DisplayDevice.h"

enum DISPLAYMODE {CV = 0, GL = 1};

class DisplayManager
{
public :

    DisplayManager();

    void addDisplay(DisplayDevice* device);

    DisplayDevice* accessDevice(unsigned int index) {if (index < m_DisplayList.size()) return m_DisplayList[index];}

    void multipleDisplay();

    DISPLAYMODE mode() {return m_CurrentMode;}
    void setMode(DISPLAYMODE mode) {m_CurrentMode = mode;}

private:

protected:

    DISPLAYMODE m_CurrentMode;

    std::vector<DisplayDevice*> m_DisplayList;

};

#endif //DISPLAYMANAGER_H_INCLUDED
