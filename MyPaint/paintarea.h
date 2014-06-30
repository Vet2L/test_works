/*
 * Area for drawing image.
 */

#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QImage>
#include <QColor>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    /* List of figures that can be drawn */
    enum figure{PENCIL, LINE, RECTANGLE, ELLIPSE};

    PaintArea(QWidget *parent = 0);

    /* Creates a new image of "size" */
    void newImage(const QSize &size);

    /* Reads an image from file "filename" */
    bool openImage(const QString &filename);

    /* Saves an image to file "filename" */
    bool saveImage(const QString &filename);

    /* Draws a loaded image */
    void setImage(const QImage &image);

    /* Returns the current image */
    QImage image() const;

    /* Returns the current color */
    QColor brushColor() const;

    /* Returns the current thickness of line */
    int brushWidth() const;

    /* Returns the current size of image */
    QSize sizeHint() const;

public slots:
    /* Set a color of line */
    void setBrushColor(const QColor &color);

    /* Set a thickness of line */
    void setBrushWidth(int width);

    /* Sets a pencil as drawing tool */
    void pencilTool();

    /* Sets a line as drawing tool */
    void lineTool();

    /* Sets a rectangle as drawing tool */
    void rectangleTool();

    /* Sets a ellipse as drawing tool */
    void ellipseTool();

    /* Sets "fill" attribute to a drawing tool */
    void setFillFigure(bool toFill);

protected:
    /* Overloaded functions */

    /* Draw the image */
    void paintEvent(QPaintEvent *event);

    /* If mouse pressed */
    void mousePressEvent(QMouseEvent *event);

    /* If mouse moved */
    void mouseMoveEvent(QMouseEvent *event);

    /* If mouse released */
    void mouseReleaseEvent(QMouseEvent *event);

private:
    /* Setup style of drawing tool */
    void setupPainter(QPainter &painter);

    figure  toDraw;         //Drawing tool (DT)
    QImage  theImage;       //Current image
    QColor  color;          //Color of DT
    int     thickness;      //Thickness of DT
    bool    fillFigure;     //Fill attribute of DT
    QPoint  lastPosition;   //Last position of mouse (coordinates)
};

#endif // PAINTAREA_H
