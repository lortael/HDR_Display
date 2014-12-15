/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 * Class to manage multiple display devices.
 * */

#ifndef DISPLAYMANAGER_H_INCLUDED
#define DISPLAYMANAGER_H_INCLUDED

#include <vector>
#include "DisplayDevice.h"
#include "BackPanel.h"
#include "FrontPanel.h"
#include "StandardPanel.h"
#include "Image.h"
#include "ImageIO.h"

enum DISPLAYMODE {CV = 0, GL = 1};

class DisplayManager
{
public :

    DisplayManager();

    /**
     * @brief initializes the manager with a previously loaded image and with the required number of devices.
     * @param img, the Image to be displayed later.
     * @param nbDevices, default is 2 (back and front LCD panels).
     * */
    void initManager(Image const &img, unsigned int nbDevices = 2);

    /**
     * @brief initializes the manager with the filepath to the image to be loaded and with the required number of devices.
     * @param filepath, the path for Image to be displayed later.
     * @param nbDevices, default is 2 (back and front LCD panels).
     * */
    void initManager(QString filepath, unsigned int nbDevices = 2);

    /**
     * @brief displays an image on all the devices, whichever the rendering mode is.
     * */
    void multipleDisplay();

    /**
     * @brief updates the image on all the devices, whichever the rendering mode is.
     * */
    void updateDisplay();

    /**
     * @brief terminates the displaying process on all devices.
     * */
    void endDisplay();

    /**
     * @brief adds a device to the device list.
     * @param device, the desired device.
     * */
    void addDisplay(DisplayDevice* device);

    DisplayDevice* accessDevice(unsigned int index) {if (index < m_DisplayList.size()) return m_DisplayList[index];} 

    DISPLAYMODE mode() {return m_CurrentMode;}

    void setMode(DISPLAYMODE mode) {m_CurrentMode = mode;}

    void loadImg(Image const &img) {m_Image = img;}

    unsigned int nbDevice() {return m_nbDevice;}

    /**
     * @brief sets the desired state for tone-mapping.
     * @param tm, the new state.
     * */
    void changeToneMapping(bool tm);

private:

protected:

    DISPLAYMODE m_CurrentMode;

    std::vector<DisplayDevice*> m_DisplayList;

    unsigned int m_nbDevice;

    Image m_Image;

};

#endif //DISPLAYMANAGER_H_INCLUDED
