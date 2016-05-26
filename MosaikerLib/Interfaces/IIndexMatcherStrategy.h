#ifndef IINDEXMATCHERSTRATEGY_H
#define IINDEXMATCHERSTRATEGY_H

#include <QString>

class IIndexMatcherStrategy
{
public:
    virtual QString matchFileWithIndex(quint32 index) = 0;
};

#endif // IINDEXMATCHERSTRATEGY_H
