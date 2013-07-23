#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QToolButton>
#include <QImage>
#include <QTableWidget>
#include <QHeaderView>
#include <QScrollBar>
#include <QTableWidgetItem>
#include <QLabel>
#include <QList>
#include <QScrollArea>

class MainLayout : public QWidget
{
    Q_OBJECT
    
public:
    MainLayout(QWidget *parent = 0);
    ~MainLayout();

public slots:
    void toCamera();
    void toGallery();
    void toResult();
    void openFile();
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
    //horizontal layout:
    QHBoxLayout *mainHLayout;
    QVBoxLayout *leftVLayout;
    QVBoxLayout *rightVLayout;
    //central
    QWidget *centralWidget;
    //functionality layouts:
    QVBoxLayout *cameraLayout;
    QGridLayout *galleryLayout;
    QVBoxLayout *resultLayout;
    //buttons:
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *actionButton;
    //camera layout:
    QLabel *cameraLabel;
    //gallery layout:
    QLabel *galleryLabel;
    QTableWidget *galleryTable;
    QList<QString> galleryList;
    //result layout:
    QScrollArea *resultArea;
    QLabel *resultImage;
    QLabel *resultLabel;
    QString resultFile;
    //QImage *resultImage;
    enum state {CAMERA, GALLERY, RESULT};
    state status;
};

#endif // MAINLAYOUT_H
