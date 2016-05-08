#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

#define COMMAND_NAME(class) #class

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QString name, QObject *parent = 0);
    virtual~Command(){}

    virtual void execute() = 0;

    bool finished() const { return mFinished; }
    QString name() const { return mName; }

signals:
    void onFinish();

protected:
    void finish() { mFinished = true; emit onFinish(); }

protected:
    bool mFinished;
    QString mName;

protected:
    class CommandFinisher
    {
    public:
        explicit CommandFinisher(Command* command)
            : mCommand(command) {}

        ~CommandFinisher()
        {
            mCommand->finish();
        }

    private:
        Command* mCommand;
    };
};

#endif // COMMAND_H
