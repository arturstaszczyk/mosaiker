#ifndef COMMANDBUILDINDEX_H
#define COMMANDBUILDINDEX_H

#include "Command.h"
#include "Interfaces/IResourceFinder.h"

class CommandBuildIndex : public Command
{
    Q_OBJECT

public:
    CommandBuildIndex(IResourceFinder& finder, QObject* parent = nullptr);

    void execute() override {};

private:
    IResourceFinder& mResourceFinder;

};

#endif // COMMANDBUILDINDEX_H
