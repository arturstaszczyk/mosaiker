#include "MosaicBuildButtonModel.h"

MosaicBuildButtonModel::MosaicBuildButtonModel(QObject *parent)
    : QObject(parent)
    , mIsBeingCreated(false)
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
