#ifndef COMMANDBUILDINDEX_H
#define COMMANDBUILDINDEX_H

#include <QFile>

#include "Command.h"
#include "Interfaces/IResourceFinder.h"

class CommandBuildIndex : public Command
{
    Q_OBJECT

public:
    CommandBuildIndex(IResourceFinder& finder, QFile& indexFile, QObject* parent = nullptr);

    void execute() override;

private:
    IResourceFinder& mResourceFinder;
    QFile& mIndexFile;

};

#endif // COMMANDBUILDINDEX_H
