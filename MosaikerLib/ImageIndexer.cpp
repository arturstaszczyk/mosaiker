#include "ImageIndexer.h"

ImageIndexer::ImageIndexer(QStringList imageList, QObject *parent)
    : QObject(parent)
    , mImageList(imageList)
{

}

void ImageIndexer::execute()
{
    QString imageName;
    foreach(imageName, mImageList)
        emit imageIndexed(imageName, QColor(1, 1, 1));
}
