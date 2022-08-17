#include "graphicspixmapitem.h"

GraphicsPixmapItem::GraphicsPixmapItem(const QPixmap &pixmap, QString name, qint32 resolution, QGraphicsItem *parent) : QGraphicsPixmapItem(pixmap, parent) {
     setData(GraphicsPixmapItem::DataName, QVariant(name));
     setData(GraphicsPixmapItem::DataResolution, resolution);
}

