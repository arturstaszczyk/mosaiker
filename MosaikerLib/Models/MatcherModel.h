﻿#ifndef MATCHERMODEL_H
#define MATCHERMODEL_H

#include <QtQml>
#include <QObject>

class MatcherModel : public QObject
{
    Q_OBJECT
public:
    enum MatcherType
    {
        MatcherGreedy,
        MatcherDistance,
    };
    Q_ENUMS(MatcherType)

    explicit MatcherModel(QObject *parent = 0);

    Q_PROPERTY(MatcherType selectedMatcher READ matcher WRITE setMatcher NOTIFY matcherChanged)
    Q_PROPERTY(quint32 distance READ distance WRITE setDistance NOTIFY distanceChanged)

    static void declareInQml()
    {
        qmlRegisterUncreatableType<MatcherModel>("Matchers", 1, 0, "Matchers",
                                                "Cannot instantiate enum class");
    }

public:

    quint32 distance() const { return mDistance; }
    MatcherType matcher() const { return mMatcher; }

signals:
    void matcherChanged(MatcherType matcher);
    void distanceChanged(quint32 distance);

public slots:
    void setDistance(quint32);
    void setMatcher(MatcherType matcher);

private:
    MatcherType mMatcher;
    quint32 mDistance;
};

#endif // MATCHERMODEL_H
