#include "ImageManipulatorBuilder.h"

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
    if(mFilename.size() > 0)
        return new ImageManipulator(mFilename, mImageLibrary);

    if(has2Dimentions(mSize) && mBytes.size() > 0)
        return new ImageManipulator(mSize, mBytes, mImageLibrary);
    else if(has2Dimentions(mSize))
        return new ImageManipulator(mSize, mImageLibrary);

    throw CannotCreateImage();
}
