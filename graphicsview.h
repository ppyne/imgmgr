#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QShowEvent>
#include <QBrush>
#include "zoombox.h"
#include <QStringList>
#include <QPen>
#include <QTimer>

class GraphicsView : public QGraphicsView {
    Q_OBJECT
public:
    typedef enum {
        ToolNone,
        ToolDirectSelection, /* A */
        ToolZoom, /* Z */
        ToolHand /* H */
    } ToolType;
    GraphicsView(QWidget *parent = 0);
    GraphicsView(QGraphicsScene *scene, QWidget *parent = 0);
    ToolType tool();
    void scale(qreal s);

public slots:
    void setTool(GraphicsView::ToolType _tool);
    void scaleEntryChanged(qreal s);
    void zoomIn();
    void zoomOut();
    void zoom100();
    void fitView();
    void zoomPrint();
protected:
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void showEvent(QShowEvent *event);
private:
    ToolType Tool;
    void setAlt(bool _alt);
    bool alt();
    bool Alt;
    ZoomBox *ZoomEntry;
    ToolType PreviousTool;
    qreal CurrentScale;
    QBrush BackgroundBrush;
    void _init();
    qreal nextUpperScale();
    qreal nextLowerScale();
    bool Zoom;
    bool ZoomRect;
    QPen ZoomPen;
    qreal ZoomPenOffset;
    QPoint A;
    QPoint B;
    void fitInView(const QRectF &rect);
    QTimer *ZoomTimer;
    bool Shown;
private slots:
    void animateZoomRect();
signals:
    void scaleChanged(qreal scale);

};

#endif // GRAPHICSVIEW_H
