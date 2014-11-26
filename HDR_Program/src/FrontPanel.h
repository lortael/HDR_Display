#ifndef FRONTPANEL_H_INCLUDED
#define FRONTPANEL_H_INCLUDED

#include "DisplayDevice.h"

class FrontPanel : public DisplayDevice
{
public :

    FrontPanel();

//    FrontPanel(unsigned int height, unsigned int width, unsigned int id);

    void displayImageCV(Image &img);

    void displayImageGL(Image &img);

private:

protected:

};

#endif //FRONTPANEL_H_INCLUDED
