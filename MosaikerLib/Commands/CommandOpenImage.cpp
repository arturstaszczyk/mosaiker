#include "CommandOpenImage.h"

#include <QDebug>

#include "Exceptions.h"

CommandOpenImage::CommandOpenImage(IFileChooser& fileDialog, QObject* parent)
    : Command(parent)
    , mFileChooser(fileDialog)
{

}

void CommandOpenImage::execute()
{
    QString fileName = mFileChooser.chooseFile();
    QImage loadedImage(fileName);
    if(loadedImage.isNull())
        throw CannotLoadImage();

    emit imageOpened(loadedImage);
}
