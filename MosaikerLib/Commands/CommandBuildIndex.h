#ifndef COMMANDBUILDINDEX_H
#define COMMANDBUILDINDEX_H

#include <QFile>
#include <QColor>
#include <QByteArray>
#include <QThread>

#include "Command.h"
#include "Interfaces/IResourceFinder.h"
#include "Models/ResourcesDirModel.h"

class CommandBuildIndex : public Command
{
    Q_OBJECT

public:
    CommandBuildIndex(IResourceFinder* finder,
                      QString& indexFileName, ResourcesDirModel* resourcesDirModel, QObject* parent = nullptr);

    void execute() override;

signals:
    void resourcesCount(quint32 resourcesCount);
    void updateProgress(quint32 updateProgress);

public slots:
    void onImageIndexed(QString imageName, quint32 color);

    void finished();

private:
    IResourceFinder* mResourceFinder;
    ResourcesDirModel* mResourcesDirModel;
    QString mIndexFileName;
    QByteArray mFileData;
};

#endif // COMMANDBUILDINDEX_H
