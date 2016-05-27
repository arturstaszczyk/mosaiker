#include "IndexMatcherDistance.h"

IndexMatcherDistance::IndexMatcherDistance(IIndexLoader* indexLoader, quint32 distance, QObject* parent)
    : QObject(parent)
    , mIndexLoader(indexLoader)
    , mDistance(distance)
    , mExecutionCounter(0)
{
    dynamic_cast<QObject*>(mIndexLoader)->setParent(this);
    mIndexLoader->loadIndex();
}

bool IndexMatcherDistance::availableForUse(QString item)
{
    QMap<QString, qint32>::const_iterator foundItem = mUsageMap.find(item);
    return (foundItem == mUsageMap.end() || mExecutionCounter - foundItem.value() >= mDistance);
}

bool IndexMatcherDistance::invalidCandidate(QString item)
{
    return item == "";
}

QString IndexMatcherDistance::matchFileWithIndex(quint32 index)
{
    QString bestFit = mIndexLoader->closestFileNameByIndex(index);
    if(availableForUse(bestFit))
    {
        mUsageMap[bestFit] = mExecutionCounter;
        mExecutionCounter++;
        return bestFit;
    }
    else
    {
        bool canUseBestFit = false;
        QStringList excludes;
        excludes.append(bestFit);

        while(!canUseBestFit)
        {
            QString nextCandidate = mIndexLoader->closestFileNameByIndexExcluding(index, excludes);
            if(invalidCandidate(nextCandidate))
            {
                canUseBestFit = true;
            }
            else if(availableForUse(nextCandidate))
            {
                mUsageMap[nextCandidate] = mExecutionCounter;
                bestFit = nextCandidate;
                canUseBestFit = true;
            }
            else
            {
                excludes.append(nextCandidate);
            }
        }
    }

    mExecutionCounter++;
    return bestFit;
}
