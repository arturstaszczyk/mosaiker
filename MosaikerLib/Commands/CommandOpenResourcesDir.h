#ifndef COMMANDOPENRESOURCESDIR_H
#define COMMANDOPENRESOURCESDIR_H

#include "Command.h"
#include "Interfaces/IFileChooser.h"

class CommandOpenResourcesDir : public Command
{
    Q_OBJECT

public:
    explicit CommandOpenResourcesDir(IPathChooser& fileChooser, QObject* parent = nullptr);

    virtual void execute() override;
private:
    IPathChooser& mFileChooser;
};

#endif // COMMANDOPENRESOURCESDIR_H
