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
};

#endif // IMAGESLICER_H
