#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFile>
#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlContext>
#include <QThread>

#include <ResourceFinder.h>
#include <FileChooser.h>
#include <Commands/CommandOpenImage.h>
#include <Commands/CommandOpenResourcesDir.h>
#include <Commands/CommandBuildIndex.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mCommandRecyclerTimer(new QTimer(this))
{
    ui->setupUi(this);

    mImageModelPtr = new ImageModel(this);
    mResourcesDirModelPtr = new ResourcesDirModel(this);
    mProgressBarModelPtr = new ProgressBarModel(this);

    ui->quickWidget->engine()->addImageProvider("imageModel", mImageModelPtr);

    ui->quickWidget->rootContext()->setContextProperty("imageModel", mImageModelPtr);
    ui->quickWidget->rootContext()->setContextProperty("resourcesDirModel", mResourcesDirModelPtr);
    ui->quickWidget->rootContext()->setContextProperty("progressBarModel", mProgressBarModelPtr);

    ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));

    QObject* root = ui->quickWidget->rootObject();

    QObject::connect(root, SIGNAL(openImage()), this, SLOT(openOriginalFileRequest()));
    QObject::connect(root, SIGNAL(setResourcesPath()), this, SLOT(openResourcesDirRequested()));
    QObject::connect(root, SIGNAL(buildIndex()), this, SLOT(buildIndexRequested()));
}


void MainWindow::setupCommandsRecycler(quint32 msecDelay)
{
    mCommandRecyclerTimer->setInterval(msecDelay);
    mCommandRecyclerTimer->setSingleShot(false);
    connect(mCommandRecyclerTimer, SIGNAL(timeout()), this, SLOT(recycleCommands()));
    mCommandRecyclerTimer->start();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openOriginalFileRequest()
{
    PathChooser* pathChooser = new PathChooser;

    CommandOpenImage* openImageCommand = new CommandOpenImage(pathChooser);
    QObject::connect(openImageCommand, SIGNAL(imageOpened(QImage)),
                     mImageModelPtr, SLOT(setOriginalImage(QImage)));

    openImageCommand->execute();
    mCommandRecycler.append(openImageCommand);
}

void MainWindow::openResourcesDirRequested()
{
    PathChooser* pathChooser = new PathChooser;
    CommandOpenResourcesDir* openResourcesCommand = new CommandOpenResourcesDir(pathChooser);

    QObject::connect(openResourcesCommand, SIGNAL(dirOpened(QString)),
                     mResourcesDirModelPtr, SLOT(setResourcesDir(QString)));

    openResourcesCommand->execute();
    mCommandRecycler.append(openResourcesCommand);
}

void MainWindow::buildIndexRequested()
{
    auto resourcesDir = mResourcesDirModelPtr->resourcesDir();
    QString indexFilePath = QDir::cleanPath(resourcesDir + "/" +  ResourcesDirModel::INDEX_FILE);
    QFile indexFile(indexFilePath);

    ResourceFinder* finder = new ResourceFinder(resourcesDir);
    CommandBuildIndex* buildIndex = new CommandBuildIndex(finder, indexFile, this);

    QObject::connect(buildIndex, SIGNAL(resourcesCount(quint32)), this, SLOT(onResourcesCount(quint32)));
    QObject::connect(buildIndex, SIGNAL(updateProgress(quint32)), this, SLOT(onUpdateIndexBuildProgress(quint32)));

    buildIndex->execute();
    mCommandRecycler.append(buildIndex);

    qDebug() << "Written file " << indexFilePath;
    mResourcesDirModelPtr->setIndexBuilt(indexFile.exists());
}

void MainWindow::onResourcesCount(quint32 resourcesCount)
{
    mProgressBarModelPtr->setMaxValue(resourcesCount);
    qDebug() << "Found resources: " << resourcesCount;
}

void MainWindow::onUpdateIndexBuildProgress(quint32 progress)
{
    mProgressBarModelPtr->setValue(progress);
    qDebug() << "Progress (files count): " << progress;
}

void MainWindow::recycleCommands()
{
    static Command* cmd;
    static QList<Command*> garbage;

    cmd = nullptr;
    garbage.clear();

    foreach(cmd, mCommandRecycler)
    {
        if(cmd->finished())
            garbage.append(cmd);
    }

    foreach(cmd, garbage)
    {
        mCommandRecycler.removeOne(cmd);
    }

    garbage.clear();
}
