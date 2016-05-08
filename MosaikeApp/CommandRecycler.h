#ifndef COMMANDRECYCLER_H
#define COMMANDRECYCLER_H

#include <QObject>

class CommandRecycler : public QObject
{
    Q_OBJECT
public:
    explicit CommandRecycler(QObject *parent = 0);

signals:

public slots:
};

#endif // COMMANDRECYCLER_H