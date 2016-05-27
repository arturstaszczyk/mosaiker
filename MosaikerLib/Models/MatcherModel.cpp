#include "MatcherModel.h"

MatcherModel::MatcherModel(QObject *parent)
    : QObject(parent)
{

}

void MatcherModel::setMatcher(MatcherType matcher)
{
    if(mMatcher != matcher)
    {
        mMatcher = matcher;
        emit matcherChanged(mMatcher);
    }
}

void MatcherModel::setDistance(quint32 distance)
{
    if(mDistance != distance)
    {
        mDistance = distance;
        emit distanceChanged(mDistance);
    }
}
