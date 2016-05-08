#ifndef COMMANDBUILDINDEX_H
#define COMMANDBUILDINDEX_H

#include <QFile>
#include <QColor>
#include <QByteArray>
#include <QThread>

#include "Command.h"
#include "Interfaces/IResourceFinder.h"

class CommandBuildIndex : public Command
{
    Q_OBJECT

public:
    CommandBuildIndex(IResourceFinder* finder, QFile& indexFile, QObject* parent = nullptr);

    void execute() override;

signals:
    void resourcesCount(quint32 resourcesCount);
    void updateProgress(quint32 updateProgress);

public slots:
    void onImageIndexed(QString imageName, quint32 color);

    void started();
    void finished();

private:
    IResourceFinder* mResourceFinder;
    QFile& mIndexFile;
    QByteArray mFileData;
};

#endif // COMMANDBUILDINDEX_H
