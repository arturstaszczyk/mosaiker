#include "ImageMatcherGreedy.h"

#include <QDebug>

#include "Exceptions.h"

ImageMatcherGreedy::ImageMatcherGreedy(IIndexLoader* indexLoader, QObject* parent)
    : QObject(parent)
    , mIndexLoader(indexLoader)
{
    dynamic_cast<QObject*>(mIndexLoader)->setParent(this);

    mIndexLoader->loadIndex();
}

QString ImageMatcherGreedy::matchFileWithIndex(quint32 index)
{
    return mIndexLoader->closestFileNameByIndex(index);
}
