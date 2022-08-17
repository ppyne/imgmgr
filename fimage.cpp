#include "fimage.h"

FImage::FImage(int width, int height, int resolution, FImage::ImageMode mode, QString profile) {
    Width = width;
    Height = height;
    Resolution = resolution;
    Mode = mode;
    Channels = 0;
    Profile = profile;
    switch(Mode) {
        case FImage::Bitmap:
            Channels = 2;
            break;
        case FImage::Grayscale:
            Channels = 2;
            break;
        case FImage::Indexed:
            Channels = 0;
            break;
        case FImage::RGB:
            Channels = 4;
            break;
        case FImage::CMYK:
            Channels = 5;
            break;
    }
    Size = Channels * Width * Height;
    if (Size > 0) Data = new unsigned char[Size];
}

void FImage::reset() {
    for (int i = 0; i < Size; i++) Data[i] = 0;
}

FImage::~FImage() {
    if (Size > 0) delete []Data;
}

int FImage::channels() {
    return Channels;
}

int FImage::width() {
    return Width;
}

int FImage::height() {
    return Height;
}

QString FImage::profile() {
    return Profile;
}

FImage::ImageMode FImage::mode() {
    return Mode;
}

int FImage::size() {
    return Size;
}

int FImage::resolution() {
    return Resolution;
}

unsigned char *FImage::scanRow(int row) {
    if (row < 0) row = 0;
    if (row >= Height) row = Height - 1;
    return Data + (row * Width * Channels);
}
unsigned char *FImage::scanCol(unsigned char *data, int col) {
    if (col < 0) col = 0;
    if (col >= Width) col = Width - 1;
    return data + (col * Channels);
}
unsigned char *FImage::scanChan(unsigned char *data, int chan) {
    if (chan < 0) chan = 0;
    if (chan >= Channels) chan = Channels - 1;
    return data + chan;
}

FColor FImage::rgb(unsigned char *data, int col) {
    if (col < 0) col = 0;
    if (col >= Width) col = Width - 1;
    unsigned char *c1 = data + (col * Channels);
    unsigned char *c2;
    unsigned char *c3;
    unsigned char *c4;
    unsigned char *c5;
    if (Mode == FImage::Bitmap) {
        c2 = c1 + FImage::Channel_BM_Alpha;
        return FColor(*c1, *c1, *c1, *c2);
    } else if (Mode == FImage::Grayscale) {
        c2 = c1 + FImage::Channel_GS_Alpha;
        return FColor(*c1, *c1, *c1, *c2);
    } else if (Mode == FImage::RGB) {
        c2 = c1 + FImage::Channel_RGB_Green;
        c3 = c1 + FImage::Channel_RGB_Blue;
        c4 = c1 + FImage::Channel_RGB_Alpha;
        return FColor(*c1, *c2, *c3, *c4);
    } else if (Mode == FImage::CMYK) {
        c2 = c1 + FImage::Channel_CMYK_Magenta;
        c3 = c1 + FImage::Channel_CMYK_Yellow;
        c4 = c1 + FImage::Channel_CMYK_Black;
        c5 = c1 + FImage::Channel_CMYK_Alpha;
        return FColor::fromCmyk(*c1, *c2, *c3, *c4, *c5);
    }
    return QColor();
}
