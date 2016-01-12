#ifndef COMMANDOPENIMAGE_H
#define COMMANDOPENIMAGE_H

#include <QFileDialog>

#include "Command.h"
#include "Interfaces/IFileChooser.h"

class CommandOpenImage : public Command
{
    Q_OBJECT
public:
    CommandOpenImage(IFileChooser& fileDialog, QObject* parent = nullptr);

    virtual void execute() override;

signals:
    void imageOpened(QImage);

private:
    IFileChooser& mFileChooser;
};

#endif // COMMANDOPENIMAGE_H
