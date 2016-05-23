#ifndef COMMANDCREATEMOSAIC_H
#define COMMANDCREATEMOSAIC_H

#include "Command.h"
#include "Interfaces/IImageSlicer.h"
#include "Interfaces/IIndexLoader.h"

#include "Models/PictureModel.h"

#define DEFAULT_SLICE_SIZE 64

class CommandCreateMosaic : public Command
{
    Q_OBJECT

public:
    explicit CommandCreateMosaic(IImageSlicer* imageSlicer, IIndexLoader* indexLoader,
                                 PictureModel* primaryImage, QObject* parent = nullptr);

    void setSliceSize(quint32 sizeInPixels);
    void setSliceSize(QSize size);
    virtual void execute();

public slots:
    void onSliceIndexed(quint32 imageNo, QString imageName, quint32 index);
    void indexingFinished();

    void onSliceDrawn(quint32 sliceNo);
    void imageCreated(QImage image);
    void finishCommand();

private:
    IImageSlicer* mImageSlicer;
    IIndexLoader* mIndexLoader;
    PictureModel* mPictureModel;

    QList<QString> mImageNames;

    QSize mSliceSize;
};

#endif // COMMANDCREATEMOSAIC_H
