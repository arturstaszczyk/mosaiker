#include "SliceSizeModel.h"

SliceSizeModel::SliceSizeModel(QObject *parent) : QObject(parent)
{

}

void SliceSizeModel::setSliceSize(QSize size)
{
    if(mSliceSize != size)
    {
        mSliceSize = size;
        emit sliceSizeChanged(mSliceSize);
    }
}

void SliceSizeModel::updateSliceSize(QSize sliceSize)
{
    setSliceSize(sliceSize);
}
