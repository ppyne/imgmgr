#include "mdisubwindow.h"
#include "graphicspixmapitem.h"
#include <QStandardPaths>
#include <QGuiApplication>
#include <QFileInfo>
#include <QDebug>
#include <QPixelFormat>
#include <QColor>
#include "fcolor.h"
#include "fgraphicsitem.h"

MdiSubWindow::MdiSubWindow(QActionGroup *tools, QWidget *parent, Qt::WindowFlags flags) : QMdiSubWindow(parent, flags) {
    connect(this, SIGNAL(windowStateChanged(Qt::WindowStates, Qt::WindowStates)), this, SLOT(onWindowStateChanged(Qt::WindowStates, Qt::WindowStates)));
    setAttribute(Qt::WA_DeleteOnClose);
    Tools = tools;
    //onToolsTriggered(Tools->checkedAction());
    Scene = new GraphicsScene(this);
    View = new GraphicsView(Scene, this);
    connect(this, SIGNAL(toolChanged(GraphicsView::ToolType)), View, SLOT(setTool(GraphicsView::ToolType)));
    setWidget(View);
    //connect(Tools, SIGNAL(triggered(QAction*)), this, SLOT(onToolsTriggered(QAction*)));
    //emit Tools->triggered(Tools->checkedAction());
}

void MdiSubWindow::onToolsTriggered(QAction *action) {
    //qDebug() << "MdiSubWindow::onToolsTriggered" << action->objectName();
    if (action->objectName() == "actionToolbarCursor")
        emit toolChanged(GraphicsView::ToolDirectSelection);
    else if (action->objectName() == "actionToolbarHand")
        emit toolChanged(GraphicsView::ToolHand);
    else if (action->objectName() == "actionToolbarZoom")
        emit toolChanged(GraphicsView::ToolZoom);
}

void MdiSubWindow::loadImage(const QString &path, const QImage &image) {
    //qDebug() << "MdiSubWindow::loadImage(" << path << ")";
    Path = path;
    _Image = image.copy();
    setWindowTitle(QFileInfo(Path).fileName());
    GraphicsPixmapItem *pixmapitem = new GraphicsPixmapItem(QPixmap::fromImage(_Image), "Background", _Image.resolution());
    Scene->addItem(pixmapitem);
    View->setSceneRect(0, 0, _Image.width(), _Image.height());
    View->show();
}

void MdiSubWindow::newImage(const QString &name, int width, int height, int resolution, FImage::ImageMode mode, MdiSubWindow::Background bg, FColor bgcolor, QString profile) {
    Q_UNUSED(bgcolor)
    setWindowTitle(name);

    FImage *image = new FImage(width, height, resolution, mode, profile);
    qDebug() << image->mode();
    if (bg == Background::Color) {
        qDebug() << "color";
        for (int y = 0; y < image->height(); y++) {
            unsigned char *row = image->scanRow(y);
            for (int x = 0; x < image->width(); x++) {
                unsigned char *col = image->scanCol(row, x);
                for (int c = 0; c < image->channels(); c ++) {
                    unsigned char *chan = image->scanChan(col, c);
                    if (image->mode() == FImage::Bitmap) {
                        switch(c) {
                            case FImage::Channel_BM_Black:
                                *chan = 0xFF;
                                break;
                            case FImage::Channel_BM_Alpha:
                                *chan = 0xFF;
                                break;
                        }
                    } else if (image->mode() == FImage::Grayscale) {
                        switch(c) {
                            case FImage::Channel_GS_Gray:
                                *chan = 0xFF;
                                break;
                            case FImage::Channel_GS_Alpha:
                                *chan = 0xFF;
                                break;
                        }
                    } else if (image->mode() == FImage::RGB) {
                        switch(c) {
                            case FImage::Channel_RGB_Red:
                                *chan = 0xFF;
                                break;
                            case FImage::Channel_RGB_Green:
                                *chan = 0x00;
                                break;
                            case FImage::Channel_RGB_Blue:
                                *chan = 0x00;
                                break;
                            case FImage::Channel_RGB_Alpha:
                                *chan = 0xFF;
                                break;
                        }
                    } else if (image->mode() == FImage::CMYK) {
                        switch(c) {
                            case FImage::Channel_CMYK_Cyan:
                                *chan = 0x00;
                                break;
                            case FImage::Channel_CMYK_Magenta:
                                *chan = 0xFF;
                                break;
                            case FImage::Channel_CMYK_Yellow:
                                *chan = 0x00;
                                break;
                            case FImage::Channel_CMYK_Black:
                                *chan = 0x00;
                                break;
                            case FImage::Channel_CMYK_Alpha:
                                *chan = 0xFF;
                                break;
                        }
                    }
                }
            }
        }
    } else
        image->reset();

    FGraphicsItem *item = new FGraphicsItem("Background", image);
    Scene->addItem(item);
    View->setSceneRect(0, 0, image->width(), image->height());
    View->show();
}

void MdiSubWindow::onWindowStateChanged(Qt::WindowStates oldState, Qt::WindowStates newState) {
    //qDebug() << this->windowTitle() << " MdiSubWindow::onWindowStateChanged(" << oldState << "," << newState << ")";
    if (oldState == Qt::WindowActive && newState == Qt::WindowNoState) { /* INACTIVE */
        //qDebug() << this->windowTitle() << "disconnect";
        disconnect(Tools, SIGNAL(triggered(QAction *)), this, SLOT(onToolsTriggered(QAction *)));
    } else if (oldState == Qt::WindowNoState && newState == Qt::WindowActive) { /* ACTIVE */
        //qDebug() << this->windowTitle() << "connect and update";
        connect(Tools, SIGNAL(triggered(QAction *)), this, SLOT(onToolsTriggered(QAction *)));
        emit Tools->triggered(Tools->checkedAction());
    } /*else {
        qDebug() << this->windowTitle() << oldState << newState;
    }*/
}

GraphicsView *MdiSubWindow::view() {
    return View;
}


