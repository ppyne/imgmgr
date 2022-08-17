#include "image.h"
#include <QDebug>

int Image::resolution() {
    return (dotsPerMeterX()*254)/10000;
}

void Image::setResolution(int r) {
    setDotsPerMeterX(qRound(((qreal)r*10000.0)/254.0));
    setDotsPerMeterY(dotsPerMeterX());
}
