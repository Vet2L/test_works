#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QImageReader>
#include <QTableWidget>
#include <QHeaderView>
#include <QScrollBar>
#include <QTableWidgetItem>
#include <QLabel>
#include <QScrollArea>
#include <QDir>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "camerawidget.h"

class MainLayout : public QWidget
{
    Q_OBJECT
    
public:
    MainLayout(CvCapture *camera, QWidget *parent = 0);
    ~MainLayout();

protected:
    void timerEvent(QTimerEvent*);

public slots:
    void toCamera();
    void toGallery();
    void toResult();
    void toResult(int i, int j);
    void toResult(QString fileName);
    void takeShoot();

private:
    //functions:
    void createHorizontalLayout();
    void initElements();
    void initCamera();
    void initGallery();
    void initResult();
    void deleteCameraLayout();
    void deleteGalleryLayout();
    void deleteResultLayout();
    void findImages(QString imDir);
    //horizontal layout:
    QHBoxLayout *mainHLayout;
    QVBoxLayout *leftVLayout;
    QVBoxLayout *rightVLayout;
    //central
    QWidget *centralWidget;
    //functionality layouts:
    QVBoxLayout *cameraLayout;
    QVBoxLayout *galleryLayout;
    QVBoxLayout *resultLayout;
    //buttons:
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *actionButton;
    //camera layout:
    //QLabel *cameraLabel;
    CameraWidget *m_cvwidget;
    CvCapture *m_camera;
    int m_photoCounter;
    int timer_id;
    //gallery layout:
    QTableWidget *galleryTable;
    QStringList galleryList;
    QString imageDir;
    int col_s;     //number of columns
    //result layout:
    QScrollArea *resultArea;
    QLabel *resultImage;
    QString resultFile;
    //QImage *resultImage;
    enum state {CAMERA, GALLERY, RESULT};
    state status;
};

#endif // MAINLAYOUT_H
