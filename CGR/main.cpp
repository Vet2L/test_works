#include "mainlayout.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainLayout w;
    //for computer
    w.show();
    //for android
    //w.showFullScreen();
    
    return a.exec();
}
