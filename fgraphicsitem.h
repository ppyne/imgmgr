#ifndef FGRAPHICSITEM_H
#define FGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QString>
#include "fimage.h"

class FGraphicsItem : public QGraphicsItem {
public:
    typedef enum {
        DataName
    } DataType;
    FGraphicsItem(QString name, FImage *image);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    FImage *Image;
};

#endif // FGRAPHICSITEM_H
