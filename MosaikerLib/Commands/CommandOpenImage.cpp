#include "CommandOpenImage.h"

#include "Exceptions.h"

CommandOpenImage::CommandOpenImage(IPathChooser* fileDialog, QObject* parent)
    : Command(COMMAND_NAME(CommandOpenImage), parent)
    , mFileChooser(fileDialog)
{
    dynamic_cast<QObject*>(mFileChooser)->setParent(this);
}

void CommandOpenImage::execute()
{
    CommandFinisher finisher(this);

    QString fileName = mFileChooser->chooseFile();
    if(fileName.isEmpty())
        return;

    QImage loadedImage(fileName);
    if(loadedImage.isNull())
        throw CannotLoadImage();

    emit imageOpened(loadedImage);
}
