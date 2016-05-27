#include "SliceSizeModel.h"

SliceSizeModel::SliceSizeModel(QObject *parent) : QObject(parent)
{

}

void SliceSizeModel::setSliceSize(quint32 size)
{
    if(mSliceSize != size)
    {
        mSliceSize = size;
        emit sliceSizeChanged(mSliceSize);
    }
}
