#ifndef IMAGEMATCHERGREEDY_H
#define IMAGEMATCHERGREEDY_H

#include "Interfaces/IIndexMatcherStrategy.h"

#include <QObject>

#include "Interfaces/IIndexLoader.h"

class IndexMatcherGreedy : public QObject, public IIndexMatcherStrategy
{
    Q_OBJECT

public:
    explicit IndexMatcherGreedy(IIndexLoader* indexLoader, QObject* parent = nullptr);

    virtual QString matchFileWithIndex(quint32 index) override;

private:
    IIndexLoader* mIndexLoader;
};

#endif // IMAGEMATCHERGREEDY_H
