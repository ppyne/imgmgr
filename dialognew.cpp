#include "dialognew.h"
#include "ui_dialognew.h"

DialogNew::DialogNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNew)
{
    ui->setupUi(this);
}

DialogNew::~DialogNew()
{
    delete ui;
}

QString DialogNew::name() {
    return ui->lineEditName->text().trimmed();
}
int DialogNew::documentWidth() {
    return ui->lineEditWidth->text().toInt();
}
int DialogNew::documentHeight() {
    return ui->lineEditHeight->text().toInt();
}
int DialogNew::resolution() {
    return ui->lineEditResolution->text().toInt();
}
FImage::ImageMode DialogNew::mode() {
    switch (ui->comboBoxMode->currentIndex()) {
        case 0:
            return FImage::Bitmap;
        case 1:
            return FImage::Grayscale;
        case 3:
            return FImage::CMYK;
    }
    return FImage::RGB;
}
MdiSubWindow::Background DialogNew::backgroundType() {
    if (ui->comboBoxBackground->currentIndex() == 1) return MdiSubWindow::Transparent;
    return MdiSubWindow::Color;
}
FColor DialogNew::backgroundColor() {
    return Qt::white;
}

QString DialogNew::profileName() {
    return ui->comboBoxColorProfile->currentText();
}
