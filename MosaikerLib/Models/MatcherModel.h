#ifndef MATCHERMODEL_H
#define MATCHERMODEL_H

#include <QObject>

class MatcherModel : public QObject
{
    Q_OBJECT
public:
    explicit MatcherModel(QObject *parent = 0);

public:

//    Q_PROPERTY(type name READ name WRITE setName NOTIFY nameChanged)
};

#endif // MATCHERMODEL_H
