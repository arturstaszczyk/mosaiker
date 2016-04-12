#ifndef COMMANDBUILDINDEX_H
#define COMMANDBUILDINDEX_H

#include <QFile>
#include <QColor>
#include <QByteArray>

#include "Command.h"
#include "Interfaces/IResourceFinder.h"

class CommandBuildIndex : public Command
{
    Q_OBJECT

public:
    CommandBuildIndex(IResourceFinder& finder, QFile& indexFile, QObject* parent = nullptr);

    void execute() override;

public slots:
    void onImageIndexed(QString imageName, QRgb color);

private:
    IResourceFinder& mResourceFinder;
    QFile& mIndexFile;
    QByteArray mFileData;

};

#endif // COMMANDBUILDINDEX_H
