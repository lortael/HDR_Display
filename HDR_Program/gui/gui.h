/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 *
 * */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../src/DisplayManager.h"
#include <QMainWindow>
#include <QString>
#include <QTimer>

class Gui : public QMainWindow
{
    Q_OBJECT
public:

    Gui();

    void init();

private slots:

    void initProgram_clicked();
    void loadNextImg_triggered();
    void loadLake();
    void loadMeadow();
    void enableFS_clicked();
    void disableFS_clicked();
    void startDiaporama_clicked();
    void endDiaporama_clicked();
    void closeProgram_clicked();

private:

    DisplayManager* m_Manager;

    QTimer* m_Timer;

    std::vector<QString> m_ImgPath;

    unsigned int m_CurrentImage;

    bool m_Running;

    bool m_Diaporama;
};

#endif // MAINWINDOW_H
