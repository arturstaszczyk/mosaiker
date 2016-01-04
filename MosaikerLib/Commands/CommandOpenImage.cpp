#include "CommandOpenImage.h"

#include "Interfaces/ImageManipulatorInt.h"

CommandOpenImage::CommandOpenImage(ImageManipulatorBuilder& imageManipulatorBuilder,
                                   ImageLibraryAdapterInt& imageLibrary,
                                   QFileDialog& fileDialog, QObject* parent)
    : Command(parent)
    , mImageManipulatorBuilder(imageManipulatorBuilder)
    , mImageLibrary(imageLibrary)
    , mFileDialog(fileDialog)
{

}

void CommandOpenImage::execute()
{
    QStringList filenames;
    if(mFileDialog.exec())
    {
        filenames = mFileDialog.selectedFiles();

        mImageManipulatorBuilder.setFilename(filenames[0]);
        ImageManipulatorInt* imageManipulator = mImageManipulatorBuilder.build(mImageLibrary);

        QImage* loadedImage = imageManipulator->toQImage();
        emit imageOpened(loadedImage);
    }


}
