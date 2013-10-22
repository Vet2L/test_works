#include "mainlayout.h"
#include <QApplication>
#include <assert.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char *argv[])
{
    CvCapture *camera = cvCreateCameraCapture(0);
    assert(camera);
    IplImage *image = cvQueryFrame(camera);
    assert(image);

    QApplication a(argc, argv);
    MainLayout w(camera);

    //for computer
    //w.show();
    //for android
    w.showFullScreen();
    
    int retval = a.exec();
    cvReleaseCapture(&camera);
    return retval;
}
