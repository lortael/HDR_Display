#ifndef BACKPANEL_H_INCLUDED
#define BACKPANEL_H_INCLUDED

#include "DisplayDevice.h"

class BackPanel : public DisplayDevice
{
public :

    BackPanel();

//    BackPanel(unsigned int height, unsigned int width, unsigned int id);

    void displayImageCV(Image &img);

    void displayImageGL(Image &img);

private:

protected:

};

#endif //BACKPANEL_H_INCLUDED
