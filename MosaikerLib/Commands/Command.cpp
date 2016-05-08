#include "Command.h"

Command::Command(QString name, QObject *parent)
    : QObject(parent)
    , mFinished(false)
    , mName(name)
{

}
