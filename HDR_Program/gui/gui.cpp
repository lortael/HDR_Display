#include "gui.h"
#include <QPushButton>

Gui::Gui()
{
    init();
}

void Gui::init()
{
    m_Manager = new DisplayManager;
    m_Manager->initManager(HDR_DIR"/data/Lake.hdr");

    setFixedSize(160, 320);
    setWindowFlags(Qt::WindowStaysOnTopHint);

    QPushButton* initProgram = new QPushButton("Initiate program", this);
    connect(initProgram, SIGNAL(clicked()), this, SLOT(initProgram_clicked()));
    initProgram->setGeometry(20, 10, 120, 50);
    initProgram->setEnabled(true);
    initProgram->show();

    QPushButton* loadImg = new QPushButton("Load image", this);
    connect(loadImg, SIGNAL(clicked()), this, SLOT(loadImg_clicked()));
    loadImg->setGeometry(20, 70, 120, 50);
    loadImg->setEnabled(true);
    loadImg->show();

    QPushButton* enableFS = new QPushButton("Enable fullscreen", this);
    connect(enableFS, SIGNAL(clicked()), this, SLOT(enableFS_clicked()));
    enableFS->setGeometry(20, 130, 120, 50);
    enableFS->setEnabled(true);
    enableFS->show();

    QPushButton* disableFS = new QPushButton("Disable fullscreen", this);
    connect(disableFS, SIGNAL(clicked()), this, SLOT(disableFS_clicked()));
    disableFS->setGeometry(20, 190, 120, 50);
    disableFS->setEnabled(true);
    disableFS->show();

    QPushButton* closeProgram = new QPushButton("Close Program", this);
    connect(closeProgram, SIGNAL(clicked()), this, SLOT(closeProgram_clicked()));
    closeProgram->setGeometry(20, 250, 120, 50);
    closeProgram->setEnabled(true);
    closeProgram->show();
}

void Gui::initProgram_clicked()
{
    m_Manager->multipleDisplay();
}

void Gui::loadImg_clicked()
{
    std::cout << "not implemented" <<std::endl;
}

void Gui::enableFS_clicked()
{
    for (unsigned int i = 0; i < m_Manager->nbDevice(); ++i)
        m_Manager->accessDevice(i)->toggleFullscreen();
    m_Manager->endDisplay();
    m_Manager->multipleDisplay();
}

void Gui::disableFS_clicked()
{
    for (unsigned int i = 0; i < m_Manager->nbDevice(); ++i)
        m_Manager->accessDevice(i)->toggleWindow();
    m_Manager->endDisplay();
    m_Manager->multipleDisplay();
}

void Gui::closeProgram_clicked()
{
    m_Manager->endDisplay();
}
