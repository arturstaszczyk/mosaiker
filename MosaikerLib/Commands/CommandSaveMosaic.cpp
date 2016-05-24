#include "CommandSaveMosaic.h"

CommandSaveMosaic::CommandSaveMosaic(IPathChooser* pathChooser, PictureModel* pictureModel, QObject* parent)
    : Command(COMMAND_NAME(CommandSaveMosaic), parent)
    , mPathChooser(pathChooser)
    , mPictureModel(pictureModel)
{
    dynamic_cast<QObject*>(pathChooser)->setParent(this);
}

void CommandSaveMosaic::execute()
{
    CommandFinisher finisher(this);

    QString fileName = mPathChooser->chooseFile(IPathChooser::OT_WRITE);
    mPictureModel->composedImage().save(fileName, "PNG", 100);
}
