#include "fgraphicsitem.h"
#include <QPen>
#include <QColor>
#include <QDebug>

FGraphicsItem::FGraphicsItem(QString name, FImage *image) {
    setData(FGraphicsItem::DataName, QVariant(name));
    Image = image;
}

QRectF FGraphicsItem::boundingRect() const {
    return QRectF(0.0, 0.0, (qreal)Image->width(), (qreal)Image->height());
}

void FGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    for (int y = 0; y < Image->height(); y++) {
        unsigned char *row = Image->scanRow(y);
        for (int x = 0; x < Image->width(); x++) {
            painter->fillRect(x, y, 1, 1, Image->rgb(row, x));
        }
    }
}
