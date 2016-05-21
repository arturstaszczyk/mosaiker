#include "CommandCreateMosaic.h"

#include <QThread>
#include <QDebug>

#include "ImageIndexer.h"

CommandCreateMosaic::CommandCreateMosaic(IImageSlicer* imageSlicer, MainImageModel* imageModel,
                                         QObject* parent)
    : Command(COMMAND_NAME(CommandCreateMosaic), parent)
    , mImageSlicer(imageSlicer)
    , mMainImageModel(imageModel)
{
    dynamic_cast<QObject*>(imageSlicer)->setParent(this);
}

void CommandCreateMosaic::execute()
{
    //mIndexLoader->loadIndex();

    auto image = mMainImageModel->image();
    auto quads = mImageSlicer->slice(image, QSize(64, 64));

    QThread* indexer = new ImageIndexer(quads, this);
    connect(indexer, SIGNAL(imageIndexed(QString, quint32)),
                     this, SLOT(onImageIndexed(QString, quint32)));
    connect(indexer, SIGNAL(finished()), this, SLOT(finished()));
    indexer->start();
}

void CommandCreateMosaic::finished()
{
    finish();
}

void CommandCreateMosaic::onImageIndexed(QString name, quint32 color)
{
    Q_UNUSED(name);
    qDebug() << color;
}
