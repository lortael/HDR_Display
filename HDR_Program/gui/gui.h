/* Copyright (C) 2014 David Murray <david.murray@institutoptique.fr>
 *
 * This class handles the GUI to manage the displays.
 * */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../src/DisplayManager.h"
#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QPushButton>
#include <QAbstractButton>

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
    void loadReno();
    void loadChurch();
    void loadEiffel();

    void startDiaporama_clicked();
    void endDiaporama_clicked();
    void closeProgram_clicked();

    void fsIsChecked(bool checked);
    void tmIsChecked(bool checked);
    void renderIsChecked(bool checked);
private:

    void loadImg();

    void addObject(QAbstractButton* object);

    //Attributes
    std::vector<QAbstractButton*> m_ButtonList;

    DisplayManager* m_Manager;

    QTimer* m_Timer;

    //Vector of filepath if images are loaded on the fly.
    std::vector<QString> m_ImgPath;
    //Vector of loaded images
    std::vector<Image> m_Images;

    unsigned int m_CurrentImage;

    bool m_Running;

    bool m_Diaporama;
};

#endif // MAINWINDOW_H
