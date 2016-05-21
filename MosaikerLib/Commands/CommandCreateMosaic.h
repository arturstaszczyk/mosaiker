#ifndef COMMANDCREATEMOSAIC_H
#define COMMANDCREATEMOSAIC_H

#include "Command.h"
#include "Interfaces/IImageSlicer.h"
#include "Interfaces/IIndexLoader.h"

#include "Models/MainImageModel.h"

class CommandCreateMosaic : public Command
{
    Q_OBJECT

public:
    explicit CommandCreateMosaic(IImageSlicer* imageSlicer, IIndexLoader* indexLoader,
                                 MainImageModel* imageModel, QObject* parent = nullptr);

    virtual void execute();

public slots:
    void onImageIndexed(QString, quint32);
    void finished();

private:
    IImageSlicer* mImageSlicer;
    IIndexLoader* mIndexLoader;
    MainImageModel* mMainImageModel;
};

#endif // COMMANDCREATEMOSAIC_H
