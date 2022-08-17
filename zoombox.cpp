#include "zoombox.h"
#include <QLineEdit>
#include <QDebug>
#include <QString>
#include <QRegularExpression>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <QStringList>
#include <QtMath>

ZoomBox::ZoomBox(QWidget *parent) : QLineEdit(parent) {
    setMinimumHeight(16);
    QFont f = font();
    f.setPointSize(10);
    setFont(f);
    setMaximumWidth(60);
    setAlignment(Qt::AlignRight);
    setFocusPolicy(Qt::StrongFocus);
}

void ZoomBox::scaleChanged(qreal scale) {
    //qDebug() << "ZoomBox::scaleChanged(" << scale << ")";
    scale *= 100.0;
    QString value = QString::number(scale, 'f', 1);
    if (value.endsWith(".0")) {
        value = value.left(value.length()-2);
    }
    setText(value+"%");
    //static_cast<QWidget *>(parent())->setFocus();
}

void ZoomBox::focusOutEvent(QFocusEvent *event) {
    Q_UNUSED(event);
    qreal s = getNumber();
    scaleChanged(s);
    emit scaleEntryChanged(s);
}

void ZoomBox::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        qreal s = getNumber();
        scaleChanged(s);
        emit scaleEntryChanged(s);
    }
}

void ZoomBox::focusInEvent(QFocusEvent *event) {
    Q_UNUSED(event);
    QTimer::singleShot(0, this, SLOT(selectAll()));
}

qreal ZoomBox::getNumber() {
    QRegularExpression re("(-?\\d+(?:[\\.,]\\d+(?:e\\d+)?)?)");
    QRegularExpressionMatch m = re.match(text());
    QStringList l = m.capturedTexts();
    if (l.empty()) return 0.0;
    QString value = l.at(0);
    return qFabs(value.toDouble()/100.0);
}
