#include "ImageManipulator.h"

ImageManipulator::ImageManipulator(quint32 width, quint32 height,
                                   ImageLibraryAdapter* imageLibrary,
                                   QObject *parent)
    : QObject(parent)
    , mImageLibraryObj(imageLibrary)
    , mWidth(width)
    , mHeight(height)
    , mImageName(0)
{
    mImageName = mImageLibraryObj->genImage();
}

void ImageManipulator::resize(quint32 width, quint32 height)
{
    mImageLibraryObj->bindImage(0);
    mWidth = width;
    mHeight = height;
}

