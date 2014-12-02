//#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include <QTimer>
//#include "Image.h"
//#include "ImageIO.h"

//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow),
//{
//    ui->setupUi(this);
////    connect(ui->LoadImage,SIGNAL(clicked()),this,SLOT(close()));

//    // timer
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(updateComputation()));
//    timer->start(30);
//}

//void MainWindow::attachManager()
//{
//    m_Manager = new DisplayManager;
//}

//MainWindow::~MainWindow()
//{
//    delete m_Manager;
//    delete ui;
//}

//void MainWindow::init()
//{
//    m_Manager->initManager(HDR_DIR"/data/Lake.hdr");
//}

//void MainWindow::on_btn_initProgram_clicked()
//{
//    m_Manager->multipleDisplay();
//}

////void MainWindow::on_btn_Load_Image_clicked()
////{
////    m_Manager->loadImg();
////}
