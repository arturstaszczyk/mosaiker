#ifndef COMMANDCREATEMOSAIC_H
#define COMMANDCREATEMOSAIC_H

#include "Command.h"
#include "Interfaces/IImageSlicer.h"
#include "Interfaces/IIndexLoader.h"
#include "Interfaces/IIndexMatcherStrategy.h"

#include "Models/PictureModel.h"
#include "Models/MatcherModel.h"

#define DEFAULT_SLICE_SIZE 64

class CommandCreateMosaic : public Command
{
    Q_OBJECT

public:
    explicit CommandCreateMosaic(IImageSlicer* imageSlicer, IIndexMatcherStrategy* indexMather,
                                 PictureModel* primaryImage,
                                 QObject* parent = nullptr);

    void setSliceSize(quint32 sizeInPixels);
    void setSliceSize(QSize size);
    virtual void execute();

public slots:
    void onSliceIndexed(quint32 imageNo, QString imageName, quint32 index);
    void onIndexingFinished();

    void onImageCreatorDrawn(quint32 sliceNo);
    void onImageCreated(QImage image);
    void onImageCreatorFinished();

private:
    IImageSlicer* mImageSlicer;
    IIndexMatcherStrategy* mIndexMatcher;

    MatcherModel* mMatcherModel;
    PictureModel* mPictureModel;

    QList<QString> mImageNames;

    QSize mSliceSize;
};

#endif // COMMANDCREATEMOSAIC_H
