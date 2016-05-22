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
                                 PictureModel* primaryImage, PictureModel* secondaryImage,
                                 QObject* parent = nullptr);

    virtual void execute();

public slots:
    void onImageIndexed(quint32 imageNo, QString imageName, quint32 index);
    void finished();

private:
    IImageSlicer* mImageSlicer;
    IIndexLoader* mIndexLoader;
    PictureModel* mMainImageModel;
    PictureModel* mSecondaryImageModel;
};

#endif // COMMANDCREATEMOSAIC_H
