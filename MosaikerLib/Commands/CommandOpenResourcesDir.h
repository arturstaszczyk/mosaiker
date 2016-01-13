#ifndef COMMANDOPENRESOURCESDIR_H
#define COMMANDOPENRESOURCESDIR_H

#include "Command.h"
#include "Interfaces/IFileChooser.h"

class CommandOpenResourcesDir : public Command
{
    Q_OBJECT

public:
    explicit CommandOpenResourcesDir(IFileChooser& fileChooser, QObject* parent = nullptr);

    virtual void execute() override {}
private:
    IFileChooser& mFileChooser;
};

#endif // COMMANDOPENRESOURCESDIR_H
