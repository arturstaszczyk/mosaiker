#include "ImageManipulatorBuilder.h"

#include <QDebug>

#include "Exceptions.h"
#include "ImageManipulator.h"

bool has2Dimentions(const QSize& size)
{
    return size.width() > 0 && size.height() > 0;
}

ImageManipulatorBuilder::ImageManipulatorBuilder(IImageLibraryAdapter& imageLibrary,
                                                 QObject *parent)
    : QObject(parent)
    , mImageLibrary(imageLibrary)
{

}

IImageManipulator* ImageManipulatorBuilder::build()
{
    ImageManipulator* constructedImage = nullptr;
    try
    {
        if(mFilename.size() > 0)
            constructedImage = new ImageManipulator(mFilename, mImageLibrary);
        else if(has2Dimentions(mSize) && mBytes.size() > 0)
            constructedImage = new ImageManipulator(mSize, mBytes, mImageLibrary);
        else if(has2Dimentions(mSize))
            constructedImage = new ImageManipulator(mSize, mImageLibrary);
    }
    catch(CannotLoadImage ex)
    {
        qDebug() << "Cannot load file [" << mFilename << "] - unsupported format";
    }
    catch(ResourceDoNotExists ex)
    {
        qDebug() << "File [" << mFilename << "] do not exists";
    }

    if(constructedImage == nullptr)
        throw CannotCreateImage();

    return constructedImage;
}
