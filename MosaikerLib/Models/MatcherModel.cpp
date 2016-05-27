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

void MatcherModel::updateMatcher(MatcherType matcher)
{
    setMatcher(matcher);
}
