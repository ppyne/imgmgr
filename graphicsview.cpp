#include "graphicsview.h"
#include <QDebug>
#include <QPainter>
#include <QRegion>
#include <QRectF>
#include <QPointF>
#include <QGraphicsItem>
#include <QScrollBar>
#include <QFont>
#include <QStyleFactory>
#include <QTransform>
#include <QMessageBox>
#include <QVector>
#include <QLineF>
#include <QVector>
#include "mdisubwindow.h"

#define D066 (qreal)(2.0 / 3.0)
#define D033 (qreal)(1.0 / 3.0)
#define D016 (qreal)(1.0 / 6.0)
#define D008 (qreal)(1.0 / 12.0)

#define MINSCALE 0.001
#define MAXSCALE 32.0

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {
    _init();
}

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent) {
    _init();
}

void GraphicsView::_init() {
    //qDebug() << "GraphicsView::GraphicsView()";
    Shown = false;

    BackgroundBrush.setTextureImage(QImage(":/resources/images/damier.png"));

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    Tool = GraphicsView::ToolDirectSelection;
    setCursor(Qt::ArrowCursor);
    PreviousTool = GraphicsView::ToolNone;

    ZoomEntry = new ZoomBox();
    connect(this, SIGNAL(scaleChanged(qreal)), ZoomEntry, SLOT(scaleChanged(qreal)));
    connect(ZoomEntry, SIGNAL(scaleEntryChanged(qreal)), this, SLOT(scaleEntryChanged(qreal)));
    addScrollBarWidget(ZoomEntry, Qt::AlignLeft);

    Alt = false;
    CurrentScale = 1.0;
    //qDebug() << static_cast<MdiSubWindow *>(scene()->parent())->windowTitle() << " emit GraphicsView::scaleChanged( 1.0 )";
    emit scaleChanged(1.0);

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ZoomRect = false;
    Zoom = false;
    ZoomPen = QPen(QColor(0xEF, 0xEF, 0xEF), 1.0);
    QVector <qreal>v;
    v.append(4.0);
    v.append(4.0);
    ZoomPen.setDashPattern(v);
    ZoomPenOffset = 7.0;

    ZoomTimer = new QTimer(this);
    ZoomTimer->setInterval(50);
    connect(ZoomTimer, SIGNAL(timeout()), this, SLOT(animateZoomRect()));
}

qreal GraphicsView::nextUpperScale() {
    if (CurrentScale >= 16.0) {
        return 32.0;
    } else if (CurrentScale >= 12.0) {
        return 16.0;
    } else if (CurrentScale >= 8.0) {
        return 12.0;
    } else if (CurrentScale >= 6.0) {
        return 8.0;
    } else if (CurrentScale >= 5.0) {
        return 6.0;
    } else if (CurrentScale >= 4.0) {
        return 5.0;
    } else if (CurrentScale >= 3.0) {
        return 4.0;
    } else if (CurrentScale >= 2.0) {
        return 3.0;
    } else if (CurrentScale >= 1.0) {
        return 2.0;
    } else if (CurrentScale >= D066) {
        return 1.0;
    } else if (CurrentScale >= 0.5) {
        return D066;
    } else if (CurrentScale >= D033) {
        return 0.5;
    } else if (CurrentScale >= 0.25) {
        return D033;
    } else if (CurrentScale >= D016) {
        return 0.25;
    } else if (CurrentScale >= 0.125) {
        return D016;
    } else if (CurrentScale >= D008) {
        return 0.125;
    } else if (CurrentScale >= 0.0625) {
        return D008;
    } else if (CurrentScale >= 0.05) {
        return 0.0625;
    } else if (CurrentScale >= 0.04) {
        return 0.05;
    } else if (CurrentScale >= 0.03) {
        return 0.04;
    } else if (CurrentScale >= 0.02) {
        return 0.03;
    } else if (CurrentScale >= 0.015) {
        return 0.02;
    } else if (CurrentScale >= 0.01) {
        return 0.015;
    } else if (CurrentScale >= 0.0075) {
        return 0.01;
    } else if (CurrentScale >= 0.005) {
        return 0.0075;
    } else if (CurrentScale >= 0.004) {
        return 0.005;
    } else if (CurrentScale >= 0.003) {
        return 0.004;
    } else if (CurrentScale >= 0.002) {
        return 0.003;
    } else if (CurrentScale >= 0.001) {
        return 0.002;
    }
    return 0.001;
}

qreal GraphicsView::nextLowerScale() {
    if (CurrentScale <= 0.002) {
        return 0.001;
    } else if (CurrentScale <= 0.003) {
        return 0.002;
    } else if (CurrentScale <= 0.004) {
        return 0.003;
    } else if (CurrentScale <= 0.005) {
        return 0.004;
    } else if (CurrentScale <= 0.0075) {
        return 0.005;
    } else if (CurrentScale <= 0.01) {
        return 0.0075;
    } else if (CurrentScale <= 0.015) {
        return 0.01;
    } else if (CurrentScale <= 0.02) {
        return 0.015;
    } else if (CurrentScale <= 0.03) {
        return 0.02;
    } else if (CurrentScale <= 0.04) {
        return 0.03;
    } else if (CurrentScale <= 0.05) {
        return 0.04;
    } else if (CurrentScale <= 0.0625) {
        return 0.05;
    } else if (CurrentScale <= D008) {
        return 0.0625;
    } else if (CurrentScale <= 0.125) {
        return D008;
    } else if (CurrentScale <= D016) {
        return 0.125;
    } else if (CurrentScale <= 0.25) {
        return D016;
    } else if (CurrentScale <= D033) {
        return 0.25;
    } else if (CurrentScale <= 0.5) {
        return D033;
    } else if (CurrentScale <= D066) {
        return 0.5;
    } else if (CurrentScale <= 1.0) {
        return D066;
    } else if (CurrentScale <= 2.0) {
        return 1.0;
    } else if (CurrentScale <= 3.0) {
        return 2.0;
    } else if (CurrentScale <= 4.0) {
        return 3.0;
    } else if (CurrentScale <= 5.0) {
        return 4.0;
    } else if (CurrentScale <= 6.0) {
        return 5.0;
    } else if (CurrentScale <= 8.0) {
        return 6.0;
    } else if (CurrentScale <= 12.0) {
        return 8.0;
    } else if (CurrentScale <= 16.0) {
        return 12.0;
    } else if (CurrentScale <= 32.0) {
        return 16.0;
    }
    return 32.0;
}

void GraphicsView::animateZoomRect() {
    if (ZoomPenOffset == 0.0) ZoomPenOffset = 7.0;
    else ZoomPenOffset--;
    viewport()->repaint();
}

void GraphicsView::paintEvent(QPaintEvent *event) {

    QPainter painter;
    painter.begin(viewport());
    painter.fillRect(event->rect(), BackgroundBrush);
    painter.end();

    QGraphicsView::paintEvent(event);

    if (CurrentScale >= 6.0) {
        QVector<QLineF> lines;

        for (qreal x = 1.0; x < sceneRect().width(); x += 1.0) {
            QPoint top = mapFromScene(x, 0);
            QPoint bottom = mapFromScene(x, sceneRect().height());
            QLineF line(top, bottom);
            lines.append(line);
        }
        for (qreal y = 1.0; y < sceneRect().height(); y += 1.0) {
            QPoint top = mapFromScene(0, y);
            QPoint bottom = mapFromScene(sceneRect().width(), y);
            QLineF line(top, bottom);
            lines.append(line);
        }
        painter.begin(viewport());
        painter.setPen(Qt::white);
        painter.setOpacity(0.25);
        painter.drawLines(lines.data(), lines.size());
        painter.end();
    }

    QPointF topleft = mapFromScene(QPointF(0, 0));
    QPointF bottomright = mapFromScene(QPointF(sceneRect().width(), sceneRect().height()));
    QRectF visiblerect(topleft, bottomright);

    painter.begin(viewport());
    QRegion mask = event->region().subtracted(QRegion(visiblerect.toRect()));
    painter.setClipRegion(mask);
    painter.fillRect(event->rect(), QColor(0x80, 0x80, 0x80));
    painter.end();

    if (ZoomRect) {
        painter.begin(viewport());
        painter.setCompositionMode(QPainter::CompositionMode_Difference);
        ZoomPen.setDashOffset(ZoomPenOffset);
        painter.setPen(ZoomPen);
        painter.drawRect(QRect(A, B));
        painter.end();
    }
}

void GraphicsView::setTool(GraphicsView::ToolType _tool) {
    //qDebug() << _tool;
    Tool = _tool;
    if (tool() == GraphicsView::ToolZoom) {
        if (CurrentScale == MAXSCALE) setCursor(QCursor(QPixmap(":/resources/cursors/curs_zoomlimit.png"), 20, 20));
        else setCursor(QCursor(QPixmap(":/resources/cursors/curs_zoomin.png"), 20, 20));
    } else if (tool() == GraphicsView::ToolHand) setCursor(Qt::OpenHandCursor);
    else setCursor(Qt::ArrowCursor);
}

GraphicsView::ToolType GraphicsView::tool() {
    return Tool;
}

void GraphicsView::keyPressEvent(QKeyEvent *event) {
    if (Qt::Key(event->key()) == Qt::Key_Space && PreviousTool == 0) {
        PreviousTool = tool();
        setTool(GraphicsView::ToolHand);
    }
    if (Qt::Key(event->key()) == Qt::Key_Alt) {
        setAlt(true);
    }
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event) {
    if (Qt::Key(event->key()) == Qt::Key_Alt) {
        setAlt(false);
    }
    if (Qt::Key(event->key()) == Qt::Key_Space && PreviousTool != 0) {
        setTool(PreviousTool);
        PreviousTool = GraphicsView::ToolNone;
    }
}

void GraphicsView::setAlt(bool _alt) {
    Alt = _alt;
    if (alt() == true) {
        if (tool() == GraphicsView::ToolZoom) {
            if (CurrentScale == MINSCALE) setCursor(QCursor(QPixmap(":/resources/cursors/curs_zoomlimit.png"), 20, 20));
            else setCursor(QCursor(QPixmap(":/resources/cursors/curs_zoomout.png"), 20, 20));
        }
    } else {
        if (tool() == GraphicsView::ToolZoom) {
            if (CurrentScale == MAXSCALE) setCursor(QCursor(QPixmap(":/resources/cursors/curs_zoomlimit.png"), 20, 20));
            else setCursor(QCursor(QPixmap(":/resources/cursors/curs_zoomin.png"), 20, 20));
        }
    }
}

bool GraphicsView::alt() {
    return Alt;
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (tool() == GraphicsView::ToolHand) {
            setDragMode (QGraphicsView::ScrollHandDrag);
        } else if (tool() == GraphicsView::ToolZoom) {
            Zoom = true;
            A = event->pos();
        } else if (tool() == GraphicsView::ToolDirectSelection) {
            QPointF pos = mapToScene(event->pos());
            QGraphicsItem *item = scene()->itemAt(pos, QGraphicsView::transform());
            if (item != 0) {
                qDebug() << item->data(0).toString();
            } else {
                qDebug() << "no item";
            }
        }
    }
    QGraphicsView::mousePressEvent (event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (tool() == GraphicsView::ToolHand) {
            setDragMode (QGraphicsView::NoDrag);
        } else if (tool() == GraphicsView::ToolZoom) {
            if (ZoomRect) {
                B = event->pos();
                QRect r(A, B);
                if (!r.isValid()) r = r.normalized();
                fitInView(QRectF(mapToScene(r.topLeft()), mapToScene(r.bottomRight())));
                ZoomRect = false;
                if (ZoomTimer->isActive()) ZoomTimer->stop();
            } else {
                if (alt() == true) {
                    scale(nextLowerScale());
                } else {
                    scale(nextUpperScale());
                }
            }
            Zoom = false;
        }
    }
    QGraphicsView::mouseReleaseEvent (event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (Zoom) {
        B = event->pos();
        if (ZoomRect == false && CurrentScale < MAXSCALE && CurrentScale > MINSCALE) {
            QRect r(A, B);
            if (!r.isValid()) r = r.normalized();
            if (r.size().width() > 1 && r.size().height() > 1) {
                ZoomRect = true;
                ZoomTimer->start();
            }
        } else {
            viewport()->repaint();
        }
    }
    QGraphicsView::mouseMoveEvent (event);
}

void GraphicsView::scale(qreal s) {
    //qDebug() << static_cast<MdiSubWindow *>(scene()->parent())->windowTitle() << " GraphicsView::scale(" << s << ")";
    CurrentScale = s;
    QTransform t;
    t.scale(CurrentScale, CurrentScale);
    setTransform(t);
    if (tool() == GraphicsView::ToolZoom) {
        if (CurrentScale == MINSCALE || CurrentScale == MAXSCALE) setCursor(QCursor(QPixmap(":/resources/cursors/curs_zoomlimit.png"), 20, 20));
        else {
            if (alt() == true) {
                setCursor(QCursor(QPixmap(":/resources/cursors/curs_zoomout.png"), 20, 20));
            } else {
                setCursor(QCursor(QPixmap(":/resources/cursors/curs_zoomin.png"), 20, 20));
            }
        }
    }
    //qDebug() << static_cast<MdiSubWindow *>(scene()->parent())->windowTitle() << " emit GraphicsView::scaleChanged(" << CurrentScale << ")";
    emit scaleChanged(CurrentScale);
}

void GraphicsView::scaleEntryChanged(qreal s) {
    //qDebug() << static_cast<MdiSubWindow *>(scene()->parent())->windowTitle() << " GraphicsView::scaleEntryChanged(" << s << ")";
    if (s == 0.0) {
        //qDebug() << static_cast<MdiSubWindow *>(scene()->parent())->windowTitle() << " emit GraphicsView::scaleChanged(" << CurrentScale << ")";
        emit scaleChanged(CurrentScale);
        QMessageBox::critical(this, tr("Invalid number"), tr("A valid number between 0.1% and 3200.0% is required."), QMessageBox::Ok, QMessageBox::Ok);
    } else {
        if (s > MAXSCALE) s = MAXSCALE;
        if (s < MINSCALE) s = MINSCALE;
        scale(s);
    }
}

void GraphicsView::showEvent(QShowEvent *event) {
    //qDebug() << " GraphicsView::showEvent(" << event << ")";
    Q_UNUSED(event);
    if (!Shown) {
        QSizeF d(sceneRect().width(), sceneRect().height());
        QSizeF b(viewport()->size());
        qreal r = 1.0;
        if (d.width() / d.height() > b.width() / b.height()) {
          r = b.width() / d.width();
        } else {
          r = b.height() / d.height();
        }
        if (r < 1.0) {
            CurrentScale = r;
            scale(nextLowerScale());
        }
        Shown = true;
    }
}

void GraphicsView::zoomIn() {
    scale(nextUpperScale());
}
void GraphicsView::zoomOut() {
    scale(nextLowerScale());
}
void GraphicsView::zoom100() {
    scale(1.0);
}
void GraphicsView::fitView() {
    //qDebug() << static_cast<MdiSubWindow *>(scene()->parent())->windowTitle() << " GraphicsView::fitView()";
    QSizeF d(sceneRect().width(), sceneRect().height());
    QSizeF b(viewport()->size());
    qreal r = 1.0;
    if (d.width() / d.height() > b.width() / b.height()) {
      r = b.width() / d.width();
    } else {
      r = b.height() / d.height();
    }
    scale(r);
}

void GraphicsView::zoomPrint() {
    // 72 / 240dpi = 30;
}

void GraphicsView::fitInView(const QRectF &rect) {
    //qDebug() << static_cast<MdiSubWindow *>(scene()->parent())->windowTitle() << " GraphicsView::fitInView(" << rect << ")";
    // Reset the view scale to 1:1.
    scale(1.0);

    // Find the ideal x / y scaling ratio to fit \a rect in the view.
    QRectF viewRect = viewport()->rect();
    if (viewRect.isEmpty()) return;
    QRectF sceneRect = transform().mapRect(rect);
    if (sceneRect.isEmpty()) return;
    qreal xratio = viewRect.width() / sceneRect.width();
    qreal yratio = viewRect.height() / sceneRect.height();

    //case Qt::KeepAspectRatio:
    qreal s = qMin(xratio, yratio);

    if (s > MAXSCALE) s = MAXSCALE;
    if (s < MINSCALE) s = MINSCALE;

    // Scale and center on the center of \a rect.
    scale(s);
    centerOn(rect.center());
}
