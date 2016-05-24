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

#include <FileChooser.h>
#include <ImageSlicer.h>
#include <IndexLoader.h>
#include <IndexBuilder.h>
#include <ResourceFinder.h>

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

    mPrimaryImageModel = new PictureModel(this);
    mResourcesDirModelPtr = new ResourcesDirModel(this);
    mProgressBarModelPtr = new ProgressBarModel(this);
    mMakeMosaicButtonModelPtr = new MosaicBuildButtonModel(this);

    ui->quickWidget->engine()->addImageProvider("mainImageModel", mPrimaryImageModel);

    ui->quickWidget->rootContext()->setContextProperty("mainImageModel", mPrimaryImageModel);
    ui->quickWidget->rootContext()->setContextProperty("resourcesDirModel", mResourcesDirModelPtr);
    ui->quickWidget->rootContext()->setContextProperty("progressBarModel", mProgressBarModelPtr);
    ui->quickWidget->rootContext()->setContextProperty("makeMosaicButtonModel", mMakeMosaicButtonModelPtr);

    ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));

    QObject* slider = ui->quickWidget->rootObject()->findChild<QObject*>("opacitySlider");
    mPrimaryImageModel->setImageOpacity(slider->property("value").toFloat());

    QObject* root = ui->quickWidget->rootObject();

    connect(root, SIGNAL(openImage()), this, SLOT(openOriginalFileRequest()));
    connect(root, SIGNAL(setResourcesPath()), this, SLOT(openResourcesDirRequested()));
    connect(root, SIGNAL(buildIndex()), this, SLOT(buildIndexRequested()));
    connect(root, SIGNAL(makeMosaic()), this, SLOT(makeMosaicRequested()));
    connect(root, SIGNAL(saveMosaic()), this, SLOT(saveMosaicRequested()));

    connect(root, SIGNAL(opacityChanged(QVariant)), this, SLOT(onOpacityChanged(QVariant)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openOriginalFileRequest()
{
    PathChooser* pathChooser = new PathChooser;

    CommandOpenImage* openImageCmd = new CommandOpenImage(pathChooser);
    QObject::connect(openImageCmd, SIGNAL(imageOpened(QImage)),
                     mPrimaryImageModel, SLOT(setDisplayImage(QImage)));

    mCommandRecycler->executeAndDispose(openImageCmd);

    mMakeMosaicButtonModelPtr->setWasCreated(false);
}

void MainWindow::openResourcesDirRequested()
{
    PathChooser* pathChooser = new PathChooser;
    CommandOpenResourcesDir* openResourcesCmd = new CommandOpenResourcesDir(pathChooser);

    QObject::connect(openResourcesCmd, SIGNAL(dirOpened(QString)),
                     mResourcesDirModelPtr, SLOT(setResourcesDir(QString)));

    mCommandRecycler->executeAndDispose(openResourcesCmd);
}

void MainWindow::buildIndexRequested()
{
    auto resourcesDir = mResourcesDirModelPtr->resourcesDir();
    QString indexFilePath = QDir::cleanPath(resourcesDir + "/" +  ResourcesDirModel::INDEX_FILE);

    IndexBuilder* indexBuilder = new IndexBuilder(indexFilePath);
    ResourceFinder* resourcesFinder = new ResourceFinder(resourcesDir);
    CommandBuildIndex* buildIndexCmd = new CommandBuildIndex(resourcesFinder, indexBuilder, this);

    connect(buildIndexCmd, SIGNAL(commandProgress(quint32)), this, SLOT(onAsyncCommandProgress(quint32)));
    connect(buildIndexCmd, SIGNAL(commandFinished()), this, SLOT(onIndexBuilt()));

    mResourcesDirModelPtr->setIndexBuilding(true);

    mCommandRecycler->executeAndDispose(buildIndexCmd);
}

void MainWindow::onAsyncCommandProgress(quint32 progress)
{
    mProgressBarModelPtr->setValue(progress);
}

void MainWindow::onIndexBuilt()
{
    mResourcesDirModelPtr->setIndexBuilt(true);
    mResourcesDirModelPtr->setIndexBuilding(false);
    mProgressBarModelPtr->setValue(0);
}

void MainWindow::makeMosaicRequested()
{
    auto resourcesDir = mResourcesDirModelPtr->resourcesDir();
    QString indexFilePath = QDir::cleanPath(resourcesDir + "/" +  ResourcesDirModel::INDEX_FILE);
    IndexLoader* indexLoader = new IndexLoader(indexFilePath);

    ImageSlicer* imageSlicer = new ImageSlicer();

    CommandCreateMosaic* createMosaicCmd = new CommandCreateMosaic(imageSlicer, indexLoader,
                                                                   mPrimaryImageModel,
                                                                   this);
    createMosaicCmd->setSliceSize(128);

    connect(createMosaicCmd, SIGNAL(commandProgress(quint32)),
            this, SLOT(onAsyncCommandProgress(quint32)));
    connect(createMosaicCmd, SIGNAL(commandFinished()),
            this, SLOT(onMosaicCreated()));

    mMakeMosaicButtonModelPtr->setIsBeingCreated(true);
    mCommandRecycler->executeAndDispose(createMosaicCmd);
}

void MainWindow::onMosaicCreated()
{
    mProgressBarModelPtr->setValue(0);
    mMakeMosaicButtonModelPtr->setIsBeingCreated(false);
    mMakeMosaicButtonModelPtr->setWasCreated(true);
}

void MainWindow::saveMosaicRequested()
{
    PathChooser* pathChooser = new PathChooser();
    CommandSaveMosaic* cmdSaveMosaic = new CommandSaveMosaic(pathChooser, mPrimaryImageModel, this);
    mCommandRecycler->executeAndDispose(cmdSaveMosaic);
}

void MainWindow::onOpacityChanged(QVariant opacity)
{
    mPrimaryImageModel->setImageOpacity(opacity.toFloat());
}
