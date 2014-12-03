#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../src/DisplayManager.h"
#include <QMainWindow>

class Gui : public QMainWindow
{
    Q_OBJECT
public:

    Gui();

    void init();

private slots:

    void initProgram_clicked();
    void loadImg_clicked();
    void enableFS_clicked();
    void disableFS_clicked();
    void closeProgram_clicked();

private:

    DisplayManager* m_Manager;
};

#endif // MAINWINDOW_H
