#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QImage>
#include <QLabel>

class MainLayout : public QWidget
{
    Q_OBJECT
    
public:
    MainLayout(QWidget *parent = 0);
    ~MainLayout();

public slots:
    void toHorizontalLayout();
    void toVerticalLayout();
    void toCamera();
    void toGallery();
    void toResult();

private:
    //functions:
    void createHorizontalLayout();
    void createVerticalLayout();
    void initElements();
    void initCamera();
    void initGallery();
    void initResult();
    void deleteCamera();
    void deleteGallery();
    void deleteResult();
    //horizontal layout:
    QHBoxLayout *mainHLayout;
    QVBoxLayout *leftVLayout;
    QVBoxLayout *rightVLayout;
    //vertical layout:
    QVBoxLayout *mainVLayout;
    QHBoxLayout *bottomHLayout;
    //central
    QWidget *centralWidget;
    //functionality layouts:
    QVBoxLayout *cameraLayout;
    QVBoxLayout *galleryLayout;
    QVBoxLayout *resultLayout;
    //buttons:
    QPushButton *leftButton;
    QPushButton *rightButton;
    //camera layout:
    QLabel *cameraLabel;
    //gallery layout:
    QLabel *galleryLabel;
    //result layout:
    QLabel *resultLabel;
    //QImage *resultImage;
    enum state {CAMERA, GALLERY, RESULT};
    state status;
};

#endif // MAINLAYOUT_H
