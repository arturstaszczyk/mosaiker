#ifndef MOCKBASE
#define MOCKBASE

#include <QStringList>
#include <QVariantList>

#define CALL calls.append(__FUNCTION__)
#define ARG(x) callsArgs.append(QVariant(x))

class MockBase
{
public:
    QStringList calls;
    QVariantList callsArgs;
};

#endif // MOCKBASE

