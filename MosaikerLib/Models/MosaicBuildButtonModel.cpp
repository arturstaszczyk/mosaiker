#include "MosaicBuildButtonModel.h"

MosaicBuildButtonModel::MosaicBuildButtonModel(QObject *parent)
    : QObject(parent)
    , mIsBeingCreated(false)
    , mWasCreated(false)
{

}

void MosaicBuildButtonModel::setIsBeingCreated(bool isBeingCreated)
{
    if(mIsBeingCreated != isBeingCreated)
    {
        mIsBeingCreated = isBeingCreated;
        emit isBeingCreatedChanged(mIsBeingCreated);
    }
}

void MosaicBuildButtonModel::setWasCreated(bool wasCreated)
{
    if(mWasCreated != wasCreated)
    {
        mWasCreated = wasCreated;
        emit wasCreatedChanged(mWasCreated);
    }
}

