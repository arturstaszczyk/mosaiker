#ifndef IMAGESLICER_H
#define IMAGESLICER_H

#include <QObject>

#include "Interfaces/IImageSlicer.h"

class ImageSlicer : public QObject, public IImageSlicer
{
    Q_OBJECT
public:
    explicit ImageSlicer(QObject *parent = 0);

    virtual QList<QImage> slice(QImage image, QSize sliceSize) override;

    virtual quint32 slices() const override { return mSlices; }

    quint32 calculateRows(quint32 imageHeight, quint32 sliceHeight) const;
    quint32 calculateColumns(quint32 imageWidth, quint32 sliceWidth) const;

private:
    quint32 mSlices;
};

#endif // IMAGESLICER_H
