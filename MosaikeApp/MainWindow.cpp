﻿#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFile>
#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlContext>
#include <QThread>

#include <ResourceFinder.h>
#include <FileChooser.h>
#include <IndexBuilder.h>
#include <ImageSlicer.h>

#include <Commands/CommandOpenImage.h>
#include <Commands/CommandBuildIndex.h>
#include <Commands/CommandCreateMosaic.h>
#include <Commands/CommandOpenResourcesDir.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mCommandRecycler = new CommandRecycler(100, this);

    ui->setupUi(this);

    mImageModelPtr = new MainImageModel(this);
    mResourcesDirModelPtr = new ResourcesDirModel(this);
    mProgressBarModelPtr = new ProgressBarModel(this);

    ui->quickWidget->engine()->addImageProvider("mainImageModel", mImageModelPtr);

    ui->quickWidget->rootContext()->setContextProperty("mainImageModel", mImageModelPtr);
    ui->quickWidget->rootContext()->setContextProperty("resourcesDirModel", mResourcesDirModelPtr);
    ui->quickWidget->rootContext()->setContextProperty("progressBarModel", mProgressBarModelPtr);

    ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));

    QObject* root = ui->quickWidget->rootObject();

    connect(root, SIGNAL(openImage()), this, SLOT(openOriginalFileRequest()));
    connect(root, SIGNAL(setResourcesPath()), this, SLOT(openResourcesDirRequested()));
    connect(root, SIGNAL(buildIndex()), this, SLOT(buildIndexRequested()));
    connect(root, SIGNAL(makeMosaic()), this, SLOT(makeMosaicRequested()));
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
                     mImageModelPtr, SLOT(setMainImage(QImage)));

    mCommandRecycler->executeAndDispose(openImageCmd);
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

    connect(buildIndexCmd, SIGNAL(resourcesCount(quint32)), this, SLOT(onResourcesCount(quint32)));
    connect(buildIndexCmd, SIGNAL(updateProgress(quint32)), this, SLOT(onUpdateIndexBuildProgress(quint32)));
    connect(buildIndexCmd, SIGNAL(commandFinished()), this, SLOT(onIndexBuilt()));

    mResourcesDirModelPtr->setIndexBuilding(true);

    mCommandRecycler->executeAndDispose(buildIndexCmd);
}

void MainWindow::onResourcesCount(quint32 resourcesCount)
{
    mProgressBarModelPtr->setMaxValue(resourcesCount);
    qDebug() << "Found resources: " << resourcesCount;
}

void MainWindow::onUpdateIndexBuildProgress(quint32 progress)
{
    mProgressBarModelPtr->setValue(progress);
}

void MainWindow::onIndexBuilt()
{
    mResourcesDirModelPtr->setIndexBuilt(true);
    mResourcesDirModelPtr->setIndexBuilding(false);
}

void MainWindow::makeMosaicRequested()
{
    ImageSlicer* imageSlicer = new ImageSlicer();

    CommandCreateMosaic* createMosaicCmd = new CommandCreateMosaic(imageSlicer,
                                                                   mImageModelPtr, this);

    mCommandRecycler->executeAndDispose(createMosaicCmd);
}

