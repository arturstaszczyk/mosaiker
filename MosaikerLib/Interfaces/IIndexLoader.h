#ifndef IINDEXLOADER_H
#define IINDEXLOADER_H

class IIndexLoader
{
public:
    virtual void loadIndex() = 0;
    virtual QString closestFileNameByIndex(quint32 index) = 0;
    virtual QString closestFileNameByIndexExcluding(quint32 index, QStringList excludes) = 0;
};

#endif // IINDEXLOADER_H
