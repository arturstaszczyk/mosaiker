#ifndef COMMANDBUILDINDEXTEST_H
#define COMMANDBUILDINDEXTEST_H

#include <QObject>

class CommandBuildIndexTest : public QObject
{
    Q_OBJECT
public:
    explicit CommandBuildIndexTest(QObject *parent = 0);

private slots:
    void testBuildIndex();
};

#endif // COMMANDBUILDINDEXTEST_H
