#ifndef COMMANDBUILDINDEX_H
#define COMMANDBUILDINDEX_H

#include <QFile>
#include <QColor>
#include <QByteArray>
#include <QThread>

#include "Command.h"
#include "Interfaces/IResourceFinder.h"
#include "Interfaces/IIndexBuilder.h"

class CommandBuildIndex : public Command
{
    Q_OBJECT

public:
    CommandBuildIndex(IResourceFinder* resourcesFinder, IIndexBuilder* indexBuilder,
                      QObject* parent = nullptr);

    void execute() override;

public slots:
    void onImageIndexed(quint32 imageNo, QString imageName, quint32 color);

    void finished();

private:
    IResourceFinder* mResourceFinder;
    IIndexBuilder* mIndexBuilder;
};

#endif // COMMANDBUILDINDEX_H
