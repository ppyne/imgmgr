#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject *parent = 0) : QGraphicsScene(parent) {}
    GraphicsScene(const QRectF &sceneRect, QObject *parent = 0) : QGraphicsScene(sceneRect,parent) {}
    GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0) : QGraphicsScene(x, y, width, height, parent) {}
signals:

public slots:
};

#endif // GRAPHICSSCENE_H
