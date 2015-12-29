#ifndef MOCKBASE
#define MOCKBASE

#include <QStringList>
#include <QVariantList>

#define CALL calls.append(__FUNCTION__)
#define ARG(x) callsArgs.append(QVariant(x))

class MockBase
{
public:

    bool hasExactlyOneCall(QString call)
    {
        return calls.filter(call, Qt::CaseSensitive).count() == 1;
    }

    bool hasCall(QString call)
    {
        return calls.filter(call, Qt::CaseSensitive).count() > 1;
    }

    bool hasCalls(QString call, int times)
    {
        return calls.filter(call, Qt::CaseSensitive).count() == times;
    }

    bool returnValues(QString method, QVariant value)
    {

    }

    void reset()
    {
        calls.clear();
        callsArgs.clear();
    }

    QStringList calls;
    QVariantList callsArgs;
    QVariantMap returnValue;
};

#endif // MOCKBASE

