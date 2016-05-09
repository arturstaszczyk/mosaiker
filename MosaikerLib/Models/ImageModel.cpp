﻿#include "ImageModel.h"

#include <QDebug>

#include "Exceptions.h"

ImageModel::ImageModel(QObject *parent)
    : QObject(parent)
    , QQuickImageProvider(QQmlImageProviderBase::Image, 0)
{

}

void ImageModel::setOriginalImage(const QImage &image)
{
    mOriginalImage = image;
    emit imageUpdated();
}

QImage ImageModel::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id);

    if(mOriginalImage.isNull())
        return mOriginalImage;

    if(size)
    {
        *size = QSize(mOriginalImage.width(), mOriginalImage.height());
        if(!requestedSize.isEmpty())
        {
            mDesiredSize = mOriginalImage.size().scaled(requestedSize.width(), requestedSize.height(),
                                                             Qt::KeepAspectRatio);
        }
    }

    emit sizeChanged();
    return mOriginalImage;
}
