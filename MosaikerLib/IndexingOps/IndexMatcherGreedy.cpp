#include "IndexMatcherGreedy.h"

#include <QDebug>

#include "Exceptions.h"

IndexMatcherGreedy::IndexMatcherGreedy(IIndexLoader* indexLoader, QObject* parent)
    : QObject(parent)
    , mIndexLoader(indexLoader)
{
    dynamic_cast<QObject*>(mIndexLoader)->setParent(this);
    mIndexLoader->loadIndex();
}

QString IndexMatcherGreedy::matchFileWithIndex(quint32 index)
{
    return mIndexLoader->closestFileNameByIndex(index);
}
