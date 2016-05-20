#ifndef COMMANDCREATEMOSAIC_H
#define COMMANDCREATEMOSAIC_H

#include "Command.h"
class CommandCreateMosaic : public Command
{
    Q_OBJECT

public:
    explicit CommandCreateMosaic(QObject* parent = nullptr);

    virtual void execute();

public slots:
    void onImageIndexed(QString, quint32);
    void finished();
};

#endif // COMMANDCREATEMOSAIC_H
