#include "CommandOpenResourcesDir.h"

#include <QDir>

#include "Exceptions.h"

CommandOpenResourcesDir::CommandOpenResourcesDir(IPathChooser& fileChooser, QObject* parent)
    : Command(parent)
    , mFileChooser(fileChooser)
{

}

void CommandOpenResourcesDir::execute()
{
    QString dirName = mFileChooser.chooseDir();
    if(dirName.isEmpty())
        return;

    QDir dir(dirName);

    if(!dir.exists())
        throw PathDoNotExists();

    emit dirOpened(dir.absolutePath());
}
