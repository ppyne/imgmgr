#ifndef ZOOMBOX_H
#define ZOOMBOX_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>

class ZoomBox : public QLineEdit
{
    Q_OBJECT
public:
    explicit ZoomBox(QWidget *parent = 0);
signals:
    void scaleEntryChanged(qreal scale);
public slots:
    void scaleChanged(qreal scale);
private:
    void focusOutEvent(QFocusEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void focusInEvent(QFocusEvent *event);
    qreal getNumber();
private slots:
};

#endif // ZOOMBOX_H
