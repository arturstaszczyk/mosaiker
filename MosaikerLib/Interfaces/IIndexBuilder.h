#ifndef IINDEXBUILDER_H
#define IINDEXBUILDER_H

class IIndexBuilder
{
public:

    virtual void addIndexForFilename(quint32 index, QString filename) = 0;
    virtual void save() = 0;
};

#endif // IINDEXBUILDER_H
