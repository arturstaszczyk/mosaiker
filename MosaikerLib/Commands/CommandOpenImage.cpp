#include "CommandOpenImage.h"

CommandOpenImage::CommandOpenImage(ImageLibraryAdapter& imageLibrary, QFileDialog& fileDialog, QObject* parent)
    : Command(parent)
    , mImageLibrary(imageLibrary)
    , mFileDialog(fileDialog)
{

}

void CommandOpenImage::execute()
{
    QStringList filenames;
    if(mFileDialog.exec())
        filenames = mFileDialog.selectedFiles();

    mImageLibrary.loadImage(filenames[0]);

//    QImage loadedImage = mImageLibrary.toQImage();
//    emit imageOpened(loadedImage);
}
