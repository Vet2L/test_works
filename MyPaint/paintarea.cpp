#include "paintarea.h"
#include <QPainter>
#include <QMouseEvent>

PaintArea::PaintArea(QWidget *parent) :
    QWidget(parent),
    toDraw(PENCIL),
    theImage(600, 400, QImage::Format_RGB32),
    color(Qt::black),
    thickness(1),
    fillFigure(false),
    lastPosition(-1, -1)
{
    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_NoBackground);

    theImage.fill(qRgb(255, 255, 255));
}

void PaintArea::newImage(const QSize &size)
{
    QImage image = QImage(size, QImage::Format_RGB32);
    image.fill(qRgb(255,255,255));
    setImage(image);
}

bool PaintArea::openImage(const QString &filename)
{
    QImage image;
    if (!image.load(filename))
        return false;

    setImage(image);
    return true;
}

bool PaintArea::saveImage(const QString &filename/*, const char *fileFormat*/)
{
    return theImage.save(filename/*, fileFormat*/);
}

void PaintArea::setImage(const QImage &image)
{
    theImage = image.convertToFormat(QImage::Format_RGB32);
    resize(theImage.size());
    update();
    updateGeometry();
}

void PaintArea::setBrushColor(const QColor &color)
{
    this->color = color;
}

void PaintArea::setBrushWidth(int width)
{
    this->thickness = width;
}

void PaintArea::pencilTool()
{
    this->toDraw = PENCIL;
}

void PaintArea::lineTool()
{
    this->toDraw = LINE;
}

void PaintArea::rectangleTool()
{
    this->toDraw = RECTANGLE;
}

void PaintArea::ellipseTool()
{
    this->toDraw = ELLIPSE;
}

void PaintArea::setFillFigure(bool toFill)
{
    this->fillFigure = toFill;
}

QImage PaintArea::image() const
{
    return theImage;
}

QColor PaintArea::brushColor() const
{
    return color;
}

int PaintArea::brushWidth() const
{
    return thickness;
}

QSize PaintArea::sizeHint() const
{
    return theImage.size();
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), theImage);
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPainter painter(&theImage);
        setupPainter(painter);
        if (toDraw!=ELLIPSE)
        {
            painter.drawPoint(event->pos());
        }
        update();
        lastPosition = event->pos();
    }
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && lastPosition != QPoint(-1, -1))
    {
        QPainter painter(&theImage);
        setupPainter(painter);
        switch (toDraw) {
        case PENCIL:
            painter.drawLine(lastPosition, event->pos());
            lastPosition = event->pos();
            break;
        default:
            break;
        }
        update();
    }
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && lastPosition != QPoint(-1, -1))
    {
        QPainter painter(&theImage);
        setupPainter(painter);
        switch (toDraw) {
        case LINE:
            painter.drawLine(lastPosition, event->pos());
            break;
        case RECTANGLE:
            painter.drawRect(QRect(lastPosition, event->pos()));
            break;
        case ELLIPSE:
            painter.drawEllipse(QRect(lastPosition, event->pos()));
            break;
        default:
            break;
        }
        update();
        lastPosition = QPoint(-1, -1);
    }
}

void PaintArea::setupPainter(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    switch (toDraw) {
    case RECTANGLE:
        painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
        break;
    default:
        painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        break;
    }
    if (fillFigure)
    {
        QBrush brush = painter.brush();
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
    }
}

