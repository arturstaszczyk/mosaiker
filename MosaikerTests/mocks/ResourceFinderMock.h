#ifndef RESOURCEFINDERMOCK_H
#define RESOURCEFINDERMOCK_H

#include <QtMock.h>

#include "Interfaces/IResourceFinder.h"

class ResourceFinderMock : public QtMockExt::QtMock, public IResourceFinder
{
public:
    explicit ResourceFinderMock(QString directory)
    {
        Q_UNUSED(directory);
    }

    void addFilter(const QString& filter) override { MOCK_CALL; MOCK_ARG(filter); }
    void addFilter(const QStringList& list) override { MOCK_CALL; MOCK_ARG(list); }
    void setFilter(const QString& filter) override { MOCK_CALL; MOCK_ARG(filter); }
    void setFilter(const QStringList& list) override { MOCK_CALL; MOCK_ARG(list); }

    void find() override { MOCK_CALL; }

    void clearFilters() override { MOCK_CALL; }
    quint32 resourcesCount() const override { return 0; }
    QStringList resourcesList() const override { return QStringList(); }
};

#endif // RESOURCEFINDERMOCK_H
