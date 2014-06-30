/*
 * Main widget (window) that contain menu,
 * tool buttons and drawing area.
 */

#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QColorDialog>
#include <QFileDialog>
#include <QScrollArea>
#include <QCheckBox>
#include "paintarea.h"
#include "createdialog.h"

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = 0);
    ~PaintWidget();

public slots:
    /* Opens dialogue for color choice */
    void openColorDialog();

    /* Opens dialogue for creating a new image */
    void openNewImageDialog();

    /* Opens dialogue for choice image file.
     * Load image from file. */
    void openImageDialog();

    /* Opens dialogue for choice image file.
     * Saves image to a file. */
    void saveImageDialog();

    /* Creates new image. */
    void createNewImage();

    /* Show current color. */
    void setShowColor(const QColor &color);

private:
    /* Initialisations of parts */
    void initLeftInterface(); //Left part of UI that contain buttons and settings of tools
    void       initMenuBar(); //Menu part of UI

    /* Menu */
    QMenuBar  *menuBarPaint;
    QMenu    *fileMenuPaint;
    /* File -> New; Open; Save; |; Quit; */

    /* Buttons */
    QPushButton       *penToolButton; //pen
    QPushButton      *lineToolButton; //line
    QPushButton *rectangleToolButton; //rectangle
    QPushButton   *ellipseToolButton; //ellipse
    QPushButton     *colorToolButton; //color choice

    /* Information and settings of drawing tools. */
    QPalette    curColorPalette; //current color palette, using for label
    QLabel       *curColorLabel; //information about current color
    QLabel      *thicknessLabel; //text label: "Thickness"
    QSpinBox  *thicknessSpinBox; //set thickness lvl
    QCheckBox   *filledCheckBox; //set figure fill attribute

    /* Actions */
    QAction      *newImageAction;  //new picture
    QAction     *openImageAction;  //open picture(file)
    QAction     *saveImageAction;  //save picture(file)
    QAction          *quitAction;  //quit

    /* Layouts */
    QHBoxLayout         *mainLayout; //Full layout
    QVBoxLayout *paintButtonsLayout; //Left part

    /* Area for drawing */
    QScrollArea *paintRenderScrollArea; //Scrolls for image
    PaintArea             *paintRender; //Main area for drawing

    /* Dialogues */
    QColorDialog *paintColorDialog; //Color choice
    createDialog   *newImageDialog; //dialogue for get new image size

    /* Name of file */
    QString filenameOfImage;
};

#endif // PAINTWIDGET_H
