#ifndef MDISUBWINDOW_H
#define MDISUBWINDOW_H
#include <QWidget>
#include <QMdiSubWindow>
#include <QString>
#include "graphicsscene.h"
#include "graphicsview.h"
#include "image.h"
#include <QCloseEvent>
#include <QActionGroup>
#include <QImage>
#include <QImageReader>
#include "fcolor.h"
#include "fimage.h"

class MdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    typedef enum {
        Transparent,
        Color
    } Background;
    MdiSubWindow(QActionGroup *tools, QWidget *parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());
    void loadImage(const QString &path, const QImage &image);
    void newImage(const QString &name, int width, int height, int resolution, FImage::ImageMode mode, Background bg, FColor bgcolor, QString profile);
    GraphicsView *view();
signals:
    void toolChanged(GraphicsView::ToolType type);
private slots:
    void onToolsTriggered(QAction *action);
    void onWindowStateChanged(Qt::WindowStates oldState, Qt::WindowStates newState);
private:
    QString Path;
    Image _Image;
    GraphicsView *View;
    GraphicsScene *Scene;
    QActionGroup *Tools;
};

#endif // MDISUBWINDOW_H
