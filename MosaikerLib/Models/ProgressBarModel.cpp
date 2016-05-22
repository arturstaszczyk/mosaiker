#include "ProgressBarModel.h"

ProgressBarModel::ProgressBarModel(QObject *parent)
    : QObject(parent)
    , mValue(0)
{

}

void ProgressBarModel::setValue(quint32 val)
{
    if(mValue != val)
    {
        mValue = val;
        emit valueChanged(mValue);
    }
}
