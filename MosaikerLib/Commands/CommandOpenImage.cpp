#include "CommandOpenImage.h"

#include "Interfaces/ImageManipulatorInt.h"

CommandOpenImage::CommandOpenImage(ImageManipulatorBuilder& imageManipulatorBuilder,
                                   IFileChooser& fileDialog, QObject* parent)
    : Command(parent)
    , mImageManipulatorBuilder(imageManipulatorBuilder)
    , mFileChooser(fileDialog)
{

}

void CommandOpenImage::execute()
{
    QString fileName = mFileChooser.chooseFile();
    mImageManipulatorBuilder.setFilename(fileName);
    ImageManipulatorInt* imageManipulator = mImageManipulatorBuilder.build();

    QImage loadedImage = imageManipulator->toQImage();
    emit imageOpened(loadedImage);
}
