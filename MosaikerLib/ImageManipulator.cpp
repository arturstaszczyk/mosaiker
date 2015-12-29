#include "ImageManipulator.h"

#include <QFile>

#include "Exceptions.h"

const int ImageManipulator::IMAGE_CHANNELS_3 = 3;

ImageManipulator::ImageManipulator(quint32 width, quint32 height,
                                   ImageLibraryAdapter* imageLibrary,
                                   QObject *parent)
    : QObject(parent)
    , mImageLibraryObj(imageLibrary)
    , mImageName(0)
    , mWidth(width)
    , mHeight(height)
{
    mImageName = mImageLibraryObj->genImage();
    mImageLibraryObj->bindImage(mImageName);

    QByteArray imageBytes(mWidth * mHeight * IMAGE_CHANNELS_3, '\0');
    mImageLibraryObj->texImage24RGB(mWidth, mHeight, imageBytes.data());
}

ImageManipulator::ImageManipulator(QString fileName,
                                   ImageLibraryAdapter* imageLibrary,
                                   QObject* parent)
    : QObject(parent)
    , mImageLibraryObj(imageLibrary)
    , mImageName(0)
    , mWidth(0)
    , mHeight(0)
{
    mImageName = mImageLibraryObj->genImage();
    mImageLibraryObj->bindImage(mImageName);

    QFile imageFile(fileName);
    if(!imageFile.exists())
        throw ImageDoNotExists();

    bool loaded = mImageLibraryObj->loadImage(fileName);
    if(!loaded)
        throw CannotLoadImage();

    mWidth = mImageLibraryObj->getWidth();
    mHeight = mImageLibraryObj->getHeight();
}

void ImageManipulator::resize(quint32 width, quint32 height)
{
    mImageLibraryObj->bindImage(0);
    mImageLibraryObj->scale(width, height);

    mWidth = width;
    mHeight = height;
}

