#include "mainlayout.h"

MainLayout::MainLayout(CvCapture *camera, QWidget *parent)
    : QWidget(parent)
{
    this->initElements();
    this->createHorizontalLayout();
    //start with camera
    connect(leftButton,SIGNAL(clicked()),this,SLOT(toResult()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(toGallery()));
    connect(actionButton,SIGNAL(clicked()),this,SLOT(takeShoot()));

    m_camera = camera;
    m_photoCounter = 0;
}

MainLayout::~MainLayout()
{
    switch (status) {
    case CAMERA:
    {
        this->deleteCameraLayout();
        break;
    }
    case GALLERY:
    {
        this->deleteGalleryLayout();
        break;
    }
    case RESULT:
    {
        this->deleteResultLayout();
        break;
    }
    default:
        break;
    }
    delete centralWidget;
    delete actionButton;
    delete leftButton;
    delete rightButton;
    delete rightVLayout;
    delete leftVLayout;
    delete mainHLayout;
}

void MainLayout::timerEvent(QTimerEvent *)
{
    IplImage *image = cvQueryFrame(m_camera);
    m_cvwidget->putFrame(image);
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
    rightButton->setMinimumHeight(64);
    rightButton->setMinimumWidth(64);
    leftButton = new QPushButton;
    leftButton->setMinimumHeight(64);
    leftButton->setMinimumWidth(64);
    leftButton->setIcon(QIcon(":/images/left_arrow.png"));
    actionButton = new QPushButton;
    actionButton->setMinimumHeight(64);
    actionButton->setMinimumWidth(64);
    actionButton->setIcon(QIcon(":/images/camera.png"));
    //imageDir = "/home/vet2l/Pictures/";
    imageDir = "/sdcard/DCIM/";

}

void MainLayout::takeShoot()
{
    IplImage *image = cvQueryFrame(m_camera);

    QPixmap photo = m_cvwidget->toPixmap(image);

    if (photo.save(imageDir+"picture.jpg")) //+ QString::number(m_photoCounter) + ".jpg"))
        //m_photoCounter++;
        toResult(imageDir+"picture.jpg");
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
    initCamera();
    centralWidget->setLayout(cameraLayout);
    status = CAMERA;
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
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toCamera()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toResult()));
    }
    if (status==RESULT)
    {
        deleteResultLayout();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toGallery()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toCamera()));
    }
    status = CAMERA;
    initCamera();
    centralWidget->setLayout(cameraLayout);
    connect(leftButton,SIGNAL(clicked()),this,SLOT(toResult()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(toGallery()));
    actionButton->show();
}

void MainLayout::toGallery()
{
    if (status==CAMERA)
    {
        deleteCameraLayout();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toResult()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toGallery()));
    }
    if (status==RESULT)
    {
        deleteResultLayout();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toGallery()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toCamera()));
    }
    status = GALLERY;
    initGallery();
    centralWidget->setLayout(galleryLayout);
    connect(leftButton,SIGNAL(clicked()),this,SLOT(toCamera()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(toResult()));
    actionButton->hide();
}

void MainLayout::toResult()
{
    if (status==CAMERA)
    {
        deleteCameraLayout();
        actionButton->hide();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toResult()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toGallery()));
    }
    if (status==GALLERY)
    {
        deleteGalleryLayout();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toCamera()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toResult()));
    }
    status = RESULT;
    initResult();
    centralWidget->setLayout(resultLayout);
    connect(leftButton,SIGNAL(clicked()),this,SLOT(toGallery()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(toCamera()));
}

void MainLayout::toResult(int i, int j)
{   //only from gallery
    if (i*col_s+j < galleryList.size())
    {
        resultFile = galleryList.at(i*col_s+j);
        //BUG
        /*status = RESULT;
        deleteGalleryLayout();
        disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toCamera()));
        disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toResult()));
        initResult();
        connect(leftButton,SIGNAL(clicked()),this,SLOT(toGallery()));
        connect(rightButton,SIGNAL(clicked()),this,SLOT(toCamera()));
        centralWidget->setLayout(resultLayout);
*/    }
}

void MainLayout::toResult(QString fileName)
{
    //only from camera
    resultFile = fileName;
    deleteCameraLayout();
    initResult();
    centralWidget->setLayout(resultLayout);
    disconnect(leftButton,SIGNAL(clicked()),this,SLOT(toResult()));
    disconnect(rightButton,SIGNAL(clicked()),this,SLOT(toGallery()));
    status = RESULT;
    actionButton->hide();
    connect(leftButton,SIGNAL(clicked()),this,SLOT(toGallery()));
    connect(rightButton,SIGNAL(clicked()),this,SLOT(toCamera()));
}

void MainLayout::initCamera()
{
    //camera layout:
    m_cvwidget = new CameraWidget;

    m_cvwidget->adjustSize();
    cameraLayout = new QVBoxLayout;
    cameraLayout->addWidget(m_cvwidget);
    timer_id = startTimer(100);  // 0.1-second timer
}

void MainLayout::initGallery()
{
    galleryList.clear();
    findImages(imageDir);
    //gallery layout:
    galleryLayout = new QVBoxLayout;
    galleryTable = new QTableWidget;
    col_s = galleryTable->width()/128 +1;
    galleryTable->setColumnCount(col_s);
    galleryTable->setRowCount(galleryList.size()/col_s+1);
    for (int i=0; i<galleryList.size()/col_s+1; i++)
        galleryTable->setRowHeight(i,128);
    for (int i=0; i<col_s; i++)
        galleryTable->setColumnWidth(i, 128);
    galleryTable->setShowGrid(false);
    galleryTable->verticalHeader()->hide();
    galleryTable->horizontalHeader()->hide();
    galleryTable->horizontalScrollBar()->hide();
    galleryTable->setIconSize(QSize(128,128));

    for (int i=0; i<galleryList.size(); i++)
    {
        QImageReader reader(galleryList[i]);
        //mathematic
        int iw=reader.size().width();
        int ih=reader.size().height();
        float ar = (float)iw/(float)ih;
        if (ar>1)
        {
            iw = 128;
            ih = 128/(ar);
        }
        else
        {
            ih = 128;
            iw = 128*(ar);
        }
        reader.setScaledSize(QSize(iw,ih));
        QTableWidgetItem *item = new QTableWidgetItem(
                    QIcon(QPixmap::fromImage(reader.read())),"");
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        galleryTable->setItem(i/col_s,i%col_s, item);
    }
    connect(galleryTable,SIGNAL(cellClicked(int,int)),this,SLOT(toResult(int,int)));
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
    if (!resultFile.isEmpty())
    {
        QImage image(resultFile);
        if (image.isNull())
        {
            resultImage->setText(tr("error to open file %1").arg(resultFile));
        }
        else
        {
            resultImage->setPixmap(QPixmap::fromImage(image));
        }
        resultImage->adjustSize();
        resultArea->setWidgetResizable(true);
    }
    resultArea->setWidget(resultImage);
    resultLayout->addWidget(resultArea);
}

void MainLayout::deleteCameraLayout()
{
    killTimer(timer_id);
    delete m_cvwidget;
    delete cameraLayout;
}

void MainLayout::deleteGalleryLayout()
{
    delete galleryTable;
    delete galleryLayout;
}

void MainLayout::deleteResultLayout()
{
    delete resultImage;
    delete resultArea;
    delete resultLayout;
}

void MainLayout::findImages(QString imDir)
{
    QStringList dirs = QDir(imDir).entryList(QDir::NoDotAndDotDot|QDir::Dirs);
    QStringList names = QDir(imDir).entryList(QStringList("*.jpg"),QDir::Files);
    for (int i=0; i<names.size(); i++)
    {
        if (names[i].compare(".jpg")>0)
            galleryList.append(imDir+names[i]);
    }
    if (!dirs.isEmpty())
        for (int i=0; i<dirs.size(); i++)
            findImages(imDir+dirs[i]+'/');
}
