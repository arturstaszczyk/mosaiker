#ifndef MATCHERENUM_H
#define MATCHERENUM_H

#include <QtQml>
#include <QObject>

class MatcherEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(MatcherType)

public:
    explicit MatcherEnum(QObject* parent = nullptr)
        : QObject(parent) {}

    enum MatcherType
    {
        MatcherGreedy,
        MatcherDistance,
    };

    static void declareInQml()
    {
        qmlRegisterUncreatableType<MatcherEnum>("Matchers", 1, 0, "Matchers",
                                                "Cannot instantiate enum class");
    }
};

#endif // MATCHERENUM_H
