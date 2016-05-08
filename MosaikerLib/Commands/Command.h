#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = 0);
    virtual~Command(){}

    virtual void execute() = 0;

    bool finished() const { return mFinished; }

protected:
    bool mFinished;
};

#endif // COMMAND_H
