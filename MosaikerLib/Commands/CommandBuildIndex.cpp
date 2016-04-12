#include "CommandBuildIndex.h"

#include <QDir>
#include <QFile>
#include <QDebug>

CommandBuildIndex::CommandBuildIndex(IResourceFinder& finder, QFile& indexFile, QObject* parent)
        : Command(parent)
        , mResourceFinder(finder)
        , mIndexFile(indexFile)
{
    mResourceFinder.addFilter({"*.jpg", "*.png", "*.jpeg"});
}

void CommandBuildIndex::execute()
{
    mResourceFinder.find();
    auto list = mResourceFinder.resourcesList();

    QString name;
    foreach(name, list) {
        qDebug() << name;
    }

    mIndexFile.open(QIODevice::WriteOnly);
    mIndexFile.close();
}
