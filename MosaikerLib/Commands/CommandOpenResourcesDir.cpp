#include "CommandOpenResourcesDir.h"

#include <QDir>

#include "Exceptions.h"

CommandOpenResourcesDir::CommandOpenResourcesDir(IPathChooser* fileChooser, QObject* parent)
    : Command(COMMAND_NAME(CommandOpenResourcesDir), parent)
    , mFileChooser(fileChooser)
{
    dynamic_cast<QObject*>(mFileChooser)->setParent(this);
}

void CommandOpenResourcesDir::execute()
{
    CommandFinisher finisher(this);

    QString dirName = mFileChooser->chooseDir();
    if(dirName.isEmpty())
        return;

    QDir dir(dirName);

    if(!dir.exists())
        throw PathDoNotExists();

    emit dirOpened(dir.absolutePath());
}
