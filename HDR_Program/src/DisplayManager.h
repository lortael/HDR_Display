#ifndef DISPLAYMANAGER_H_INCLUDED
#define DISPLAYMANAGER_H_INCLUDED

#include <vector>
#include "DisplayDevice.h"
#include "BackPanel.h"
#include "FrontPanel.h"
#include "Image.h"
#include "ImageIO.h"

enum DISPLAYMODE {CV = 0, GL = 1};

class DisplayManager
{
public :

    DisplayManager();

    void initManager(Image const &img, unsigned int nbDevices = 2);

    void initManager(QString filepath, unsigned int nbDevices = 2);

    void addDisplay(DisplayDevice* device);

    DisplayDevice* accessDevice(unsigned int index) {if (index < m_DisplayList.size()) return m_DisplayList[index];}

    void multipleDisplay();

    DISPLAYMODE mode() {return m_CurrentMode;}
    void setMode(DISPLAYMODE mode) {m_CurrentMode = mode;}

    void loadImg(Image const &img) {m_Image = img;}

private:

protected:

    DISPLAYMODE m_CurrentMode;

    std::vector<DisplayDevice*> m_DisplayList;

    Image m_Image;

};

#endif //DISPLAYMANAGER_H_INCLUDED
