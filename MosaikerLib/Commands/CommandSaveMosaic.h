#ifndef COMMANDSAVEMOSAIC_H
#define COMMANDSAVEMOSAIC_H

#include "Command.h"

#include "Interfaces/IFileChooser.h"
#include "Models/PictureModel.h"

class CommandSaveMosaic : public Command
{
public:
    explicit CommandSaveMosaic(IPathChooser* pathChooser, PictureModel* pictureModel, QObject* parent = nullptr);

    virtual void execute() override;

private:
    IPathChooser* mPathChooser;
    PictureModel* mPictureModel;
};

#endif // COMMANDSAVEMOSAIC_H
