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
    void startDiaporama_clicked();
    void endDiaporama_clicked();
    void closeProgram_clicked();

    void fsIsChecked(bool checked);
    void tmIsChecked(bool checked);
private:

    void addObject(QAbstractButton* object);

    std::vector<QAbstractButton*> m_ButtonList;

    DisplayManager* m_Manager;

    QTimer* m_Timer;

    std::vector<QString> m_ImgPath;
    std::vector<Image> m_Images;

    unsigned int m_CurrentImage;

    bool m_Running;

    bool m_Diaporama;
};

#endif // MAINWINDOW_H
