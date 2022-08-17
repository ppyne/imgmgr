#ifndef DIALOGNEW_H
#define DIALOGNEW_H

#include <QDialog>
#include "fimage.h"
#include "mdisubwindow.h"
#include "fcolor.h"

namespace Ui {
class DialogNew;
}

class DialogNew : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNew(QWidget *parent = 0);
    ~DialogNew();
    QString name();
    int documentWidth();
    int documentHeight();
    int resolution();
    FImage::ImageMode mode();
    MdiSubWindow::Background backgroundType();
    FColor backgroundColor();
    QString profileName();
private:
    Ui::DialogNew *ui;
};

#endif // DIALOGNEW_H
