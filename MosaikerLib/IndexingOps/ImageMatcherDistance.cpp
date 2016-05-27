#include "ImageMatcherDistance.h"

ImageMatcherDistance::ImageMatcherDistance(IIndexLoader* indexLoader, quint32 distance, QObject* parent)
    : QObject(parent)
    , mIndexLoader(indexLoader)
    , mDistance(distance)
    , mExecutionCounter(0)
{
    dynamic_cast<QObject*>(mIndexLoader)->setParent(this);
    mIndexLoader->loadIndex();
}

QString ImageMatcherDistance::matchFileWithIndex(quint32 index)
{
    QString bestFit = mIndexLoader->closestFileNameByIndex(index);
    if(mUsageMap.find(bestFit) == mUsageMap.end())
    {
        mUsageMap.insert(bestFit, mExecutionCounter);
        mExecutionCounter++;
        return bestFit;
    }
    else
    {
        bool canUse = false;
        QStringList excludes;

        while(!canUse)
        {
            QString nextCandidate = mIndexLoader->closestFileNameByIndexExcluding(index, excludes);
            if(nextCandidate == "")
            {
                mExecutionCounter++;
                return bestFit;
            }

            QMap<QString, qint32>::const_iterator foundItem = mUsageMap.find(nextCandidate);
            if(foundItem == mUsageMap.end() || mExecutionCounter - foundItem.value() >= mDistance)
            {
                mUsageMap[nextCandidate] = mExecutionCounter;
                mExecutionCounter++;
                return nextCandidate;
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
