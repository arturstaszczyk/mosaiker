#ifndef COMMANDOPENIMAGE_H
#define COMMANDOPENIMAGE_H

#include <QFileDialog>

#include "Command.h"
#include "ImageLibraryAdapter.h"

class CommandOpenImage : public Command
{
public:
    CommandOpenImage(ImageLibraryAdapter& imageLibrary,
                     QFileDialog& fileDialog, QObject* parent = nullptr);

    virtual void execute() override;

signals:
    void imageOpened(QImage);

private:
    ImageLibraryAdapter& mImageLibrary;
    QFileDialog& mFileDialog;
};

#endif // COMMANDOPENIMAGE_H
