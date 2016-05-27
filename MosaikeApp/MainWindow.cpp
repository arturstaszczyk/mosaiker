#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <chrono>

#include <QFile>
#include <QDebug>
#include <QThread>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlProperty>

#include <ImageOps/ImageSlicer.h>
#include <IndexingOps/IndexLoader.h>
#include <IndexingOps/IndexBuilder.h>
#include <FileSystemOps/FileChooser.h>
#include <FileSystemOps/ResourceFinder.h>
#include <IndexingOps/IndexMatcherFactory.h>
#include <Interfaces/IIndexMatcherStrategy.h>

#include <Commands/CommandOpenImage.h>
#include <Commands/CommandBuildIndex.h>
#include <Commands/CommandSaveMosaic.h>
#include <Commands/CommandCreateMosaic.h>
#include <Commands/CommandOpenResourcesDir.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mCommandRecycler = new CommandRecycler(std::chrono::milliseconds(100), this);

    ui->setupUi(this);
    MatcherModel::declareInQml();

    mMatcherModel = new MatcherModel(this);
    mPrimaryImageModel = new PictureModel(this);
    mResourcesDirModelPtr = new ResourcesDirModel(this);
    mProgressBarModelPtr = new ProgressBarModel(this);
    mMakeMosaicButtonModelPtr = new MosaicBuildButtonModel(this);
    mSliceSizeModel = new SliceSizeModel(this);

    ui->quickWidget->engine()->addImageProvider("mainImageModel", mPrimaryImageModel);

    ui->quickWidget->rootContext()->setContextProperty("sliceSizeModel", mSliceSizeModel);
    ui->quickWidget->rootContext()->setContextProperty("matcherModel", mMatcherModel);
    ui->quickWidget->rootContext()->setContextProperty("mainImageModel", mPrimaryImageModel);
    ui->quickWidget->rootContext()->setContextProperty("resourcesDirModel", mResourcesDirModelPtr);
    ui->quickWidget->rootContext()->setContextProperty("progressBarModel", mProgressBarModelPtr);
    ui->quickWidget->rootContext()->setContextProperty("makeMosaicButtonModel", mMakeMosaicButtonModelPtr);

    ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));

    QObject* slider = ui->quickWidget->rootObject()->findChild<QObject*>("opacitySlider");
    mPrimaryImageModel->setImageOpacity(slider->property("value").toFloat());

    QObject* root = ui->quickWidget->rootObject();

    connect(root, SIGNAL(openImage()), this, SLOT(onOpenOriginalFileButton()));
    connect(root, SIGNAL(setResourcesPath()), this, SLOT(onOpenResourcesDirButton()));
    connect(root, SIGNAL(buildIndex()), this, SLOT(onBuildIndexButton()));
    connect(root, SIGNAL(makeMosaic()), this, SLOT(onMakeMosaicButton()));
    connect(root, SIGNAL(saveMosaic()), this, SLOT(onSaveMosaicButton()));

    connect(root, SIGNAL(opacityChanged(QVariant)), this, SLOT(onOpacityChanged(QVariant)));

    mMatcherModel->setDistance(5);
    mSliceSizeModel->setSliceSize(QSize(64, 64));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenOriginalFileButton()
{
    FileChooser* pathChooser = new FileChooser;

    CommandOpenImage* openImageCmd = new CommandOpenImage(pathChooser);
    QObject::connect(openImageCmd, SIGNAL(imageOpened(QImage)),
                     mPrimaryImageModel, SLOT(setDisplayImage(QImage)));

    mCommandRecycler->executeAndDispose(openImageCmd);

    mMakeMosaicButtonModelPtr->setWasCreated(false);
}

void MainWindow::onOpenResourcesDirButton()
{
    FileChooser* pathChooser = new FileChooser;
    CommandOpenResourcesDir* openResourcesCmd = new CommandOpenResourcesDir(pathChooser);

    QObject::connect(openResourcesCmd, SIGNAL(dirOpened(QString)),
                     mResourcesDirModelPtr, SLOT(setResourcesDir(QString)));

    mCommandRecycler->executeAndDispose(openResourcesCmd);
}

void MainWindow::onBuildIndexButton()
{
    auto resourcesDir = mResourcesDirModelPtr->resourcesDir();
    QString indexFilePath = QDir::cleanPath(resourcesDir + "/" +  ResourcesDirModel::INDEX_FILE);

    IndexBuilder* indexBuilder = new IndexBuilder(indexFilePath);
    ResourceFinder* resourcesFinder = new ResourceFinder(resourcesDir);
    resourcesFinder->addFilter({"*.jpg", "*.png", "*.jpeg"});
    CommandBuildIndex* buildIndexCmd = new CommandBuildIndex(resourcesFinder, indexBuilder, this);

    connect(buildIndexCmd, SIGNAL(commandProgress(quint32)), this, SLOT(onAsyncCommandProgress(quint32)));
    connect(buildIndexCmd, SIGNAL(commandFinished()), this, SLOT(onCommandIndexBuilt()));

    mResourcesDirModelPtr->setIndexBuilding(true);

    mCommandRecycler->executeAndDispose(buildIndexCmd);
}

void MainWindow::onAsyncCommandProgress(quint32 progress)
{
    mProgressBarModelPtr->setValue(progress);
}

void MainWindow::onCommandIndexBuilt()
{
    mResourcesDirModelPtr->setIndexBuilt(true);
    mResourcesDirModelPtr->setIndexBuilding(false);
    mProgressBarModelPtr->setValue(0);
}

void MainWindow::onMakeMosaicButton()
{
    auto resourcesDir = mResourcesDirModelPtr->resourcesDir();
    QString indexFilePath = QDir::cleanPath(resourcesDir + "/" +  ResourcesDirModel::INDEX_FILE);
    IndexLoader* indexLoader = new IndexLoader(indexFilePath);

    ImageSlicer* imageSlicer = new ImageSlicer();
    IIndexMatcherStrategy* indexMatcher = IndexMatcherFactory::create(indexLoader, mMatcherModel);
    CommandCreateMosaic* createMosaicCmd = new CommandCreateMosaic(imageSlicer, indexMatcher,
                                                                   mPrimaryImageModel,
                                                                   this);
    createMosaicCmd->setSliceSize(mSliceSizeModel->sliceSize());

    connect(createMosaicCmd, SIGNAL(commandProgress(quint32)),
            this, SLOT(onAsyncCommandProgress(quint32)));
    connect(createMosaicCmd, SIGNAL(commandFinished()),
            this, SLOT(onCommandMosaicCreated()));

    mMakeMosaicButtonModelPtr->setIsBeingCreated(true);
    mCommandRecycler->executeAndDispose(createMosaicCmd);
}

void MainWindow::onCommandMosaicCreated()
{
    mProgressBarModelPtr->setValue(0);
    mMakeMosaicButtonModelPtr->setIsBeingCreated(false);
    mMakeMosaicButtonModelPtr->setWasCreated(true);
}

void MainWindow::onSaveMosaicButton()
{
    FileChooser* pathChooser = new FileChooser;
    CommandSaveMosaic* cmdSaveMosaic = new CommandSaveMosaic(pathChooser, mPrimaryImageModel, this);
    mCommandRecycler->executeAndDispose(cmdSaveMosaic);
}

void MainWindow::onOpacityChanged(QVariant opacity)
{
    mPrimaryImageModel->setImageOpacity(opacity.toFloat());
}
