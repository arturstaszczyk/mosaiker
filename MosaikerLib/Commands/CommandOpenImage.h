#ifndef COMMANDOPENIMAGE_H
#define COMMANDOPENIMAGE_H

#include <QFileDialog>

#include "Command.h"
#include "ImageManipulatorBuilder.h"
#include "Interfaces/IFileChooser.h"
#include "Interfaces/ImageLibraryAdapterInt.h"

class CommandOpenImage : public Command
{
    Q_OBJECT
public:
    CommandOpenImage(ImageManipulatorBuilder& imageManipulatorBuilder,
                     IFileChooser& fileDialog, QObject* parent = nullptr);

    virtual void execute() override;

signals:
    void imageOpened(QImage);

private:
    ImageManipulatorBuilder& mImageManipulatorBuilder;
    IFileChooser& mFileChooser;
};

#endif // COMMANDOPENIMAGE_H
