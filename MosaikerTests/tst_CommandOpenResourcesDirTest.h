#ifndef TST_COMMANDOPENRESOURCESDIRTEST_H
#define TST_COMMANDOPENRESOURCESDIRTEST_H

#include <QObject>

class CommandOpenResourcesDirTest : public QObject
{
    Q_OBJECT
public:
    explicit CommandOpenResourcesDirTest(QObject *parent = 0);

private slots:
    void testInvalidDir();
};

#endif // TST_COMMANDOPENRESOURCESDIRTEST_H
