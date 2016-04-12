#ifndef IRESOURCEFINDER_H
#define IRESOURCEFINDER_H

class IResourceFinder
{
public:
    virtual ~IResourceFinder()
    {}

    virtual void addFilter(const QString &filter) = 0;
    virtual void addFilter(const QStringList& list) = 0;
    virtual void setFilter(const QString& filter) = 0;
    virtual void setFilter(const QStringList& list) = 0;
    virtual void clearFilters() = 0;

    virtual void find() = 0;

public:
    virtual quint32 resourcesCount() const = 0;
    virtual QStringList resourcesList() const = 0;
    virtual QString resourcesDir() const = 0;
};

#endif // IRESOURCEFINDER_H
