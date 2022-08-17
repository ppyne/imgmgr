#ifndef COLOR_H
#define COLOR_H
#include <QColor>
//#include <QStringView>

class FColor : public QColor {
public:
    FColor();
    FColor(Qt::GlobalColor color) : QColor(color) {}
    FColor(int r, int g, int b, int a = 255) : QColor(r, g, b, a) {}
    FColor(QRgb color) : QColor(color) {}
    FColor(QRgba64 rgba64) : QColor(rgba64) {}
    FColor(const QString &name) : QColor(name) {}
    //FColor(QStringView name) : QColor(name) {}
    FColor(const char *name) : QColor(name) {}
    FColor(QLatin1String name) : QColor(name) {}
    FColor(const QColor &color) : QColor(color) {}
    FColor(QColor &&other) : QColor(other) {}
};
#endif // COLOR_H
