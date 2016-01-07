#include "CommandOpenImage.h"

#include <QDebug>

#include "Exceptions.h"
#include "Interfaces/IImageManipulator.h"

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

    try
    {
        IImageManipulator* imageManipulator = mImageManipulatorBuilder.build();

        QImage loadedImage = imageManipulator->toQImage();
        emit imageOpened(loadedImage);
    }
    catch (CannotCreateImage ex)
    {
        qDebug() << "ImageManipulatorBuilder cannot create image.";
    }
}
