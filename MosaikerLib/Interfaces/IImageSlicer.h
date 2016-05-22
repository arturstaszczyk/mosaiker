#ifndef IIMAGESLICER_H
#define IIMAGESLICER_H

#include <QList>
#include <QImage>

class IImageSlicer
{
public:

    // Slice should return slices of image in "row-first" order,
    // meanig it should process image row by row
    virtual QList<QImage> slice(QImage image, QSize sliceSize) = 0;
    virtual quint32 slices() const = 0;
};

#endif // IIMAGESLICER_H
