#include "mainlayout.h"

MainLayout::MainLayout(QWidget *parent)
    : QWidget(parent)
{
    this->initElements();
    this->createHorizontalLayout();
    connect(leftButton,SIGNAL(clicked()),this,SLOT(toResult()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(toGallery()));
}

MainLayout::~MainLayout()
{
    delete mainHLayout;
    delete mainVLayout;
    delete leftVLayout;
    delete rightVLayout;
    delete bottomHLayout;
    delete rightButton;
    delete leftButton;
    delete centralWidget;
    this->deleteCamera();
    this->deleteGallery();
    this->deleteResult();
}

void MainLayout::initElements()
{
    //horizontal layout:
    mainHLayout = new QHBoxLayout;
    leftVLayout = new QVBoxLayout;
    rightVLayout = new QVBoxLayout;
    //vertical layout:
    mainVLayout = new QVBoxLayout;
    bottomHLayout = new QHBoxLayout;

    centralWidget = new QWidget();
    //buttons:
    rightButton = new QPushButton(">");
    leftButton = new QPushButton("<");

    initCamera();
    initGallery();
    initResult();
}

void MainLayout::createHorizontalLayout()
{
    //left part
    leftVLayout->addStretch();
    leftVLayout->addWidget(leftButton);
    //right part
    rightVLayout->addStretch();
    rightVLayout->addWidget(rightButton);
    //central part
    centralWidget->setLayout(cameraLayout);
    status = CAMERA;
    //main
    mainHLayout->addLayout(leftVLayout);
    mainHLayout->addWidget(centralWidget);
    mainHLayout->addLayout(rightVLayout);

    this->setLayout(mainHLayout);
}

void MainLayout::createVerticalLayout()
{
    //TODO
}

void MainLayout::toHorizontalLayout()
{

}

void MainLayout::toVerticalLayout()
{

}

void MainLayout::toCamera()
{
    if (status==GALLERY)
    {
        deleteGallery();
        centralWidget->setLayout(cameraLayout);
        initGallery();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toCamera()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toResult()));
    }
    if (status==RESULT)
    {
        deleteResult();
        centralWidget->setLayout(cameraLayout);
        initResult();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toGallery()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toCamera()));
    }
    status = CAMERA;
    connect(leftButton,SIGNAL(clicked()),this,SLOT(toResult()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(toGallery()));
}

void MainLayout::toGallery()
{
    if (status==CAMERA)
    {
        deleteCamera();
        centralWidget->setLayout(galleryLayout);
        initCamera();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toResult()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toGallery()));
    }
    if (status==RESULT)
    {
        deleteResult();
        centralWidget->setLayout(galleryLayout);
        initResult();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toGallery()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toCamera()));
    }
    status = GALLERY;
    connect(leftButton,SIGNAL(clicked()),this,SLOT(toCamera()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(toResult()));
}

void MainLayout::toResult()
{
    if (status==CAMERA)
    {
        deleteCamera();
        centralWidget->setLayout(resultLayout);
        initCamera();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toResult()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toGallery()));
    }
    if (status==GALLERY)
    {
        deleteGallery();
        centralWidget->setLayout(resultLayout);
        initGallery();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toCamera()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toResult()));
    }
    status = RESULT;
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
    galleryLayout = new QVBoxLayout;
    galleryLabel = new QLabel("Gallery");
    galleryLayout->addWidget(galleryLabel);
    galleryLayout->addStretch();
}

void MainLayout::initResult()
{
    //result:
    resultLayout = new QVBoxLayout;
    resultLabel = new QLabel("Result");
    resultLayout->addWidget(resultLabel);
    resultLayout->addStretch();
    //resultImage = new QImage();
    //resultLayout->addWidget(resultImage);

}

void MainLayout::deleteCamera()
{
    delete cameraLabel;
    delete cameraLayout;
}

void MainLayout::deleteGallery()
{
    delete galleryLabel;
    delete galleryLayout;
}

void MainLayout::deleteResult()
{
    delete resultLabel;
    delete resultLayout;
}
