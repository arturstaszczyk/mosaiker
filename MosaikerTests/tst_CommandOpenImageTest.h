#ifndef TST_COMMANDOPENIMAGETEST_H
#define TST_COMMANDOPENIMAGETEST_H

#include <QtTest>

class CommandOpenImageTest : public QObject
{
    Q_OBJECT

public:
    CommandOpenImageTest()
    {}

private slots:
    void testOpenImageSignal();
};

#endif // TST_COMMANDOPENIMAGETEST_H
