#ifndef COMMANDCREATEMOSAIC_H
#define COMMANDCREATEMOSAIC_H

#include "Command.h"
class CommandCreateMosaic : public Command
{
public:
    explicit CommandCreateMosaic(QObject* parent = nullptr);

    virtual void execute();
};

#endif // COMMANDCREATEMOSAIC_H