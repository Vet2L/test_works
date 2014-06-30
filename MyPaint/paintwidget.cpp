#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
{
    initMenuBar();
    initLeftInterface();

    newImageDialog = new createDialog();

    /* Connects "accept" signal from dialogue of new image. */
    connect(newImageDialog, SIGNAL(acceptedToCreate()), this, SLOT(createNewImage()));

    mainLayout = new QHBoxLayout(this);

    /* Area for drawing */
    paintRenderScrollArea =                new QScrollArea(this);
    paintRender           = new PaintArea(paintRenderScrollArea);
    paintRenderScrollArea->setBackgroundRole(QPalette::Dark);
    paintRenderScrollArea->setWidget(paintRender);

    /* Connects signals from buttons */
    connect(      penToolButton, SIGNAL(clicked()), paintRender, SLOT(     pencilTool()));
    connect(     lineToolButton, SIGNAL(clicked()), paintRender, SLOT(       lineTool()));
    connect(rectangleToolButton, SIGNAL(clicked()), paintRender, SLOT(  rectangleTool()));
    connect(  ellipseToolButton, SIGNAL(clicked()), paintRender, SLOT(    ellipseTool()));
    connect(    colorToolButton, SIGNAL(clicked()), this       , SLOT(openColorDialog()));

    /* Connects signals from settings of drawing tools */
    connect(thicknessSpinBox, SIGNAL(valueChanged(int)), paintRender, SLOT(setBrushWidth(int)) );
    connect(  filledCheckBox, SIGNAL(toggled(bool))    , paintRender, SLOT(setFillFigure(bool)));

    paintColorDialog = new QColorDialog(paintRender->brushColor(), this);

    /* Connects signal from color choice dialogue */
    connect(paintColorDialog, SIGNAL(colorSelected(QColor)), paintRender, SLOT(setBrushColor(QColor)));
    connect(paintColorDialog, SIGNAL(colorSelected(QColor)), this       , SLOT(setShowColor(QColor)) );

    mainLayout->setMenuBar(menuBarPaint);
    mainLayout->addLayout(paintButtonsLayout, 0);
    mainLayout->addWidget(paintRenderScrollArea, 1);

    this->setLayout(mainLayout);
}

PaintWidget::~PaintWidget()
{
    delete paintButtonsLayout;
    delete newImageDialog;
}

void PaintWidget::openColorDialog()
{
    paintColorDialog->open();
}

void PaintWidget::openNewImageDialog()
{
    newImageDialog->open();
}

void PaintWidget::openImageDialog()
{
    filenameOfImage = QFileDialog::getOpenFileName(this, tr("Open image"), "",
                                                   tr("Image files (*.png *.jpg *.bmp)"));
    paintRender->openImage(filenameOfImage);
}

void PaintWidget::saveImageDialog()
{
    filenameOfImage = QFileDialog::getSaveFileName(this, tr("Save image"), "",
                                                   tr("Image files (*.png *.jpg *.bmp)"));
    paintRender->saveImage(filenameOfImage);
}

void PaintWidget::createNewImage()
{
    QSize size = newImageDialog->getNewImageSize();
    paintRender->newImage(size);
}

void PaintWidget::setShowColor(const QColor &color)
{
    curColorPalette.setColor(curColorLabel->backgroundRole(), color);
    curColorLabel->setPalette(curColorPalette);
}

void PaintWidget::initLeftInterface()
{
    paintButtonsLayout = new QVBoxLayout();

    /* Create buttons */
    penToolButton       = new QPushButton(tr("Pencil")   , this);
    lineToolButton      = new QPushButton(tr("Line")     , this);
    rectangleToolButton = new QPushButton(tr("Rectangle"), this);
    ellipseToolButton   = new QPushButton(tr("Ellipse")  , this);

    colorToolButton     = new QPushButton(tr("Color...") , this);

    /* Information about color */
    curColorLabel = new QLabel(this);
    curColorLabel->setAutoFillBackground(true);

    curColorPalette = curColorLabel->palette();
    curColorPalette.setColor(curColorLabel->backgroundRole(), qRgb(0, 0, 0));
    curColorLabel->setPalette(curColorPalette);

    /* Thickness */
    thicknessLabel = new QLabel(tr("Thickness:"), this);
    thicknessSpinBox = new QSpinBox(this);
    thicknessSpinBox->setMinimum(1);
    thicknessSpinBox->setMaximum(1000);

    /* Filled attribute */
    filledCheckBox = new QCheckBox(tr("Fill"), this);
    filledCheckBox->setChecked(false);

    paintButtonsLayout->addWidget(      penToolButton);
    paintButtonsLayout->addWidget(     lineToolButton);
    paintButtonsLayout->addWidget(rectangleToolButton);
    paintButtonsLayout->addWidget(  ellipseToolButton);
    paintButtonsLayout->addWidget(    colorToolButton);
    paintButtonsLayout->addWidget(      curColorLabel);
    paintButtonsLayout->addWidget(     thicknessLabel);
    paintButtonsLayout->addWidget(   thicknessSpinBox);
    paintButtonsLayout->addWidget(     filledCheckBox);
    paintButtonsLayout->addStretch(1);
}

void PaintWidget::initMenuBar()
{
    menuBarPaint  = new QMenuBar(this);
    fileMenuPaint = new QMenu(tr("&File"), menuBarPaint);

    newImageAction  = new QAction(tr( "New"), this);
    openImageAction = new QAction(tr("Open"), this);
    saveImageAction = new QAction(tr("Save"), this);
    quitAction      = new QAction(tr("Quit"), this);

    /* Gathers actions to menu. */
    fileMenuPaint->addAction( newImageAction);
    fileMenuPaint->addAction(openImageAction);
    fileMenuPaint->addAction(saveImageAction);
    fileMenuPaint->addSeparator();
    fileMenuPaint->addAction(quitAction);

    menuBarPaint->addMenu(fileMenuPaint);

    /* Connects signals from actions */
    connect(newImageAction , SIGNAL(triggered()), this, SLOT(openNewImageDialog()));
    connect(openImageAction, SIGNAL(triggered()), this, SLOT(   openImageDialog()));
    connect(saveImageAction, SIGNAL(triggered()), this, SLOT(   saveImageDialog()));
    connect(quitAction     , SIGNAL(triggered()), this, SLOT(             close()));
}
