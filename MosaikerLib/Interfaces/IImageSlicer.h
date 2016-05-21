#ifndef IIMAGESLICER_H
#define IIMAGESLICER_H

#include <QList>
#include <QImage>

class IImageSlicer
{
public:

    virtual QList<QImage> slice(QImage image, QSize sliceSize) = 0;
};

#endif // IIMAGESLICER_H
