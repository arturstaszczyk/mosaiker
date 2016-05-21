﻿#include "ProgressBarModel.h"

ProgressBarModel::ProgressBarModel(QObject *parent)
    : QObject(parent)
    , mMaxValue(1)
    , mValue(0)
{

}

void ProgressBarModel::setMaxValue(quint32 maxVal)
{
    if(maxVal != mMaxValue)
    {
        mMaxValue = maxVal;
        emit maxValueChanged(mMaxValue);
    }
}

void ProgressBarModel::setValue(quint32 val)
{
    if(mValue != val)
    {
        mValue = val;
        emit valueChanged(mValue);
    }
}
