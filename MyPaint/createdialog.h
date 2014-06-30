/*
 * Dialogue for create a new image.
 * Specifies the image size.
 */

#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H

#include <QWidget>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>

class createDialog : public QWidget
{
    Q_OBJECT
public:
    explicit createDialog(QWidget *parent = 0);
    ~createDialog();

    /* Open this dialog */
    void open();
    /* Return the size of a new image and close this dialogue */
    QSize getNewImageSize();

signals:
    /* It's used by parent to get "accept" signal */
    void acceptedToCreate();

public slots:
    /* Close dialogue. Button "Cancel" */
    void reject();

private:
    /* OK & Cancel buttons */
    QDialogButtonBox *buttons;

    /* Layouts */
    QVBoxLayout   *mainLayout;
    QHBoxLayout  *widthLayout;
    QHBoxLayout *heightLayout;

    /* Labels */
    QLabel  *widthLabel;
    QLabel *heightLabel;

    /* Spin boxes to get image size */
    QSpinBox  *widthSpinBox;
    QSpinBox *heightSpinBox;
};

#endif // CREATEDIALOG_H
