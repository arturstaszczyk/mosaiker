#ifndef IMAGEMANIPULATORINT_H
#define IMAGEMANIPULATORINT_H

#include "IImageLibraryAdapter.h"

class IImageManipulator
{
public:
    virtual ~IImageManipulator() {}

    virtual IImageManipulator* imageManipulatorForSubimage(const QRect& imageRect) = 0;
    virtual void saveAsPng(QString fileName) = 0;
    virtual QImage toQImage() const = 0;

    virtual void resize(const QSize& newSize) = 0;
    virtual QByteArray rawData() = 0;

    virtual quint32 imageName() const = 0;
    virtual qint32 width() const = 0;
    virtual qint32 height() const = 0;
    virtual const IImageLibraryAdapter& imageLibraryAdapter() const = 0;
};

#endif // IMAGEMANIPULATORINT_H
