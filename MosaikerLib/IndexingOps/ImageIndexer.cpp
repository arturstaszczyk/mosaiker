#include "ImageIndexer.h"

#include "Exceptions.h"

ImageIndexer::ImageIndexer(QStringList imageList, QObject *parent)
    : QThread(parent)
    , mImageNamesList(imageList)
{

}

ImageIndexer::ImageIndexer(QList<QImage> imageList, QObject *parent)
    : QThread(parent)
    , mImagesList(imageList)
{

}

void ImageIndexer::run()
{
    if(!mImageNamesList.empty())
        runWithImageNames();
    else if(!mImagesList.empty())
        runWithImageList();
    else
        throw CannotIndexFiles();
}

void ImageIndexer::runWithImageNames()
{
    for (int i = 0; i < mImageNamesList.count(); ++i)
    {
        QString imageName = mImageNamesList[i];
        QImage image(imageName);

        QRgb imageIndex = calculateImageIndex(image);
        emit imageIndexed(i, imageName, imageIndex);
    }
}

void ImageIndexer::runWithImageList()
{
    for (int i = 0; i < mImagesList.count(); ++i)
    {
        QRgb imageIndex = calculateImageIndex(mImagesList[i]);
        emit imageIndexed(i, "", imageIndex);
    }
}

QRgb ImageIndexer::calculateImageIndex(QImage image)
{
    quint32 r = 0, g = 0, b = 0;

    for(int x = 0; x < image.width(); ++x)
    {
        for(int y = 0; y < image.height(); ++y)
        {
            QRgb rgb = image.pixel(x, y);
            r += qRed(rgb);
            g += qGreen(rgb);
            b += qBlue(rgb);
        }
    }

    auto pixelCount = image.width() * image.height();
    r /= pixelCount;
    g /= pixelCount;
    b /= pixelCount;

    return qRgb(r, g, b);
}
