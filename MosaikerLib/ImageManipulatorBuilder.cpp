#include "ImageManipulatorBuilder.h"

#include "ImageManipulator.h"

ImageManipulatorBuilder::ImageManipulatorBuilder(QObject *parent) : QObject(parent)
{

}

ImageManipulatorInt* ImageManipulatorBuilder::build(ImageLibraryAdapterInt& imageLibrary)
{
    if(mFilename.size() > 0)
        return new ImageManipulator(mFilename, imageLibrary);

    return nullptr;
}
