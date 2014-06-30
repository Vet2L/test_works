#include <limits>
#include "createdialog.h"

createDialog::createDialog(QWidget *parent) :
    QWidget(parent)
{
    widthLabel  = new QLabel(tr("Width: "), this);
    heightLabel = new QLabel(tr("Height:"), this);

    widthSpinBox = new QSpinBox(this);
    widthSpinBox->setMinimum(1);
    widthSpinBox->setMaximum(std::numeric_limits<int>::max());

    heightSpinBox = new QSpinBox(this);
    heightSpinBox->setMinimum(1);
    heightSpinBox->setMaximum(std::numeric_limits<int>::max());

    buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    /* OK: we can get size of a new image */
    connect(buttons, SIGNAL(accepted()), this, SIGNAL(acceptedToCreate()));
    /* Cancel: just close this dialogue */
    connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));

    mainLayout   = new QVBoxLayout(this);
    widthLayout  = new QHBoxLayout();
    heightLayout = new QHBoxLayout();

    widthLayout->addWidget(widthLabel);
    widthLayout->addStretch();
    widthLayout->addWidget(widthSpinBox);

    heightLayout->addWidget(heightLabel);
    heightLayout->addStretch();
    heightLayout->addWidget(heightSpinBox);

    mainLayout->addLayout(widthLayout);
    mainLayout->addLayout(heightLayout);
    mainLayout->addWidget(buttons);

    setLayout(mainLayout);

    /* Hide this dialogue after creation. Use "open()" to open dialogue. -_-  */
    hide();
}

createDialog::~createDialog()
{
    delete heightLayout;
    delete widthLayout;
}

void createDialog::open()
{
    this->show();
}

QSize createDialog::getNewImageSize()
{
    this->close();
    return QSize(widthSpinBox->value(), heightSpinBox->value());
}

void createDialog::reject()
{
    this->close();
}
