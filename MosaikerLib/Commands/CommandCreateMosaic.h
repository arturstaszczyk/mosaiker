#ifndef COMMANDCREATEMOSAIC_H
#define COMMANDCREATEMOSAIC_H

#include "Command.h"
#include "Interfaces/IImageSlicer.h"
#include "Models/MainImageModel.h"

class CommandCreateMosaic : public Command
{
    Q_OBJECT

public:
    explicit CommandCreateMosaic(IImageSlicer* imageSlicer, MainImageModel* imageModel,
                                 QObject* parent = nullptr);

    virtual void execute();

public slots:
    void onImageIndexed(QString, quint32);
    void finished();

private:
    IImageSlicer* mImageSlicer;
    MainImageModel* mMainImageModel;
};

#endif // COMMANDCREATEMOSAIC_H
