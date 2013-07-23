#include "mainlayout.h"
#include <QFileDialog>

MainLayout::MainLayout(QWidget *parent)
    : QWidget(parent)
{
    this->initElements();
    this->createHorizontalLayout();
    //start with camera
    connect(leftButton,SIGNAL(clicked()),this,SLOT(toResult()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(toGallery()));
    connect(actionButton,SIGNAL(clicked()),this,SLOT(takeShoot()));
}

MainLayout::~MainLayout()
{
    delete mainHLayout;
    delete leftVLayout;
    delete rightVLayout;
    delete rightButton;
    delete leftButton;
    delete actionButton;
    delete centralWidget;

    this->deleteCameraLayout();
    this->deleteGalleryLayout();
    this->deleteResultLayout();
}

void MainLayout::initElements()
{
    //horizontal layout:
    mainHLayout = new QHBoxLayout;
    leftVLayout = new QVBoxLayout;
    rightVLayout = new QVBoxLayout;

    centralWidget = new QWidget(this);
    //buttons:
    rightButton = new QPushButton;
    rightButton->setIcon(QIcon(":/images/right_arrow.png"));
    leftButton = new QPushButton;
    leftButton->setIcon(QIcon(":/images/left_arrow.png"));
    actionButton = new QPushButton;

    initCamera();
    initGallery();
    initResult();
}

void MainLayout::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::homePath());
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
        if (image.isNull())
        {
            //resultImage->setText(tr("error to open file %1").append(fileName));
            //resultImage->adjustSize();
            return;
        }
        galleryList.append(fileName);
        deleteGalleryLayout();
        initGallery();
        centralWidget->setLayout(galleryLayout);
    }
    //toResult();
}

void MainLayout::takeShoot()
{
    //camera
}

void MainLayout::createHorizontalLayout()
{
    //left part
    leftVLayout->addStretch();
    leftVLayout->addWidget(leftButton);
    //right part
    rightVLayout->addWidget(actionButton);
    rightVLayout->addStretch();
    rightVLayout->addWidget(rightButton);
    //central part
    centralWidget->setLayout(cameraLayout);
    status = CAMERA;
    actionButton->setIcon(QIcon(":/images/camera.png"));
    //main
    mainHLayout->addLayout(leftVLayout);
    mainHLayout->addWidget(centralWidget);
    mainHLayout->addLayout(rightVLayout);

    this->setLayout(mainHLayout);
}

void MainLayout::toCamera()
{
    if (status==GALLERY)
    {
        deleteGalleryLayout();
        centralWidget->setLayout(cameraLayout);
        initGallery();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toCamera()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toResult()));
        disconnect(actionButton,SIGNAL(clicked()),this,SLOT(openFile()));
    }
    if (status==RESULT)
    {
        deleteResultLayout();
        centralWidget->setLayout(cameraLayout);
        initResult();
        actionButton->show();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toGallery()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toCamera()));
    }
    status = CAMERA;
    actionButton->setIcon(QIcon(":/images/camera.png"));
    connect(leftButton,SIGNAL(clicked()),this,SLOT(toResult()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(toGallery()));
    connect(actionButton,SIGNAL(clicked()),this,SLOT(takeShoot()));
}

void MainLayout::toGallery()
{
    if (status==CAMERA)
    {
        deleteCameraLayout();
        centralWidget->setLayout(galleryLayout);
        initCamera();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toResult()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toGallery()));
        disconnect(actionButton,SIGNAL(clicked()),this,SLOT(takeShoot()));
    }
    if (status==RESULT)
    {
        deleteResultLayout();
        centralWidget->setLayout(galleryLayout);
        initResult();
        actionButton->show();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toGallery()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toCamera()));
    }
    status = GALLERY;
    actionButton->setIcon(QIcon(":/images/open_icon.png"));
    connect(leftButton,SIGNAL(clicked()),this,SLOT(toCamera()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(toResult()));
    connect(actionButton,SIGNAL(clicked()),this,SLOT(openFile()));
}

void MainLayout::toResult()
{
    if (status==CAMERA)
    {
        deleteCameraLayout();
        centralWidget->setLayout(resultLayout);
        initCamera();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toResult()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toGallery()));
        disconnect(actionButton,SIGNAL(clicked()),this,SLOT(takeShoot()));
    }
    if (status==GALLERY)
    {
        deleteGalleryLayout();
        centralWidget->setLayout(resultLayout);
        initGallery();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toCamera()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toResult()));
        disconnect(actionButton,SIGNAL(clicked()),this,SLOT(openFile()));
    }
    status = RESULT;
    actionButton->hide();
    connect(leftButton,SIGNAL(clicked()),this,SLOT(toGallery()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(toCamera()));
}

void MainLayout::initCamera()
{
    //camera layout:
    cameraLayout = new QVBoxLayout;
    cameraLabel = new QLabel("Camera");
    cameraLayout->addWidget(cameraLabel);
    cameraLayout->addStretch();
}

void MainLayout::initGallery()
{
    //gallery layout:
    galleryLayout = new QGridLayout;
    galleryTable = new QTableWidget(galleryList.size()/3+1,3);
    galleryTable->setShowGrid(false);
    galleryTable->verticalHeader()->hide();
    galleryTable->horizontalHeader()->hide();
    galleryTable->horizontalScrollBar()->hide();
    int cw = centralWidget->width()/3;
    galleryTable->setColumnWidth(0,cw);
    galleryTable->setColumnWidth(1,cw);
    galleryTable->setColumnWidth(2,cw);
    int rh = centralWidget->height()/3;
    for (int i=0; i<galleryList.size()/3+1; i++)
        galleryTable->setRowHeight(i,rh);
    for (int i=0; i<galleryList.size(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(
                    QIcon(galleryList[i]),"");
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        galleryTable->setItem(i/3,i%3, item);
    }
    galleryTable->setIconSize(QSize(cw,rh));

    galleryLabel = new QLabel("Gallery");

    galleryLayout->addWidget(galleryTable);
}

void MainLayout::initResult()
{
    //result:
    resultLayout = new QVBoxLayout;
    resultArea = new QScrollArea;
    resultImage = new QLabel;
    resultImage->setBackgroundRole(QPalette::Base);
    resultImage->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    resultImage->setScaledContents(true);
    resultArea->setBackgroundRole(QPalette::Dark);
    resultArea->setWidget(resultImage);
    resultLayout->addWidget(resultArea);
    if (!resultFile.isEmpty())
    {
        QImage image(resultFile);
        if (image.isNull())
        {
            resultImage->setText(tr("error to open file %1").append(resultFile));
            resultImage->adjustSize();
            return;
        }
        resultImage->setPixmap(QPixmap::fromImage(image));
        resultImage->adjustSize();
    }
    //resultLayout->addStretch();
    //resultImage = new QImage();
    //resultLayout->addWidget(resultImage);

}

void MainLayout::deleteCameraLayout()
{
    delete cameraLabel;
    delete cameraLayout;
}

void MainLayout::deleteGalleryLayout()
{
    delete galleryLabel;
    delete galleryTable;
    delete galleryLayout;
}

void MainLayout::deleteResultLayout()
{
    delete resultLayout;
    delete resultImage;
    delete resultArea;
}
