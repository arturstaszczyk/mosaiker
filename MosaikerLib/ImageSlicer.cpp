﻿#include "ImageSlicer.h"

ImageSlicer::ImageSlicer(QObject *parent)
    : QObject(parent)
{

}

QList<QImage> ImageSlicer::slice(QImage image, QSize sliceSize)
{
    QList<QImage> slicesList;

    int countHorizontal = image.width() / sliceSize.width();
    int countVertical = image.height() / sliceSize.height();

    for(int x = 0; x < countHorizontal; ++x)
    {
        for(int y = 0; y < countVertical; ++y)
        {
            QImage slice = image.copy(x, y, sliceSize.width(), sliceSize.height());
            slicesList.append(slice);
        }
    }

    return slicesList;
}
