#ifndef IMAGEMATCHERLINEAR_H
#define IMAGEMATCHERLINEAR_H

#include <QMap>
#include <QObject>

#include "Interfaces/IIndexLoader.h"
#include "Interfaces/IIndexMatcherStrategy.h"

class IndexMatcherDistance : public QObject, public IIndexMatcherStrategy
{
public:
    IndexMatcherDistance(IIndexLoader* indexLoader, quint32 distance, QObject* parent = nullptr);

    virtual QString matchFileWithIndex(quint32 index) override;

private:
    IIndexLoader* mIndexLoader;
    QMap<QString, qint32> mUsageMap;

    qint32 mDistance;
    qint32 mExecutionCounter;
};

#endif // IMAGEMATCHERLINEAR_H
