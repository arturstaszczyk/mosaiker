#ifndef MATCHERMODEL_H
#define MATCHERMODEL_H

#include <QtQml>
#include <QObject>

class MatcherModel : public QObject
{
    Q_OBJECT
public:
    explicit MatcherModel(QObject *parent = 0);

    Q_PROPERTY(MatcherType selectedMatcher READ matcher WRITE setMatcher NOTIFY matcherChanged)

public:

    enum MatcherType
    {
        MatcherGreedy,
        MatcherDistance,
    };

    Q_ENUMS(MatcherType)

    void setMatcher(MatcherType matcher);
    MatcherType matcher() const { return mMatcher; }

    static void declareInQml()
    {
        qmlRegisterUncreatableType<MatcherModel>("Matchers", 1, 0, "Matchers",
                                                "Cannot instantiate enum class");
    }

signals:
    void matcherChanged(MatcherType matcher);

public slots:
    void updateMatcher(MatcherType matcher);

private:
    MatcherType mMatcher;
};

#endif // MATCHERMODEL_H
