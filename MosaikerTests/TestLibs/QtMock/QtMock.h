#ifndef QTMOCK_H
#define QTMOCK_H

#include <QStringList>
#include <QVariantList>

#define MOCK_FNAME __FUNCTION__
#define MOCK_CALL mCalls.append(MOCK_FNAME)
#define MOCK_ARG(call, x) addCallArg(call, x)
#define SET_RETURN_VALUES(call, args) addReturnValues(call, args)
#define RETURN_VALUES(T) returnValue<T>(MOCK_FNAME)

namespace QtMockExt
{

class QtMock
{
public:

    void reset()
    {
        mCalls.clear();
        mCallArgs.clear();
        mReturnValue.clear();
        mReturnValuesUsed.clear();;
    }

    const QStringList& calls() const { return mCalls; }

    bool hasExactlyOneCall(QString call) const
    {
        return mCalls.filter(call, Qt::CaseSensitive).count() == 1;
    }

    bool hasCall(QString call) const
    {
        return mCalls.filter(call, Qt::CaseSensitive).count() > 1;
    }

    bool hasCalls(QString call, int times) const
    {
        return mCalls.filter(call, Qt::CaseSensitive).count() == times;
    }

    void returnValues(QString method, QVariantList values)
    {
        SET_RETURN_VALUES(method, values);
    }

    const QVariantList callArgs(QString callName)
    {
        return mCallArgs.value(callName).toList();
    }

protected:
    void addCallArg(QString callName, QVariant arg)
    {
        if(!mCallArgs.contains(callName))
            mCallArgs.insert(callName, QVariantList());

        auto argsList = mCallArgs[callName].toList();
        argsList.append(arg);
        mCallArgs[callName] = argsList;
    }

    void addReturnValues(QString callName, QVariantList values)
    {
        if(!mReturnValue.contains(callName))
        {
            mReturnValue.insert(callName, values);
            mReturnValuesUsed.insert(callName, 0);
        }
        else
        {
            auto retValues = mReturnValue[callName].toList();
            retValues.append(values);
            mReturnValue[callName] = retValues;
        }
    }

    template
    <typename T>
    T returnValue(QString callName)
    {
        T retValue = T();
        if(mReturnValue.contains(callName))
        {
            int currentIdx = mReturnValuesUsed[callName].toInt();
            auto returnValuesList = mReturnValue[callName].toList();
            if(returnValuesList.count() > currentIdx)
            {
                retValue = qvariant_cast<T>(returnValuesList[currentIdx]);
                mReturnValuesUsed[callName] = currentIdx + 1;
            }
        }

        return retValue;
    }

protected:
    QStringList mCalls;
    QVariantMap mCallArgs;
    QVariantMap mReturnValue;
    QVariantMap mReturnValuesUsed;
};

}

#endif // QTMOCK_H
