#ifndef IMAGE_H
#define IMAGE_H
#include <QImage>

class Image : public QImage
{
public:
    typedef enum {
        Bitmap,
        Grayscale,
        RGB,
        CMYK
    } Mode;
    Image() {};
    Image(const QSize &size, Format format) : QImage(size, format) {}
    Image(int width, int height, Format format) : QImage(width, height, format) {}
    Image(uchar *data, int width, int height, Format format, QImageCleanupFunction cleanupFunction = Q_NULLPTR, void *cleanupInfo = Q_NULLPTR) : QImage(data, width, height, format, cleanupFunction, cleanupInfo) {}
    Image(const uchar *data, int width, int height, Format format, QImageCleanupFunction cleanupFunction = Q_NULLPTR, void *cleanupInfo = Q_NULLPTR) : QImage(data, width, height, format, cleanupFunction, cleanupInfo) {}
    Image(uchar *data, int width, int height, int bytesPerLine, Format format, QImageCleanupFunction cleanupFunction = Q_NULLPTR, void *cleanupInfo = Q_NULLPTR) : QImage(data, width, height, bytesPerLine, format, cleanupFunction, cleanupInfo) {}
    Image(const uchar *data, int width, int height, int bytesPerLine, Format format, QImageCleanupFunction cleanupFunction = Q_NULLPTR, void *cleanupInfo = Q_NULLPTR) : QImage(data, width, height, bytesPerLine, format, cleanupFunction, cleanupInfo) {}
    Image(const QString &fileName, const char *format = Q_NULLPTR) : QImage(fileName, format) {}
    Image(const QImage &image) : QImage(image) {}
    Image(QImage &&other) : QImage(other) {}
    int resolution();
    void setResolution(int r);
};

#endif // IMAGE_H
