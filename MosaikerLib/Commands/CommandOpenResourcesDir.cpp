#include "CommandOpenResourcesDir.h"

#include <QDir>

#include "Exceptions.h"

CommandOpenResourcesDir::CommandOpenResourcesDir(IFileChooser& fileChooser, QObject* parent)
    : Command(parent)
    , mFileChooser(fileChooser)
{

}

void CommandOpenResourcesDir::execute()
{
    QString dirName = mFileChooser.chooseFile();
    QDir dir(dirName);

    if(!dir.exists())
        throw PathDoNotExists();
}
