#ifndef COMMANDRECYCLER_H
#define COMMANDRECYCLER_H

#include <chrono>

#include <QTimer>
#include <QObject>

#include <Commands/Command.h>

class CommandRecycler : public QObject
{
    Q_OBJECT
public:
    explicit CommandRecycler(std::chrono::milliseconds msecDelay, QObject *parent = 0);

    void executeAndDispose(Command* command);

private slots:
    void recycleCommands();

private:
    QTimer* mRecyclerTimer;
    QList<Command*> mCommandsContainer;
};

#endif // COMMANDRECYCLER_H
