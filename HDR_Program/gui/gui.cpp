#include "gui.h"
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>

#include "ImageIO.h"
#include"Image.h"

Gui::Gui()
    : m_Running(false),
      m_Timer(new QTimer(this)),
      m_Diaporama(false)
{
    m_ImgPath.push_back(HDR_DIR"/data/Lake.hdr");
    m_ImgPath.push_back(HDR_DIR"/data/meadow.hdr");
    m_ImgPath.push_back(HDR_DIR"/data/image.hdr");

    init();
}

void Gui::init()
{
    m_Manager = new DisplayManager;
    m_Manager->initManager(m_ImgPath[0]);
    m_CurrentImage = 0;

    setFixedSize(200, 440);
    setWindowFlags(Qt::WindowStaysOnTopHint);
//    setFocusPolicy();

    QPushButton* initProgram = new QPushButton("Initiate program", this);
    connect(initProgram, SIGNAL(clicked()), this, SLOT(initProgram_clicked()));
    initProgram->setGeometry(20, 10, 160, 50);
    initProgram->setEnabled(true);
    initProgram->show();

    QMenu* imgMenu = menuBar()->addMenu("&Load image");

    QAction* loadLake = imgMenu->addAction("Load Lake");
    connect(loadLake, SIGNAL(triggered()), this, SLOT(loadLake()));
    QAction* loadMeadow = imgMenu->addAction("Load meadow");
    connect(loadMeadow, SIGNAL(triggered()), this, SLOT(loadMeadow()));

    QPushButton* loadImg = new QPushButton("Load image", this);
    loadImg->setMenu(imgMenu);
    loadImg->setGeometry(20, 70, 160, 50);
    loadImg->setEnabled(true);
    loadImg->show();

    QPushButton* enableFS = new QPushButton("Enable fullscreen", this);
    connect(enableFS, SIGNAL(clicked()), this, SLOT(enableFS_clicked()));
    enableFS->setGeometry(20, 130, 160, 50);
    enableFS->setEnabled(true);
    enableFS->show();

    QPushButton* disableFS = new QPushButton("Disable fullscreen", this);
    connect(disableFS, SIGNAL(clicked()), this, SLOT(disableFS_clicked()));
    disableFS->setGeometry(20, 190, 160, 50);
    disableFS->setEnabled(true);
    disableFS->show();

    QPushButton* startDiaporama = new QPushButton("Start diaporama", this);
    connect(startDiaporama, SIGNAL(clicked()), this, SLOT(startDiaporama_clicked()));
    startDiaporama->setGeometry(20, 250, 160, 50);
    startDiaporama->setEnabled(true);
    startDiaporama->show();

    QPushButton* endDiaporama = new QPushButton("End diaporama", this);
    connect(endDiaporama, SIGNAL(clicked()), this, SLOT(endDiaporama_clicked()));
    endDiaporama->setGeometry(20, 310, 160, 50);
    endDiaporama->setEnabled(true);
    endDiaporama->show();

    QPushButton* closeProgram = new QPushButton("Close Program", this);
    connect(closeProgram, SIGNAL(clicked()), this, SLOT(closeProgram_clicked()));
    closeProgram->setGeometry(20, 370, 160, 50);
    closeProgram->setEnabled(true);
    closeProgram->show();
}

void Gui::initProgram_clicked()
{
    if (m_Running == false)
    {
        m_Manager->multipleDisplay();
        m_Running = true;
    }
}

void Gui::loadLake()
{
    if (m_Running == true)
        m_Manager->endDisplay();
    else
        m_Running = true;

    ImageIO loader;
    Image img;
    loader.imgLoad(img, m_ImgPath[0]);
    m_CurrentImage = 0;
    m_Manager->loadImg(img);
    m_Manager->multipleDisplay();
}

void Gui::loadMeadow()
{
    if (m_Running == true)
        m_Manager->endDisplay();
    else
        m_Running = true;

    ImageIO loader;
    Image img;
    loader.imgLoad(img, m_ImgPath[1]);
    m_CurrentImage = 1;
    m_Manager->loadImg(img);
    m_Manager->multipleDisplay();
}

void Gui::enableFS_clicked()
{    
    for (unsigned int i = 0; i < m_Manager->nbDevice(); ++i)
        m_Manager->accessDevice(i)->toggleFullscreen();

    if (m_Running == true)
    {
        m_Manager->endDisplay();

        m_Manager->multipleDisplay();
    }
}

void Gui::disableFS_clicked()
{
    for (unsigned int i = 0; i < m_Manager->nbDevice(); ++i)
        m_Manager->accessDevice(i)->toggleWindow();

    if (m_Running == true)
    {
        m_Manager->endDisplay();

        m_Manager->multipleDisplay();
    }
}

void Gui::startDiaporama_clicked()
{
    if (m_Diaporama == false)
    {
        connect(m_Timer, SIGNAL(timeout()), this, SLOT(loadNextImg_triggered()));
        m_Timer->start(3000);
        m_Diaporama = true;
    }
}

void Gui::endDiaporama_clicked()
{
    if(m_Diaporama == true)
    {
        m_Timer->start(10000000);
        m_Diaporama = false;
        std::cout << "end" << std::endl;
    }
}

void Gui::loadNextImg_triggered()
{
    if (m_Running == true)
        m_Manager->endDisplay();
    else
        m_Running = true;

    m_CurrentImage = (m_CurrentImage + 1 > m_ImgPath.size() - 1)? 0 : m_CurrentImage + 1;
    ImageIO loader;
    Image img;
    loader.imgLoad(img, m_ImgPath[m_CurrentImage]);
    m_Manager->loadImg(img);
    m_Manager->multipleDisplay();
}


void Gui::closeProgram_clicked()
{
    if (m_Running == true)
    {
        m_Manager->endDisplay();
        m_Running = false;
    }
}
