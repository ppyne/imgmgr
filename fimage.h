#ifndef FIMAGE_H
#define FIMAGE_H

#include <QString>
#include "fcolor.h"

class FImage {
    public:
        enum ImageMode {
            Bitmap = 0,
            Grayscale,
            Indexed,
            RGB,
            CMYK
        };
        static const int Channel_RGB_Red = 0;
        static const int Channel_CMYK_Cyan = 0;
        static const int Channel_GS_Gray = 0;
        static const int Channel_BM_Black = 0;
        static const int Channel_RGB_Green = 1;
        static const int Channel_CMYK_Magenta = 1;
        static const int Channel_GS_Alpha = 1;
        static const int Channel_BM_Alpha = 1;
        static const int Channel_RGB_Blue = 2;
        static const int Channel_CMYK_Yellow = 2;
        static const int Channel_RGB_Alpha = 3;
        static const int Channel_CMYK_Black = 3;
        static const int Channel_CMYK_Alpha = 4;
        FImage(int width, int height, int resolution, ImageMode mode, QString profile);
        ~FImage();
        int channels();
        int width();
        int height();
        QString profile();
        ImageMode mode();
        int size();
        int resolution();
        unsigned char *scanRow(int row);
        unsigned char *scanCol(unsigned char *data, int col);
        unsigned char *scanChan(unsigned char *data, int chan);
        FColor rgb(unsigned char *data, int col);
        void reset();
    private:
        int Channels;
        int Width;
        int Height;
        int Resolution;
        QString Profile;
        ImageMode Mode;
        unsigned char *Data;
        int Size;
};

#endif // FIMAGE_H
