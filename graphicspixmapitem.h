#ifndef GRAPHICSPIXMAPITEM_H
#define GRAPHICSPIXMAPITEM_H
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include "image.h"

class GraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
    typedef enum {
        DataName,
        DataResolution
    } DataType;
    GraphicsPixmapItem(QGraphicsItem *parent = Q_NULLPTR) : QGraphicsPixmapItem(parent) {}
    GraphicsPixmapItem(const QPixmap &pixmap, QString name, qint32 resolution, QGraphicsItem *parent = Q_NULLPTR);
};

#endif // GRAPHICSPIXMAPITEM_H
