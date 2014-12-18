#include "gui.h"
#include <QMenu>
#include <QMenuBar>
#include <QCheckBox>

#include "ImageIO.h"
#include"Image.h"

#define IMAGE_DIR HDR_DIR"/data/hdr_images"

Gui::Gui()
    : m_Running(false),
      m_Timer(new QTimer(this)),
      m_Diaporama(false)
{
    m_ImgPath.push_back(IMAGE_DIR"/lake.hdr");
    m_ImgPath.push_back(IMAGE_DIR"/meadow.hdr");
    m_ImgPath.push_back(IMAGE_DIR"/reno.hdr");
    m_ImgPath.push_back(IMAGE_DIR"/church.hdr");
//    m_ImgPath.push_back(IMAGE_DIR"/../PhiGrid.png");
    m_ImgPath.push_back(IMAGE_DIR"/eiffel.hdr");
    m_ImgPath.push_back(IMAGE_DIR"/vinesunset.hdr");

    ImageIO loader;

    for (unsigned int i = 0; i < m_ImgPath.size(); ++i)
    {
        Image img;
        loader.imgLoad(img, m_ImgPath[i]);
        m_Images.push_back(img);
    }

    init();
}

void Gui::init()
{
    m_CurrentImage = 0;
    m_Manager = new DisplayManager;
    m_Manager->initManager(m_Images[m_CurrentImage], 3);

    setWindowFlags(Qt::WindowStaysOnTopHint);

    QPushButton* initProgram = new QPushButton("Initiate program", this);
    connect(initProgram, SIGNAL(clicked()), this, SLOT(initProgram_clicked()));
    addObject(initProgram);

    QMenu* imgMenu = menuBar()->addMenu("&Load image");

    QAction* loadLake = imgMenu->addAction("Load Lake");
    connect(loadLake, SIGNAL(triggered()), this, SLOT(loadLake()));
    QAction* loadMeadow = imgMenu->addAction("Load meadow");
    connect(loadMeadow, SIGNAL(triggered()), this, SLOT(loadMeadow()));
    QAction* loadReno = imgMenu->addAction("Load reno");
    connect(loadReno, SIGNAL(triggered()), this, SLOT(loadReno()));
    QAction* loadChurch = imgMenu->addAction("Load church");
    connect(loadChurch, SIGNAL(triggered()), this, SLOT(loadChurch()));
    QAction* loadEiffel = imgMenu->addAction("Load eiffel");
    connect(loadEiffel, SIGNAL(triggered()), this, SLOT(loadEiffel()));

    QPushButton* loadImg = new QPushButton("Load image", this);
    loadImg->setMenu(imgMenu);
    addObject(loadImg);

    QCheckBox* fullscreen = new QCheckBox("Fullscreen", this);
    connect(fullscreen, SIGNAL(toggled(bool)), this, SLOT(fsIsChecked(bool)));
    addObject(fullscreen);

    QCheckBox* tonemap = new QCheckBox("Tone mapping", this);
    connect(tonemap, SIGNAL(toggled(bool)), this, SLOT(tmIsChecked(bool)));
    addObject(tonemap);

    QCheckBox* rendering = new QCheckBox("Using OpenGL", this);
    connect(rendering, SIGNAL(toggled(bool)), this, SLOT(renderIsChecked(bool)));
    rendering->setChecked(true);
    addObject(rendering);

    QPushButton* startDiaporama = new QPushButton("Start diaporama", this);
    connect(startDiaporama, SIGNAL(clicked()), this, SLOT(startDiaporama_clicked()));
    addObject(startDiaporama);

    QPushButton* endDiaporama = new QPushButton("End diaporama", this);
    connect(endDiaporama, SIGNAL(clicked()), this, SLOT(endDiaporama_clicked()));
    addObject(endDiaporama);

    QPushButton* closeProgram = new QPushButton("Close windows", this);
    connect(closeProgram, SIGNAL(clicked()), this, SLOT(closeProgram_clicked()));
    addObject(closeProgram);

    int nbButton(m_ButtonList.size());
    setFixedSize(200, nbButton*60 + 20);
}

void Gui::addObject(QAbstractButton *object)
{
    m_ButtonList.push_back(object);
    int nbObject(m_ButtonList.size() - 1);

    m_ButtonList[nbObject]->setGeometry(20, 10 + nbObject*60, 160, 50);
    m_ButtonList[nbObject]->setEnabled(true);
    m_ButtonList[nbObject]->show();
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
    m_CurrentImage = 0;
    loadImg();
}

void Gui::loadMeadow()
{
    m_CurrentImage = 1;
    loadImg();
}

void Gui::loadReno()
{
    m_CurrentImage = 2;
    loadImg();
}

void Gui::loadChurch()
{
    m_CurrentImage = 3;
    loadImg();
}

void Gui::loadEiffel()
{
    m_CurrentImage = 4;
    loadImg();
}

void Gui::fsIsChecked(bool checked)
{
    if (checked)
        for (unsigned int i = 0; i < m_Manager->nbDevice(); ++i)
            m_Manager->accessDevice(i)->toggleFullscreen();
    else
        for (unsigned int i = 0; i < m_Manager->nbDevice(); ++i)
            m_Manager->accessDevice(i)->toggleWindow();

    if (m_Running == true)
    {
        m_Manager->endDisplay();

        m_Manager->multipleDisplay();
    }
}

void Gui::tmIsChecked(bool checked)
{
    m_Manager->changeToneMapping(checked);
    if (m_Running == true)
    {
        if (m_Manager->mode() == GL)
        {
            if (checked)
            for (unsigned int i = 0; i < m_Manager->nbDevice(); ++i)
                m_Manager->accessDevice(i)->glWidget()->toggleToneMapping();
        else
            for (unsigned int i = 0; i < m_Manager->nbDevice(); ++i)
                m_Manager->accessDevice(i)->glWidget()->toggleHDRDisplay();
        }
        else if (m_Manager->mode() == CV)
        {
            m_Manager->endDisplay();
            m_Manager->multipleDisplay();
        }
    }
}

void Gui::renderIsChecked(bool checked)
{
    if (m_Running == true)
    {
        m_Manager->endDisplay();
    }

    if (checked == true)
        m_Manager->setMode(GL);
    else
        m_Manager->setMode(CV);

    if (m_Running == true)
    {
        m_Manager->multipleDisplay();
    }
}

void Gui::startDiaporama_clicked()
{
    if (m_Diaporama == false)
    {
        connect(m_Timer, SIGNAL(timeout()), this, SLOT(loadNextImg_triggered()));
        m_Timer->start(5000);
        m_Diaporama = true;

        if (m_Running == false)
        {
            m_Manager->multipleDisplay();
            m_Running = true;
        }
    }

}

void Gui::endDiaporama_clicked()
{
    if(m_Diaporama == true)
    {
        m_Timer->disconnect(SIGNAL(timeout()));
        m_Diaporama = false;
    }
}

void Gui::loadNextImg_triggered()
{
    m_CurrentImage = (m_CurrentImage + 1 > m_ImgPath.size() - 1)? 0 : m_CurrentImage + 1;
    loadImg();
}

void Gui::loadImg()
{
    m_Manager->loadImg(m_Images[m_CurrentImage]);
    if (m_Running == true)
        m_Manager->updateDisplay();
    else
    {
        m_Manager->multipleDisplay();
        m_Running = true;
    }
}


void Gui::closeProgram_clicked()
{
    if (m_Running == true)
    {
        endDiaporama_clicked();
        m_Manager->endDisplay();
        m_Running = false;
    }
}
