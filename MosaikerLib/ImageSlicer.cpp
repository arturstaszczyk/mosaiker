#include "ImageSlicer.h"

ImageSlicer::ImageSlicer(QObject *parent)
    : QObject(parent)
    , mSlices(0)
{

}

quint32 ImageSlicer::calculateRows(quint32 imageHeight, quint32 sliceHeight) const
{
    quint32 wholeSlices = imageHeight / sliceHeight;
    return wholeSlices + (wholeSlices * sliceHeight < imageHeight ? 1 : 0);
}

quint32 ImageSlicer::calculateColumns(quint32 imageWidth, quint32 sliceWidth) const
{
    quint32 wholeSlices = imageWidth / sliceWidth;
    return wholeSlices + (wholeSlices * sliceWidth < imageWidth ? 1 : 0);
}

QList<QImage> ImageSlicer::slice(QImage image, QSize sliceSize)
{
    QList<QImage> slicesList;

    int columnsCount = calculateColumns(image.width(), sliceSize.width());
    int rowsCount = calculateRows(image.height(), sliceSize.height());

    for(int y = 0; y < rowsCount; ++y)
    {
        for(int x = 0; x < columnsCount; ++x)
        {
            quint32 clampedWidth = std::min(image.width() - x, sliceSize.width());
            quint32 clampedHeight = std::min(image.height() - y, sliceSize.height());

            QImage slice = image.copy(x * sliceSize.width(), y * sliceSize.height(),
                                      clampedWidth, clampedHeight);
            slicesList.append(slice);
        }
    }

    mSlices = slicesList.count();
    return slicesList;
}
