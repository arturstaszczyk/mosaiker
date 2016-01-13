#include "CommandOpenResourcesDir.h"

CommandOpenResourcesDir::CommandOpenResourcesDir(IFileChooser& fileChooser, QObject* parent)
    : Command(parent)
    , mFileChooser(fileChooser)
{

}
