#-------------------------------------------------
#
# Project created by QtCreator 2013-07-19T01:46:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CGR
TEMPLATE = app
#LIBS += -lopencv_core -lopencv_highgui
#DEPENDPATH += .
#INCLUDEPATH += /usr/include/opencv
ANDROID_OPENCV = ./android/#media/Software/android/OpenCV-2.4/
LIBS += \
$$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_contrib.a \
$$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_legacy.a \
$$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_ml.a \
$$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_objdetect.a \
$$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_calib3d.a \
$$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_video.a \
$$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_features2d.a \
$$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_highgui.a \
$$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_androidcamera.a \
$$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_flann.a \
$$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_imgproc.a \
$$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_core.a \
$$ANDROID_OPENCV/share/OpenCV/3rdparty/libs/armeabi-v7a/liblibjpeg.a \
$$ANDROID_OPENCV/share/OpenCV/3rdparty/libs/armeabi-v7a/liblibpng.a \
$$ANDROID_OPENCV/share/OpenCV/3rdparty/libs/armeabi-v7a/liblibtiff.a \
$$ANDROID_OPENCV/share/OpenCV/3rdparty/libs/armeabi-v7a/liblibjasper.a \
$$ANDROID_OPENCV/share/OpenCV/3rdparty/libs/armeabi-v7a/libtbb.a \
$$ANDROID_OPENCV/share/OpenCV/3rdparty/libs/armeabi-v7a/libIlmImf.a

INCLUDEPATH += ./opencv/include/

CONFIG+=link_pkgconfig PKGCONFIG+=opencv

SOURCES += main.cpp\
        mainlayout.cpp \
        camerawidget.cpp

HEADERS  += mainlayout.h \
         camerawidget.h

CONFIG += mobility
MOBILITY = 

OTHER_FILES += \
    android/AndroidManifest.xml \
    android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
    android/src/org/qtproject/qt5/android/bindings/QtApplication.java \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/res/values-it/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-es/strings.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-ro/strings.xml \
    android/version.xml \
    images/right_arrow.png \
    images/left_arrow.png

RESOURCES += \
    images.qrc

