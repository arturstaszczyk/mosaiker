#ifndef IMAGEMANIPULATORINT_H
#define IMAGEMANIPULATORINT_H

#include "ImageLibraryAdapterInt.h"

class ImageManipulatorInt
{
public:
    virtual ~ImageManipulatorInt() {}

    virtual ImageManipulatorInt* imageManipulatorForSubimage(const QRect& imageRect) = 0;
    virtual void saveAsPng(QString fileName) = 0;
    virtual QImage* toQImage() const = 0;

    virtual void resize(const QSize& newSize) = 0;
    virtual QByteArray rawData() = 0;

    virtual quint32 imageName() const = 0;
    virtual qint32 width() const = 0;
    virtual qint32 height() const = 0;
    virtual const ImageLibraryAdapterInt& imageLibraryAdapter() const = 0;
};

#endif // IMAGEMANIPULATORINT_H
